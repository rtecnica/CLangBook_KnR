use std::cmp::Ordering;
use std::env;
use std::fs::File;
use std::io::prelude::*;
use std::process;

mod cross_ref;

struct Position {
    line: u32,
    col: u32,
}

fn main() -> std::io::Result<()> {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Please input filename!");
        process::exit(1)
    }

    let mut file = File::open(&args[1])?;
    let mut buf = String::new();
    file.read_to_string(&mut buf)?;
    let mut crossref: Vec<cross_ref::WordEntry> = Vec::new();
    
    let mut curr_pos = Position { line: 1, col: 0 };
    let mut curr_word = String::new();
            let mut in_word = false;

    for c in buf.chars() {
        let holder: Vec<char> = c.to_lowercase().collect();
        let holder = holder[0];

        if holder.is_alphabetic() {
            if !in_word {
                in_word = true;
            }
            curr_word.push(c);
        } else {
            if in_word {
                let new_word = cross_ref::WordEntry::new_from(&curr_word, &curr_pos.line);
                let mut new_entry = false;
                for i in 0..crossref.len() {
                    if crossref[i].compare_word_alph(&new_word) == Ordering::Equal {
                        crossref[i].count();
                        crossref[i].add_page(curr_pos.line);
                        new_entry = true;
                    }
                }
                if !new_entry {
                    crossref.push(new_word);
                }
                curr_word = String::new();
            }
            if c == '\n' {
                curr_pos.line += 1;
                curr_pos.col = 0;
            }
            in_word = false;
        }

        curr_pos.col += 1;
    }

    crossref.sort_by(|a, b| a.compare_word_alph(b));
    for entry in crossref {
        println!("{}", entry);
    }

    Ok(())
}

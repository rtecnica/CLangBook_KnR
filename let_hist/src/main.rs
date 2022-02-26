use std::collections::HashMap;
use std::env;
use std::fs::File;
use std::io::prelude::*;
use std::process;

const BAR_HEIGHT: u8 = 20;
const BAR_TOKEN: char = '#'; //'ﱢ';

fn main() -> std::io::Result<()> {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Please input filename!");
        process::exit(1);
    }

    let mut file = File::open(&args[1])?;

    let mut buf = String::new();
    file.read_to_string(&mut buf)?;

    //Init buckets
    let mut buckets: std::collections::HashMap<char, u32> = HashMap::new();

    // use iterator to implement state machine
    for c in buf.chars() {
        if c.is_alphabetic() {
            let mut holder: u32 = 0;
            let cholder: Vec<char> = c.to_lowercase().collect();
            let cholder = cholder[0];
            if let Some(val) = buckets.get(&cholder) {
                holder = *val;
            } else {
                buckets.insert(cholder, 1);
            }
            if holder != 0 {
                buckets.insert(cholder, holder + 1);
            }
        }
    }
    // Get word total
    let mut word_total = 0;
    for val in buckets.values() {
        word_total += val;
    }

    // Assemble index
    let mut alph_idx: Vec<&char> = buckets.keys().collect();
    alph_idx.sort();

    // Display Bars
    for b in 0..BAR_HEIGHT {
        for n in &alph_idx {
            if let Some(val) = buckets.get(&n) {
                let bar_height = (*val as f32 / *buckets.values().max().unwrap_or(&1) as f32
                    * BAR_HEIGHT as f32) as u8;
                if bar_height >= (BAR_HEIGHT - b) {
                    print!("{}{}{}\t", BAR_TOKEN, BAR_TOKEN, BAR_TOKEN);
                } else {
                    print!("   \t");
                }
            }
        }
        println!();
    }
    println!();
    for n in &alph_idx {
        if let Some(val) = buckets.get(&n) {
            print!("{}\t", val);
        }
    }
    println!();

    for n in &alph_idx {
        if let Some(val) = buckets.get(&n) {
            let bar_height = *val as f32 / word_total as f32 * 100.0;
            print!("{:.2}%\t", bar_height);
        }
    }
    println!();
    for n in &alph_idx {
        if let Some(_) = buckets.get(&n) {
            print!("{}\t", n);
        }
    }
    println!();
    println!("{} {}", buckets.len(), alph_idx.len());
    Ok(())
}

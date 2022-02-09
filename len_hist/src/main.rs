use std::env;
use std::fs::File;
use std::process;
use std::io::prelude::*;
use std::collections::HashMap;

const BAR_HEIGHT: u8 = 20;
const BAR_TOKEN: char = 'ﱢ';

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
    let mut buckets: std::collections::HashMap<u8,u32> = HashMap::new();
    
    // use iterator to implement state machine
    let mut in_word = false;
    let mut curr_len: u8 = 0;
    for c in buf.chars() {
        if c.is_ascii_alphabetic() {
            if in_word {
                curr_len = curr_len + 1;
            } else {
                curr_len = 1;
                in_word = true;
            }
        } else {
            if in_word {
                if let Some(val) = buckets.get_mut(&curr_len) {
                    *val += 1; 
                } else {
                    buckets.insert(curr_len, 1);
                }
                in_word = false;
            }
        }
    }
    // Get word total
    let mut word_total = 0;
    for val in buckets.values() {
        word_total += val;
    }
    // Display Bars
    for b in 0..BAR_HEIGHT {
        for n in *buckets.keys().min().unwrap_or(&0)..*buckets.keys().max().unwrap_or(&0)+1 {
            if let Some(val) = buckets.get(&n) {
                let bar_height = (*val as f32 / *buckets.values().max().unwrap_or(&1) as f32 * BAR_HEIGHT as f32) as u8;
                if bar_height >= (BAR_HEIGHT - b) {
                    print!("{} {} {}\t", BAR_TOKEN, BAR_TOKEN, BAR_TOKEN);
                } else {
                    print!("   \t");
                }
            }
        }
        println!();
    }
    for n in *buckets.keys().min().unwrap_or(&0)..*buckets.keys().max().unwrap_or(&0)+1 {
        if let Some(val) = buckets.get(&n) {
            print!("{}\t", val);
        }
    }
    println!();
    
    for n in *buckets.keys().min().unwrap_or(&0)..*buckets.keys().max().unwrap_or(&0)+1 {
        if let Some(val) = buckets.get(&n) {
            let bar_height = *val as f32 / word_total as f32 * 100.0;
            print!("{:.2}%\t", bar_height);
        }
    }
    println!();
    
    for n in *buckets.keys().min().unwrap_or(&0)..*buckets.keys().max().unwrap_or(&0)+1 {
        if let Some(_) = buckets.get(&n) {
            print!("{}\t", n);
        }

    }
    println!();
    
      
    Ok(())
}

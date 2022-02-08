use std::env;

fn main() {
    let new_str = String::from("Sample String");
    let mut rev_str = String::new();
    
    for char in new_str.chars().rev() {
        rev_str.push(char);
    }
    println!("{}", rev_str);
}

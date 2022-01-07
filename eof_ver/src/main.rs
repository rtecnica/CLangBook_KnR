use std::fs;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    
    println!("{}", &args[1]);
    let file = fs::read(&args[1]).unwrap();
    println!("{:?}", file);
    // Turns out rust doesn't handle files in the same way as C  
}

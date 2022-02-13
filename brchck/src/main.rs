use std::env;
use std::fs::File;
use std::io::prelude::*;
use std::process;

#[derive(Copy, Clone, PartialEq, Debug)]
struct Position {
    line: u32,
    col: u32,
}

#[derive(PartialEq, Copy, Clone, Debug)]
enum BrackPos {
    Opening,
    Closing,
}

#[derive(PartialEq, Copy, Clone, Debug)]
enum BrackType {
    Paren(Position),
    Curly(Position),
    Square(Position),
    Squote(Position),
    Dquote(Position),
    FSlash(BrackPos, Position),
    BSlash(Position),
    None,
}

impl BrackType {
    fn get_var(&self) -> std::mem::Discriminant<BrackType> {
        std::mem::discriminant(self)
    }
}

fn main() -> std::io::Result<()> {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Please input filename!");
        process::exit(1);
    }

    let mut file = File::open(&args[1])?;

    let mut buf = String::new();
    file.read_to_string(&mut buf)?;

    let mut stack: Vec<BrackType> = Vec::new();

    let mut curr_pos = Position { line: 1, col: 0 };

    for c in buf.chars() {
        curr_pos.col += 1;
        let last_brack: BrackType;

        if let Some(brack) = stack.last() {
            match brack {
                BrackType::BSlash(_) => {
                    stack.pop();
                    continue;
                }

                _ => last_brack = *brack,
            };
        } else {
            last_brack = BrackType::None;
        }

        match c {
            '(' | '{' | '[' => {
                let curr_brack = match c {
                    '(' => BrackType::Paren(curr_pos),
                    '{' => BrackType::Curly(curr_pos),
                    '[' => BrackType::Square(curr_pos),
                    _ => BrackType::None,
                };

                match last_brack {
                    BrackType::Paren(_) | BrackType::Square(_) | BrackType::Curly(_) => {
                        stack.push(curr_brack);
                    }

                    BrackType::FSlash(brackpos, _) => match brackpos {
                        BrackPos::Opening => {
                            stack.pop();
                            stack.push(curr_brack);
                        }

                        BrackPos::Closing => {}
                    },

                    BrackType::None => stack.push(curr_brack),

                    _ => {}
                };
            }

            ')' | '}' | ']' => {
                let curr_brack = match c {
                    ')' => BrackType::Paren(curr_pos),
                    '}' => BrackType::Curly(curr_pos),
                    ']' => BrackType::Square(curr_pos),
                    _ => BrackType::None,
                };
                if curr_brack.get_var() == last_brack.get_var() {
                    stack.pop();
                } else {
                    match last_brack {
                        BrackType::Square(pos) => {
                            eprintln!(
                                "Unclosed square bracet at ln:{} col:{} & ln:{} col:{}",
                                pos.line, pos.col, curr_pos.line, curr_pos.col
                            );
                            process::exit(1);
                        }

                        BrackType::Curly(pos) => {
                            eprintln!(
                                "Unclosed curly brace at ln:{} col:{} & ln:{} col:{}",
                                pos.line, pos.col, curr_pos.line, curr_pos.col
                            );
                            process::exit(1);
                        }

                        BrackType::Paren(pos) => {
                            eprintln!(
                                "Unclosed parenthesis at ln:{} col:{} & ln:{} col:{}",
                                pos.line, pos.col, curr_pos.line, curr_pos.col
                            );
                            process::exit(1);
                        }

                        BrackType::None => {
                            eprintln!("Unclosed  at ln:{} col:{}", curr_pos.line, curr_pos.col);
                            process::exit(1);
                        }

                        _ => {}
                    }
                }
            }

            '\'' | '\"' => {
                let curr_brack = match c {
                    '\'' => BrackType::Squote(curr_pos),
                    '\"' => BrackType::Dquote(curr_pos),
                    _ => BrackType::None,
                };

                if last_brack.get_var() == curr_brack.get_var() {
                    stack.pop().unwrap();
                }
            }

            '/' => {
                match last_brack {
                    BrackType::FSlash(BrackPos::Opening, _) => {
                        stack.push(BrackType::FSlash(BrackPos::Closing, curr_pos));
                    }

                    _ => stack.push(BrackType::FSlash(BrackPos::Opening, curr_pos)),
                };
            }

            '\\' => {
                stack.push(BrackType::BSlash(curr_pos));
            }

            '\n' => {
                match last_brack {
                    BrackType::FSlash(pos, position) => match pos {
                        BrackPos::Opening => {}
                        BrackPos::Closing => {
                            if let Some(val) = stack.get(stack.len() - 2) {
                                if let BrackType::FSlash(BrackPos::Opening, _) = val {
                                    stack.pop();
                                    stack.pop();
                                } else {
                                    eprintln!(
                                        "Internal error: Unbalanced comment ln:{} col:{}",
                                        position.line, position.col
                                    );
                                    process::exit(1);
                                };
                            }
                        }
                    },
                    _ => {}
                }
                curr_pos.line += 1;
                curr_pos.col = 0;
            }

            _ => {}
        };
    }

    if stack.len() > 0 {
        if let Some(val) = stack.last() {
            let br_name: String;
            let br_position = match val {
                BrackType::FSlash(_, pos) => {
                    br_name = String::from("Forward Slash");
                    pos
                }
                BrackType::BSlash(pos) => {
                    br_name = String::from("Backslash");
                    pos
                }
                BrackType::Dquote(pos) => {
                    br_name = String::from("Double Quote");
                    pos
                }
                BrackType::Squote(pos) => {
                    br_name = String::from("Single Quote");
                    pos
                }
                BrackType::Paren(pos) => {
                    br_name = String::from("Parenthesis");
                    pos
                }
                BrackType::Curly(pos) => {
                    br_name = String::from("Curly Brace");
                    pos
                }
                BrackType::Square(pos) => {
                    br_name = String::from("Square Brace");
                    pos
                }
                BrackType::None => {
                    return Ok(());
                }
            };
            eprintln!(
                "Unbalanced {} at ln:{} col:{}",
                br_name, br_position.line, br_position.col
            );
        }

        process::exit(1);
    }
    Ok(())
}

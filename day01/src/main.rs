use std::collections::HashMap;

fn part1(file: &str) {
    let lines_vec = file.lines();

    let mut sum = 0;
    let mut num1 = 0;
    let mut num2 = 0;
    for line in lines_vec {
        for c in line.chars() {
            if !c.is_digit(10) {
                continue;
            }
            num1 = c.to_digit(10).unwrap();
            break;
        }

        for c in line.chars().rev() {
            if !c.is_digit(10) {
                continue;
            }
            num2 = c.to_digit(10).unwrap();
            break;
        }

        sum += 10 * num1 + num2;
    }

    println!("Sum: {}", sum);
}

fn part2(file: &str, numbers: HashMap<&str, u32>) {
    let lines_vec = file.lines();

    let mut sum: u32 = 0;
    let mut num1: u32 = 0;
    let mut num2: u32 = 0;
    for line in lines_vec {
        'outer: for (i, c) in line.chars().enumerate() {
            if !c.is_digit(10) {
                for (k, v) in numbers.clone() {
                    if i + k.len() > line.len() {
                        continue;
                    }

                    if k == &line[i..i + k.len()] {
                        num1 = v;
                        break 'outer;
                    }
                }
            } else {
                num1 = c.to_digit(10).unwrap();
                break;
            }
        }

        'outer_two: for (i, c) in line
            .chars()
            .collect::<Vec<_>>()
            .into_iter()
            .enumerate()
            .rev()
        {
            if !c.is_digit(10) {
                for (k, v) in numbers.clone() {
                    if i + k.len() > line.len() {
                        continue;
                    }

                    if k == &line[i..i + k.len()] {
                        num2 = v;
                        break 'outer_two;
                    }
                }
            } else {
                num2 = c.to_digit(10).unwrap();
                break;
            }
        }

        sum += 10 * num1 + num2;
    }

    println!("Sum part2: {}", sum);
}

fn main() {
    let numbers: HashMap<&str, u32> = HashMap::from([
        ("one", 1),
        ("two", 2),
        ("three", 3),
        ("four", 4),
        ("five", 5),
        ("six", 6),
        ("seven", 7),
        ("eight", 8),
        ("nine", 9),
        ("zero", 0),
    ]);

    let file = include_str!("input.txt");
    part1(&file);
    part2(&file, numbers);
}

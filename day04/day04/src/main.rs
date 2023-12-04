use std::collections::HashSet;

fn main() {
    let file = include_str!("input.txt");

    let mut vec1 = Vec::new();
    let mut vec2 = Vec::new();
    let mut points = 0;

    for line in file.lines() {
        vec1.clear();
        vec2.clear();

        let parts: Vec<&str> = line.split('|').collect();

        let numbers_before_pipe: Vec<i32> = parts[0]
            .split_whitespace()
            .filter_map(|s| s.parse().ok())
            .collect();

        let numbers_after_pipe: Vec<i32> = parts[1]
            .split_whitespace()
            .filter_map(|s| s.parse().ok())
            .collect();

        vec1.extend(numbers_before_pipe);
        vec2.extend(numbers_after_pipe);

        let set1: HashSet<_> = vec1.clone().into_iter().collect();
        let set2: HashSet<_> = vec2.clone().into_iter().collect();

        let common_elements: HashSet<_> = set1.intersection(&set2).cloned().collect();
        let res = common_elements.into_iter().collect::<Vec<_>>();

        let mut tmp_res = 0;
        for (i, _) in res.iter().enumerate() {
            if i > 0 {
                tmp_res *= 2;
            } else {
                tmp_res += 1;
            }
        }

        points += tmp_res;
    }

    println!("points: {}", points);
}

use nom::{
    bytes::complete::tag,
    character::complete::{alpha1, digit1, space1},
    combinator::map_res,
    multi::separated_list1,
    sequence::{delimited, separated_pair},
    IResult,
};

#[derive(Debug)]
struct Game {
    id: usize,
    rounds: Vec<Round>,
}

impl Game {
    fn parse(input: &str) -> IResult<&str, Self> {
        let (input, id) = delimited(tag("Game "), parse_number, tag(": "))(input)?;
        let (input, rounds) = separated_list1(tag("; "), Round::parse)(input)?;

        Ok((input, Self { id, rounds }))
    }
}

#[derive(Debug)]
struct Round {
    blue: usize,
    green: usize,
    red: usize,
}

impl Round {
    fn parse(input: &str) -> IResult<&str, Self> {
        // At this step we have
        //   3 blue,
        //   seperated_pair parses like this:
        //   parse_number gets the 3
        //   spac1 ignores the space between 3 and blue
        //   alpha1 gets one or more char

        let (input, count_color_tuples) =
            separated_list1(tag(", "), separated_pair(parse_number, space1, alpha1))(input)?;

        let mut blue = 0;
        let mut green = 0;
        let mut red = 0;
        for (count, color) in count_color_tuples {
            match color {
                "blue" => blue += count,
                "green" => green += count,
                "red" => red += count,
                _ => panic!("Unknown color: {}", color.replace(' ', "X")),
            }
        }

        Ok((input, Self { blue, green, red }))
    }
}

fn part1(input: &str) {
    let max_red = 12;
    let max_green = 13;
    let max_blue = 14;

    let possible_games_iter = input
        .trim()
        .lines()
        .map(|g| Game::parse(g).unwrap().1)
        .filter(|game| {
            game.rounds.iter().all(|round| {
                round.red <= max_red && round.green <= max_green && round.blue <= max_blue
            })
        });

    println!(
        "Part 1: {}",
        possible_games_iter.map(|game| game.id).sum::<usize>()
    );
}

fn part2(input: &str) {
    let possible_games_iter = input.trim().lines().map(|g| Game::parse(g).unwrap().1);

    let game_power = possible_games_iter
        .map(|game| {
            game.rounds
                .iter()
                .fold((0, 0, 0), |(max_red, max_green, max_blue), round| {
                    (
                        max_red.max(round.red),
                        max_green.max(round.green),
                        max_blue.max(round.blue),
                    )
                })
        })
        .map(|(max_red, max_green, max_blue)| max_red * max_green * max_blue);

    println!("Part 2: {}", game_power.sum::<usize>());
}

fn parse_number(i: &str) -> IResult<&str, usize> {
    map_res(digit1, |s: &str| s.parse::<usize>())(i)
}

fn main() {
    let file = include_str!("test.txt");
    part2(file);
}

use std::fmt;
use rand::prelude::*;
use super::genetic::MemberInterface;

#[derive(Clone)]
pub struct Member {
    content: String,
}

impl Member {
    const TARGET: &'static str = "I'm Skynet and I will be back!";
}

impl MemberInterface for Member {
    fn random(rng: &mut ThreadRng) -> Self {
        let random_string: String = (0..Self::TARGET.len())
            .map(|_| rng.gen_range(b' '..b'}' + 1) as char)
            .collect();

        Self {
            content: random_string
        }
    }

    fn crossover(rng: &mut ThreadRng, parent1: &Member, parent2: &Member) -> Self {
        let mut child: String = String::new();

        for (ch1, ch2) in parent1.content.chars().zip(parent2.content.chars()) {
            let random = rng.gen::<bool>();
            let ch = if random { ch1 } else { ch2 };

            child.push(ch);
        }

        let random = rng.gen::<f32>();
        if random<0.05_f32 {
            let mut chars: Vec<char> = child.chars().collect();
            let index = rng.gen_range(0..chars.len());
            let character = rng.gen_range(b' '..b'}' + 1) as char;
            chars[index] = character;
            child = chars.into_iter().collect();
        }

        Self {
            content: child
        }
    }

    fn fitness(&self) -> f32 {
        let diff = self
            .content
            .chars()
            .zip(Self::TARGET.chars())
            .filter(|&(char1, char2)| char1 != char2)
            .count();

        if diff==0 {
            //return f32::INFINITY;
            return f32::MAX;
        }

        return 1_f32 / diff as f32;
    }
}

impl fmt::Display for Member {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self.content)
    }
}

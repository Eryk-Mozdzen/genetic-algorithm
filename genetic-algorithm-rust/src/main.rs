mod genetic;
mod member;

use genetic::Genetic;
use genetic::MemberInterface;
use member::Member;

fn main() {
    let mut genetic = Genetic::<Member>::new(10000);

    loop {
        let result = genetic.fittest();
        let fitness = result.fitness();

        println!("{:10}{:10.3}{:>32}", genetic.epoch(), fitness, result);

        if fitness > 1000_f32 {
            break;
        }

        genetic.evaluate();
    }
}

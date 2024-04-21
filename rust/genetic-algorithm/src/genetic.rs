use rand::prelude::*;
use rand::distributions::WeightedIndex;

pub trait MemberInterface {
    fn random(rng: &mut ThreadRng) -> Self;
    fn crossover(rng: &mut ThreadRng, parent1: &Self, parent2: &Self) -> Self;
    fn fitness(&self) -> f32;
}

pub struct Genetic<T>  {
    rng: ThreadRng,
    population: Vec<T>,
    counter: u32
}

impl<T: MemberInterface+Clone> Genetic<T> {
    pub fn new(size: usize) -> Self {
        let mut rng = rand::thread_rng();

        let mut population = Vec::with_capacity(size);
        for _ in 0..size {
            population.push(T::random(&mut rng));
        }

        Self {
            rng,
            population,
            counter: 0
        }
    }

    pub fn epoch(&self) -> u32 {
        return self.counter;
    }

    pub fn fittest(&self) -> T {
        return self.population[0].clone();
    }

    pub fn evaluate(&mut self) {
        let mut weights: Vec<f32> = Vec::with_capacity(self.population.len());
        for member in &self.population {
            weights.push(member.fitness())
        }

        let best_index = weights
            .iter()
            .enumerate()
            .max_by(|(_, &x), (_, &y)| x.partial_cmp(&y).unwrap())
            .map(|(i, _)| i)
            .unwrap();
        let best = &self.population[best_index];

        let mut next: Vec<T> = Vec::with_capacity(self.population.len());
        next.push(best.clone());

        let distribution = WeightedIndex::new(weights).unwrap();

        for _ in 1..self.population.len() {
            let parent1 = &self.population[distribution.sample(&mut self.rng)];
            let parent2 = &self.population[distribution.sample(&mut self.rng)];

            next.push(T::crossover(&mut self.rng, parent1, parent2));
        }

        self.population = next;
        self.counter +=1;
    }
}

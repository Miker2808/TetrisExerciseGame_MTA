#include "Trainer.h"



// Generate the initial population of solutions with random parameter values
void Trainer::generateStartingBach() {
	std::uniform_real_distribution<double> unif(0, 1);
	for (int i = 0; i < SOL_NUM; i++)
		solutions.push_back(Solution{unif(device), unif(device), unif(device), unif(device), 0 });
}

// Evaluate the fitness of each solution by simulating games of Tetris
void Trainer::fitSolutions() {
	gotoxy(0, 1);
	std::cout << "Generation number: " << gen_number ;
	for (auto& s : solutions) {
		s.fit(SIMULATIONS_PER_SOLUTION);
	}
}

// Log the top solutions to a file
void Trainer::logSolutions() {
	std::string filename = "generation_" + std::to_string(gen_number) + "_top_solutions.txt";
	std::ofstream of(filename);

	if (of.is_open()) {
		for (int i = 0; i < NUM_OF_LOGGED_TOP_SOLUTIONS && i < solutions.size(); ++i) {
			const auto& s = solutions[i];
			of  << "Generation number: " << gen_number << '\n'
				<< "Solution index: " << i << '\n'
				<< "Score: " << s.fitness_score << '\n'
				<< "Max height penalty: " << s.max_height_penality << '\n'
				<< "Holes penalty: " << s.holes_penality << '\n'
				<< "Lines reward: " << s.lines_reward << '\n'
				<< "Bumpiness penalty: " << s.bumpiness_penality << "\n\n";
		}

		of.close();
	}
}

// Sample solutions for mutation and crossover operations
void Trainer::sampleSolutions() {
	std::copy(
		solutions.begin(),
		solutions.begin() + SAMPLE_SIZE,
		std::back_inserter(sample));

	solutions.clear();
};

// Create a mutated copy of a solution
Solution Trainer::makeMutatedCopy(Solution s) {
	Solution mutated_s = s;
	double upper = 1 + (0.01 * SINGLE_SOLUTION_MUTATION_PRECENT);
	double lower = 1 - (0.01 * SINGLE_SOLUTION_MUTATION_PRECENT);
	std::uniform_real_distribution<double> mutator(lower, upper);
	mutated_s.max_height_penality *= mutator(device);
	mutated_s.holes_penality *= mutator(device);
	mutated_s.bumpiness_penality *= mutator(device);
	mutated_s.lines_reward *= mutator(device);
	mutated_s.fitness_score = 0;
	return mutated_s;
}

// Perform crossover between solutions
void Trainer::crossSolutions() {
	std::uniform_int_distribution<int> cross(0, SAMPLE_SIZE - 1);
	std::uniform_real_distribution<double> distribution(0, 1);
	gen_number++;
	double totalFitness = calculateTotalFitness();

	for (int i = 0; i < SOL_NUM - RESTARTED_POP; i++) {
		double randNum = distribution(device);
		Solution parent = selectParentForCrossover(randNum, totalFitness);
		if (randNum < CROSS_RATE) {
			Solution otherParent = sample[cross(device)];
			Solution offspring = performCrossover(parent, otherParent);
			solutions.push_back(offspring);
		}
		else {
			solutions.push_back(makeMutatedCopy(parent));
		}
	}
	sample.clear();
}

// Perform a partial restart of the population
void Trainer::partialRestart() {
	std::uniform_real_distribution<double> unif(0, 1);
	for (int i = 0; i < RESTARTED_POP; i++)
		solutions.push_back(Solution{ unif(device), unif(device), unif(device), unif(device), 0 });
}

// Calculate the total fitness of sampled solutions
double Trainer::calculateTotalFitness() {
	double totalFitness = 0.0;
	for (const auto& s : sample) {
		totalFitness += s.fitness_score;
	}
	return totalFitness;
}

// Select a parent for crossover
Solution Trainer::selectParentForCrossover(double randNum, double totalFitness) {
	double accumulatedFitness = 0.0;
	for (const auto& s : sample) {
		accumulatedFitness += s.fitness_score / totalFitness;
		if (randNum <= accumulatedFitness) {
			return s;
		}
	}
	return sample[0];
}

// Perform crossover between parent solutions
Solution Trainer::performCrossover(const Solution& parent1, const Solution& parent2) {
	// Define the mutation range for crossover
	double upper = 1 + (0.01 * CROSSOVER_MUTATION_PRECENT);
	double lower = 1 - (0.01 * CROSSOVER_MUTATION_PRECENT);

	// Define uniform distributions for generating random numbers
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	std::uniform_real_distribution<double> mutator(lower, upper);

	// Initialize variables to store parameters of the offspring solution
	double max_height_penalty;
	double holes_penalty;
	double bumpiness_penalty;
	double lines_reward;

	// Determine the crossover of each parameter between parent solutions
	// with a 50% chance of inheriting from each parent
	if (distribution(device) < 0.5)
		max_height_penalty = parent1.max_height_penality;
	else
		max_height_penalty = parent2.max_height_penality;

	if (distribution(device) < 0.5)
		holes_penalty = parent1.holes_penality;
	else
		holes_penalty = parent2.holes_penality;

	if (distribution(device) < 0.5)
		bumpiness_penalty = parent1.bumpiness_penality;
	else
		bumpiness_penalty = parent2.bumpiness_penality;

	if (distribution(device) < 0.5)
		lines_reward = parent1.lines_reward;
	else
		lines_reward = parent2.lines_reward;

	// Apply mutation to each parameter of the offspring solution
	max_height_penalty *= mutator(device);
	holes_penalty *= mutator(device);
	bumpiness_penalty *= mutator(device);
	lines_reward *= mutator(device);

	// Create and return the offspring solution with the modified parameters
	return Solution{ max_height_penalty, holes_penalty, bumpiness_penalty, lines_reward, 0 };
}
// Sort solutions based on fitness scores
void Trainer::sortSolutions() {
	std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs) {return lhs.fitness_score > rhs.fitness_score; });
}
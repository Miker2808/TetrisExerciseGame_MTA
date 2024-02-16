#include "Trainer.h"




void Trainer::generateStartingBach() {
	std::uniform_real_distribution<double> unif(0, 1);
	for (int i = 0; i < SOL_NUM; i++)
		solutions.push_back(Solution{unif(device), unif(device), unif(device), 0 });
}

void Trainer::fitSolutions() {
	gotoxy(0, 1);
	std::cout << "Generation number: " << gen_number ;
	int solution_ittrator = 0;
	for (auto& s : solutions) {
		gotoxy(0, 2);
		std::cout << "progress: "<< ((solution_ittrator)*100/ (SOL_NUM) ) << "%" << "\n";
		solution_ittrator++;
		s.fit(SIMULATIONS_PER_SOLUTION);
	}
}

void Trainer::logSolutions() {
	std::string filename = "generation_" + std::to_string(gen_number) + "_top_solutions.txt";
	std::ofstream of(filename);

	if (of.is_open()) {
		// Iterate over the top solutions and write their information to the file
		for (int i = 0; i < NUM_OF_LOGGED_TOP_SOLUTIONS && i < solutions.size(); ++i) {
			const auto& s = solutions[i];
			of << std::fixed
				<< "Generation number: " << gen_number << '\n'
				<< "Solution index: " << i << '\n'
				<< "Score: " << s.fitness_score << '\n'
				<< "Max height penalty: " << s.max_height_penality << '\n'
				<< "Holes penalty: " << s.holes_penality << '\n'
				<< "Bumpiness penalty: " << s.bumpiness_penality << "\n\n";
		}

		of.close();
	}
}

void Trainer::sampleSolutions() {
	std::copy(
		solutions.begin(),
		solutions.begin() + SAMPLE_SIZE,
		std::back_inserter(sample));

	solutions.clear();
};

Solution Trainer::makeMutatedCopy(Solution s) {
	Solution nutated_s = s;
	double upper = 1 + (0.01 * SINGLE_SOLUTION_MUTATION_PRECENT);
	double lower = 1 - (0.01 * SINGLE_SOLUTION_MUTATION_PRECENT);
	std::uniform_real_distribution<double> mutator(lower, upper);
	nutated_s.max_height_penality *= mutator(device);
	nutated_s.holes_penality *= mutator(device);
	nutated_s.bumpiness_penality *= mutator(device);
	return nutated_s;
}


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

void Trainer::partialRestart() {
	std::uniform_real_distribution<double> unif(0, 1);
	for (int i = 0; i < RESTARTED_POP; i++)
		solutions.push_back(Solution{ unif(device), unif(device), unif(device), 0 });
}

double Trainer::calculateTotalFitness() {
	double totalFitness = 0.0;
	for (const auto& s : sample) {
		totalFitness += s.fitness_score;
	}
	return totalFitness;
}

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

Solution Trainer::performCrossover(const Solution& parent1, const Solution& parent2) {
	double upper = 1 + (0.01 * CROSSOVER_MUTATION_PRECENT);
	double lower = 1 - (0.01 * CROSSOVER_MUTATION_PRECENT);
	std::uniform_real_distribution<double> distribution(0.0, 1.0);
	std::uniform_real_distribution<double> mutator(lower , upper);

	double max_height_penalty;
	double holes_penalty;
	double bumpiness_penalty;

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

	// Apply mutation
	max_height_penalty *= mutator(device);
	holes_penalty *= mutator(device);
	bumpiness_penalty *= mutator(device);

	return Solution{ max_height_penalty, holes_penalty, bumpiness_penalty, 0 };
}


void Trainer::sortSolutions() {
	std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs) {return lhs.fitness_score > rhs.fitness_score; });
}
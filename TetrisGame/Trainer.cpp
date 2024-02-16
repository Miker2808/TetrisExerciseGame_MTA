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
		//debug
		gotoxy(0, 2);
		std::cout << "progress: "<< ((solution_ittrator)*100/ (SOL_NUM) ) << "%" << "\n";
		solution_ittrator++;
		//debug over
		s.fit();
	}
}

void Trainer::logSolutions() {
	std::string filename = "generation_" + std::to_string(gen_number) + "_top_solutions.txt";
	std::ofstream of(filename);

	if (of.is_open()) {
		// Iterate over the top solutions and write their information to the file
		for (int i = 0; i < logged_samples_per_generation && i < solutions.size(); ++i) {
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

void Trainer::mutateSamples() {
	std::uniform_real_distribution<double> mutator(0.9, 1.1);
	double rate = 0.9 + MUT_RATE / 5;

	std::for_each(sample.begin(), sample.end(), [&](auto& s) {
		if (mutator(device) < rate) {
			s.max_height_penality *= mutator(device);
			s.holes_penality *= mutator(device);
			s.bumpiness_penality *= mutator(device);
		}
		});
}


void Trainer::crossSolutions() {
	std::uniform_int_distribution<int> cross(0, SAMPLE_SIZE - 1);
	std::uniform_real_distribution<double> distribution(0, 1);

	gen_number++;
	double totalFitness = calculateTotalFitness();

	for (int i = 0; i < SOL_NUM; i++) {
		double randNum = distribution(device);
		Solution parent = selectParentForCrossover(randNum, totalFitness);
		if (randNum < CROSS_RATE) {
			Solution otherParent = sample[cross(device)];
			Solution offspring = performCrossover(parent, otherParent);
			solutions.push_back(offspring);
		}
		else {
			solutions.push_back(parent);
		}
	}
	sample.clear();
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
	// Default return if no parent is selected (should not happen)
	return sample[0];
}

Solution Trainer::performCrossover(const Solution& parent1, const Solution& parent2) {
	std::uniform_real_distribution<double> mutator(0.95, 1.05);
	double max_height_penality = ((parent1.max_height_penality + parent2.max_height_penality) * mutator(device)) / 2.0;
	double holes_penality = ((parent1.holes_penality + parent2.holes_penality) * mutator(device)) / 2.0;
	double bumpiness_penality = ((parent1.bumpiness_penality + parent2.bumpiness_penality) * mutator(device)) / 2.0;
	return Solution{max_height_penality, holes_penality, bumpiness_penality, 0 };
}

void Trainer::sortSolutions() {
	std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs) {return lhs.fitness_score > rhs.fitness_score; });
}
#include "Trainer.h"




void Trainer::generateStartingBach() {
	std::uniform_real_distribution<double> unif(0, 1);
	for (int i = 0; i < SOL_NUM; i++)
		solutions.push_back(Solution{ unif(device), unif(device), unif(device), unif(device), 0 });
}

void Trainer::fitSolutions() {
	gotoxy(0, 1);
	std::cout << "Generation number: " << gen_number ;
	int solution_ittrator = 0;
	for (auto& s : solutions) {
		//debug
		gotoxy(0, 2);
		std::cout << "progress: "<< (solution_ittrator/ (SOL_NUM/100)) << "%" << "\n";
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
				<< "Height penalty: " << s.height_penalty << '\n'
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
		solutions.begin() + gen_sample_size,
		std::back_inserter(sample));

	solutions.clear();
};

void Trainer::mutateSamples() {
	std::uniform_real_distribution<double> mutator(0.9, 1.1);
	std::for_each(sample.begin(), sample.end(), [&](auto& s) {
		s.height_penalty *= mutator(device);
		s.max_height_penality *= mutator(device);
		s.holes_penality *= mutator(device);
		s.bumpiness_penality *= mutator(device);
		});
}


void Trainer::crossSolutions() {
	std::uniform_int_distribution<int> cross(0, gen_sample_size - 1);

	gen_number++;
	for (int i = 0; i < SOL_NUM; i++)
		solutions.push_back(Solution{
		sample[cross(device)].height_penalty,
		sample[cross(device)].max_height_penality,
		sample[cross(device)].holes_penality,
		sample[cross(device)].bumpiness_penality,
		0
			});
}


void Trainer::sortSolutions() {
	std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs) {return lhs.fitness_score > rhs.fitness_score; });
}
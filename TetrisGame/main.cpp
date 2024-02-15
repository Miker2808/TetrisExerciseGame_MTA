#include "MultiplayerTetris.h"
#include "Trainer.h"

Settings global_settings;

int main()
{
	Trainer trainer;
	trainer.generateStartingBach();
	while (true) {
		trainer.fitSolutions();
		trainer.sortSolutions();
		trainer.logSolutions();
		trainer.sampleSolutions();
		trainer.mutateSamples();
		trainer.crossSolutions();
	}


}


//int debug = 0;
////create solutions
//std::random_device device;
//std::uniform_real_distribution<double> unif(0, 1);
//std::vector<Solution> solutions;
//std::vector<Solution> sample;
//const int SOL_NUM = 1000;
//const int GEN_SAMPLE_SIZE = 100;
////init the solutions vector
//std::cout << "init solutions" << "\n";
//for (int i = 0; i < SOL_NUM; i++)
//	solutions.push_back(Solution{ unif(device), unif(device), unif(device), unif(device), 0 });
//std::cout << "fitting" << "\n";

////fit the starting solutions
//for (auto& s : solutions) {
//	std::cout << "sol: " << debug << "\n";
//	debug++;
//	s.fit();
//	gotoxy(0, 2);
//}

////sort the solutions by score
//std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs) {return lhs.fitness_score > rhs.fitness_score; });

////log the solutions
//std::for_each(solutions.begin(), solutions.begin() + 10, [](const auto& s) {
//	std::cout << std::fixed
//		<< "score: " << s.fitness_score
//		<< " heig_p: " << s.height_penalty
//		<< " m_heig_p: " << s.max_height_penality
//		<< " holes_p: " << s.holes_penality
//		<< "bump_p: " << s.bumpiness_penality << "\n";
//	});

////get a sample of the top 100 solutions 
//std::copy(
//	solutions.begin(),
//	solutions.begin() + GEN_SAMPLE_SIZE,
//	std::back_inserter(sample));

//solutions.clear();

//std::uniform_real_distribution<double> mutator(0.9, 1.1);

////mutate each of the 100 solutions by 10%
//std::for_each(sample.begin(), sample.end(), [&](auto& s) {
//	s.height_penalty *= mutator(device);
//	s.max_height_penality *= mutator(device);
//	s.holes_penality *= mutator(device);
//	s.bumpiness_penality *= mutator(device);
//	});

////crossover 
////create 1000 from 100 solutions
////100^4 variants possible
//std::uniform_real_distribution<int> cross(0, GEN_SAMPLE_SIZE - 1);

//for (int i = 0; i < SOL_NUM; i++)
//	solutions.push_back(Solution{
//	sample[cross(device)].height_penalty,
//	sample[cross(device)].max_height_penality,
//	sample[cross(device)].holes_penality,
//	sample[cross(device)].bumpiness_penality,
//	0
//		});


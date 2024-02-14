#include "MultiplayerTetris.h"
#include "solution.h"

Settings global_settings;

int main()
{
	int debug = 0;
	//create solutions
	std::random_device device;
	std::uniform_real_distribution<double> unif(0, 1);
	std::vector<Solution> solutions;
	const int solution_number = 10;
	//init the solutions vector
	std::cout << "init solutions" << "\n";
	for (int i = 0; i < solution_number; i++)
		solutions.push_back(Solution{ unif(device), unif(device), unif(device), unif(device), 0 });
	std::cout << "fitting" << "\n";
	for (auto& s : solutions) {
		std::cout << "sol: " << debug << "\n";
		debug++;
		s.fit();
		gotoxy(0, 3);
	}

	
	std::sort(solutions.begin(), solutions.end(), [](const auto& lhs, const auto& rhs) {return lhs.fitness_score > rhs.fitness_score; });

	//log the solutions
	std::for_each(solutions.begin(), solutions.begin() + 10, [](const auto& s) {
		std::cout << std::fixed
			<< "score: " << s.fitness_score
			<< "h_p: " << s.height_penalty
			<< "mh_p: " << s.max_height_penality
			<< "bump_p: " << s.bumpiness_penality << "\n";
		});


}

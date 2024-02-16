#pragma once
#include "MultiplayerTetris.h"
#include "solution.h"
#include "Utility.h"

class Trainer{
	const int SOL_NUM = 200;
	const int SAMPLE_SIZE = 50;
	const int SIMULATIONS_PER_SOLUTION = 10;
	const int NUM_OF_LOGGED_TOP_SOLUTIONS = 20;
	const double SINGLE_SOLUTION_MUTATION_PRECENT = 15;
	const double CROSSOVER_MUTATION_PRECENT = 5;
	const double CROSS_RATE = 0.95;
	const double PARTIAL_RESTART_RATE = 0.2;
	const int RESTARTED_POP = SOL_NUM * PARTIAL_RESTART_RATE;

	std::random_device device;

	std::vector<Solution> solutions;
	std::vector<Solution> sample;

public:
	int gen_number = 0;
	void generateStartingBach();
	void fitSolutions();
	void sortSolutions();
	void logSolutions();
	void sampleSolutions();
	Solution makeMutatedCopy(Solution s);
	void crossSolutions();
	void partialRestart();
	double calculateTotalFitness();
	Solution selectParentForCrossover(double randNum, double totalFitness);
	Solution performCrossover(const Solution& parent1, const Solution& parent2);

};




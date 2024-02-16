#pragma once
#include "MultiplayerTetris.h"
#include "solution.h"
#include "Utility.h"

class Trainer{
	const int SOL_NUM = 20;
	const int SAMPLE_SIZE = 10;
	const int SIMULATIONS_PER_SOLUTION = 10;
	const int NUM_OF_LOGGED_TOP_SOLUTIONS = 10;
	const double SINGLE_SOLUTION_MUTATION_PRECENT = 5;
	const double CROSSOVER_MUTATION_PRECENT = 10;
	const double CROSS_RATE = 0.9;

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
	void mutateSolution(Solution* s);
	void crossSolutions();
	double calculateTotalFitness();
	Solution selectParentForCrossover(double randNum, double totalFitness);
	Solution performCrossover(const Solution& parent1, const Solution& parent2);
	void loadSample();

};




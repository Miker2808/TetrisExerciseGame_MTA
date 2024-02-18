#pragma once
#include "MultiplayerTetris.h"
#include "solution.h"
#include "Utility.h"

class Trainer{

	// Population size: Number of solutions in each generation
	const int SOL_NUM = 200;
	// Sample size: Number of solutions sampled for mutation and crossover operations
	const int SAMPLE_SIZE = 40;
	// Number of simulations per solution for fitness evaluation
	const int SIMULATIONS_PER_SOLUTION = 10;
	// Number of top solutions logged to a file
	const int NUM_OF_LOGGED_TOP_SOLUTIONS = 20;
	// Mutation rate for single solution
	const double SINGLE_SOLUTION_MUTATION_PRECENT = 1;
	// Mutation rate for crossover
	const double CROSSOVER_MUTATION_PRECENT = 1;
	// Crossover rate
	const double CROSS_RATE = 0.95;
	// Partial restart rate
	const double PARTIAL_RESTART_RATE = 0.05;
	// Number of restarted population
	const int RESTARTED_POP = SOL_NUM * PARTIAL_RESTART_RATE;

	// Random device for generating random numbers
	std::random_device device;

	// Vector to store solutions
	std::vector<Solution> solutions;
	// Vector to store sampled solutions
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




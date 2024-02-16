#pragma once
#include "MultiplayerTetris.h"
#include "solution.h"
#include "Utility.h"

class Trainer{
	const int SOL_NUM = 20;
	const int SAMPLE_SIZE = 15;
	const int logged_samples_per_generation = 15;
	const double MUT_RATE = 0.3;
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
	void mutateSamples();
	void crossSolutions();
	double calculateTotalFitness();
	Solution selectParentForCrossover(double randNum, double totalFitness);
	Solution performCrossover(const Solution& parent1, const Solution& parent2);
	void loadSample();

};




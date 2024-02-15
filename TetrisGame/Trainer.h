#pragma once
#include "MultiplayerTetris.h"
#include "solution.h"
#include "Utility.h"

class Trainer{
	const int SOL_NUM = 100;
	const int SAMPLE_SIZE = 10;
	const int logged_samples_per_generation = 10;
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
	void loadSample();

};




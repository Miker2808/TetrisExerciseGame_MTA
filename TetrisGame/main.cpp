#include "MultiplayerTetris.h"
#include "Trainer.h"

Settings global_settings;

int main()
{
	srand((unsigned int)time(NULL));
	Trainer trainer;
	trainer.generateStartingBach();
	while (true) {
		trainer.fitSolutions();
		trainer.sortSolutions();
		trainer.logSolutions();
		trainer.sampleSolutions();
		trainer.crossSolutions();
		trainer.partialRestart();
	}
}

//example on how to use Solution::generateStats:
//Solution sln = { 0.949676, 0.821943, 0.402855, 0.570584 };
//sln.generateStats(1000, true);
//TODO:print the stats from sln

//example on how to use Trainer:
//Trainer trainer;
//trainer.generateStartingBach();
//while (true) {
//	trainer.fitSolutions();
//	trainer.sortSolutions();
//	trainer.logSolutions();
//	trainer.sampleSolutions();
//	trainer.crossSolutions();
//	trainer.partialRestart();
//}
//TODO:find a stop contition for while loop

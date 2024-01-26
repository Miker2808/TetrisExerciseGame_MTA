#pragma once
#include "TetrisGame.h"
#include "Settings.h"

class HeuristicsExplorer
{

public:

	int getColumnHeight(TetrisBoard* board, const int x);
	std::vector<int> boardHeights(TetrisBoard* board);
	std::vector<int> boardHoles(TetrisBoard* board);
	int getColumnHoles(TetrisBoard* board, const int x);
	int chooseMove(const TetrisGame& game);
};


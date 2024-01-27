#pragma once
#include "TetrisGame.h"
#include "Settings.h"

class HeuristicsExplorer
{

public:

	static int getColumnHeight(TetrisBoard* board, const int x);
	static std::vector<int> boardHeights(TetrisBoard* board);
	static std::vector<int> boardHoles(TetrisBoard* board);
	static int getColumnHoles(TetrisBoard* board, const int x);
	static std::vector<int> chooseMove(const TetrisGame & game);
};


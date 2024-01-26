#pragma once
#include "TetrisGame.h"
#include "Settings.h"

class HeuristicsExplorer
{

public:
	//int bestColumnScore(const TetrisBoard& board,const char pieceType);
	int getColumnHeight(TetrisBoard* board, const int x);
	std::vector<int> boardHeights(TetrisBoard* board);
	std::vector<int> boardHoles(TetrisBoard* board);
	int getColumnHoles(TetrisBoard* board, const int x);

};


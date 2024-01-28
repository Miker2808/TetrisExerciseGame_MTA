
#include "TetrisGame.h"
class AITetrisGame :
    public TetrisGame
{
public:
    int best_x = 0; // track best x position to have
    int best_rotation = 0; // track best rotation to have

public:
    AITetrisGame(int start_x, int start_y, bool bombs, bool human_player);
    AITetrisGame(const AITetrisGame& other);
    void play();

    std::vector<int> boardHeights(TetrisBoard* board);
    std::vector<int> boardHoles(TetrisBoard* board);
    int getColumnHeight(TetrisBoard* board, const int x);
    int getColumnHoles(TetrisBoard* board, const int x);
    int calculateHeuristicScore(TetrisBoard* board);
    void estimateBestMove();
    void movementHandler();


};

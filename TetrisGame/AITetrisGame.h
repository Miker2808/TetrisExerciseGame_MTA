
#include "TetrisGame.h"
class AITetrisGame :
    public TetrisGame
{
    int best_x = 0; // track best x position to have
    int best_rotation = 0; // track best rotation to have
    
    int getBestX();
    int getBestRot();
    void setBestX(int x);
    void setBestRot(int rot);
    std::vector<int> boardHeights(TetrisBoard* board) const;
    std::vector<int> boardHoles(TetrisBoard* board) const;
    int getColumnHeight(TetrisBoard* board, const int x) const;
    int getColumnHoles(TetrisBoard* board, const int x) const;
    int calculateHeuristicScore(TetrisBoard* board) const;
    void estimateBestMove();
    void movementHandler();

public:
    AITetrisGame(int start_x, int start_y, bool bombs, bool human_player);
    AITetrisGame(const AITetrisGame& other);
    void play();

    

    


};

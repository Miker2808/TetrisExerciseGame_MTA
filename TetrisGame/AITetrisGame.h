
#include "TetrisGame.h"
class AITetrisGame :
    public TetrisGame
{
    
    const unsigned int height_penalty = 0;
    const double max_height_penality = 1.4;
    const unsigned int holes_penality = 100;
    const unsigned int bumpiness_penality = 10;

    int best_x = 0; // track best x position to have
    int best_rotation = 0; // track best rotation to have
    static constexpr size_t playable_width = Settings::DEFAULT_BOARD_WIDTH - 2;

    int getBestX();
    int getBestRot();
    void setBestX(int x);
    void setBestRot(int rot);
    unsigned int getBoardHeightSum(TetrisBoard* board, unsigned int& maximum) const;
    int getColumnBumpiness(TetrisBoard* board, const int x) const;
    unsigned int getBoardBumpinessSum(TetrisBoard* board) const;
    int getColumnHeight(TetrisBoard* board, const int x) const;
    int getColumnHoles(TetrisBoard* board, const int x) const;
    unsigned int getBoardHolesSum(TetrisBoard* board) const;
    int calculateHeuristicScore(TetrisBoard* board) const;
    void estimateBestMove();
    void movementHandler();

public:
    AITetrisGame(int start_x, int start_y, bool bombs, bool human_player);
    AITetrisGame(const AITetrisGame& other);
    void play();

    

    


};

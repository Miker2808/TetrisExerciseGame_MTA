
#include "TetrisGame.h"
class AITetrisGame :
    public TetrisGame
{
    
    double height_penalty = 0;
    double max_height_penality = 0.5;
    double holes_penality = 0.100;
    double bumpiness_penality = 0.010;

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
    double calculateHeuristicScore(TetrisBoard* board) const;
    void estimateBestMove();
    void movementHandler();

public:
    AITetrisGame(int start_x, int start_y, bool bombs, bool human_player);
    AITetrisGame(const AITetrisGame& other);
    AITetrisGame();
    void play(unsigned char curr_key);
    void setAIWeights(double height_penalty , double max_height_penality, double holes_penality, double bumpiness_penality);

    

    


};


#include "TetrisGame.h"
class AITetrisGame :
    public TetrisGame
{
    TetrisAIProfile profile;

    int best_x = 0; // track best x position to have
    int best_rotation = 0; // track best rotation to have
    static constexpr size_t playable_width = Settings::DEFAULT_BOARD_WIDTH - 2;
    static constexpr size_t playable_height = Settings::DEFAULT_BOARD_HEIGHT - 2;

    int getBestX();
    int getBestRot();
    void setBestX(int x);
    void setBestRot(int rot);
    unsigned int getBoardMaxHeight(TetrisBoard* board) const;
    int getColumnBumpiness(TetrisBoard* board, const int x) const;
    unsigned int getBoardBumpinessSum(TetrisBoard* board) const;
    int getColumnHeight(TetrisBoard* board, const int x) const;
    int getColumnHoles(TetrisBoard* board, const int x) const;
    unsigned int getBoardHolesSum(TetrisBoard* board) const;
    double calculateHeuristicScore(TetrisBoard* board, int lines_cleard) const;
    void estimateBestMove();
    void movementHandler();

public:
    AITetrisGame(int start_x, int start_y, bool bombs, bool human_player, TetrisAIProfile ai_profile);
    AITetrisGame(const AITetrisGame& other);
    void play(unsigned char curr_key);
    void setAIWeights(double max_height_penality, double holes_penality, double bumpiness_penality, double lines_reward);
    

    


};


#include "TetrisGame.h"

class AITetrisGame :
    public TetrisGame
{
    // Stores the profile of the Tetris AI
    TetrisAIProfile profile;

    // Tracks the best x position and rotation to have
    int best_x = 0;
    int best_rotation = 0;

    // Constants defining the playable width and height of the game board
    static constexpr size_t playable_width = Settings::DEFAULT_BOARD_WIDTH - 2;
    static constexpr size_t playable_height = Settings::DEFAULT_BOARD_HEIGHT - 2;

    // Private member functions
    
    void setBestX(int x);
    void setBestRot(int rot);
    void estimateBestMove();
    void movementHandler(unsigned char curr_key) override;

public:
    AITetrisGame(int start_x, int start_y, bool bombs, bool human_player, TetrisAIProfile ai_profile);
    AITetrisGame(const AITetrisGame& other);
    ~AITetrisGame();

    void play(unsigned char curr_key) override;

    int getColumnBumpiness(TetrisBoard* board, const int x) const;
    int getColumnHeight(TetrisBoard* board, const int x) const;
    int getColumnHoles(TetrisBoard* board, const int x) const;
    unsigned int getBoardBumpinessSum(TetrisBoard* board) const;
    unsigned int getBoardMaxHeight(TetrisBoard* board) const;
    unsigned int getBoardHolesSum(TetrisBoard* board) const;
    double calculateHeuristicScore(TetrisBoard* board, int lines_cleard) const;
    int getBestX() const;
    int getBestRot() const;

};

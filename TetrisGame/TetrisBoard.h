#pragma once
#include "Utility.h"

extern Settings global_settings;

class TetrisBoard {

// hidden members, use getters and setters instead
	const int board_start_x; // X offset from console edge of board location
	const int board_start_y;  // Y offset from console edge of board location
	const size_t board_width;
	const size_t board_height;
	std::array<std::array<unsigned char, Settings::DEFAULT_BOARD_WIDTH>, Settings::DEFAULT_BOARD_HEIGHT> board;

// methods
public:
	explicit TetrisBoard(
		int pos_x = 0,
		int pos_y = 0,
		size_t width = Settings::DEFAULT_BOARD_WIDTH,
		size_t height = Settings::DEFAULT_BOARD_HEIGHT
		);
	TetrisBoard(const TetrisBoard&);
	~TetrisBoard();

	void printBoard() const;
	void writeCellToBoard(int x_coor, int y_coor, char cell_contents);
	int getBoardStartX() const;
	int getBoardStartY() const;
	int getBoardWidth() const;
	int getBoardHeight() const;
	char getBoardCell(int x, int y) const;
	bool isALine(int y_coor) const;
	void destroyLine(int y_coor);
	void shiftBoardDown(int y_shift);
	void blowUpBomb(int x, int y);

private:
	void printTetrisColor(char c, HANDLE& hConsole) const;
	void printBoardColor() const;
	void printBoardBNW() const;
	void initializeBoard();
	void boardBombShift(int x, int y);
	void shiftCol(int col);

};



#pragma once
#include "Pieces.h"

class Board
{
	Piece * board[8][8];
	int player = Piece::COLOR_WHITE;

public:
	static const int MAX_ROWS = 8;
	static const int MAX_COLUMNS = 8;

public:
	Board();
	~Board();
	Piece * getPieceAt(Position);
	void movePieceTo(Position, Position);
	bool isInRange(Position);
	bool isValidPosition(Position);
	int getCurrentPlayer();
	void setCurrentPlayer(int);
};


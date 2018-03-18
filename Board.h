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
	Piece * getPieceAt(Position position);
	void movePieceTo(Position currentPosition, Position newPosition);
	bool isInRange(Position position);
	bool isValidPosition(Position position);
	int getCurrentPlayer();
	void setCurrentPlayer(int color);
};


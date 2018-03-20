#pragma once
#include "Pieces.h"

class Board
{
	Piece * board[8][8];
	int currentPlayer = Piece::COLOR_WHITE;
	Position whiteKingPosition = Position(7, 4);
	Position blackKingPosition = Position(0, 4);

public:
	static const int MAX_ROWS = 8;
	static const int MAX_COLUMNS = 8;

public:
	Board();
	~Board();

	Piece * getPieceAt(Position position);
	void setPieceAt(Position position, Piece * piece);
	bool containsPieceAt(Position position);
	void movePiece(Position currentPosition, Position destinationPosition);

	bool isInRange(Position position);
	bool isInCheck(int playerColor);
	bool isCheckMate(int playerColor);

	int getCurrentPlayer();
	void setCurrentPlayer(int color);
};


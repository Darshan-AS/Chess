#pragma once
#include "Pieces.h"

class ChessBoard
{
	Piece * board[8][8];

public:
	ChessBoard();
	~ChessBoard();
	int getRowSize();
	int getColumnSize();
	Piece * getPieceAt(int, int);
	void movePieceTo(int, int, int, int);
};


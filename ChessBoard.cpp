#include "stdafx.h"
#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
	board[0][0] = new Pawn(Piece::COLOR_WHITE);
}

ChessBoard::~ChessBoard()
{
}

int ChessBoard::getRowSize()
{
	return sizeof(board) / sizeof(board[0]) ;
}

int ChessBoard::getColumnSize()
{
	return sizeof(board[0]) / sizeof(int);
}

Piece * ChessBoard::getPieceAt(int row, int column)
{
	return board[row][column];
}

void ChessBoard::movePieceTo(int currentRow, int currentColumn, int newRow, int newColumn)
{
	board[newRow][newColumn] = getPieceAt(currentRow, currentColumn);
	board[currentRow][currentColumn] = 0;
}

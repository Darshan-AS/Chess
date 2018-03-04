#include "stdafx.h"
#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
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

int ChessBoard::getPieceAt(int row, int column)
{
	return board[row][column];
}

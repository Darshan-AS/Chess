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

Piece * ChessBoard::getPieceAt(Position position)
{
	return board[position.getRow()][position.getColumn()];
}

void ChessBoard::movePieceTo(Position currentPosition, Position newPosition)
{
	board[newPosition.getRow()][newPosition.getColumn()] = getPieceAt(currentPosition);
	board[currentPosition.getRow()][currentPosition.getColumn()] = 0;
}

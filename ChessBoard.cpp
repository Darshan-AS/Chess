#include "stdafx.h"
#include "ChessBoard.h"


ChessBoard::ChessBoard()
{
	board[0][0] = new Rook(Piece::COLOR_BLACK);
	board[0][1] = new Knight(Piece::COLOR_BLACK);
	board[0][2] = new Bishop(Piece::COLOR_BLACK);
	board[0][3] = new Queen(Piece::COLOR_BLACK);
	board[0][4] = new King(Piece::COLOR_BLACK);
	board[0][5] = new Bishop(Piece::COLOR_BLACK);
	board[0][6] = new Knight(Piece::COLOR_BLACK);
	board[0][7] = new Rook(Piece::COLOR_BLACK);

	board[1][0] = new Pawn(Piece::COLOR_BLACK);
	board[1][1] = new Pawn(Piece::COLOR_BLACK);
	board[1][2] = new Pawn(Piece::COLOR_BLACK);
	board[1][3] = new Pawn(Piece::COLOR_BLACK);
	board[1][4] = new Pawn(Piece::COLOR_BLACK);
	board[1][5] = new Pawn(Piece::COLOR_BLACK);
	board[1][6] = new Pawn(Piece::COLOR_BLACK);
	board[1][7] = new Pawn(Piece::COLOR_BLACK);

	board[6][0] = new Pawn(Piece::COLOR_WHITE);
	board[6][1] = new Pawn(Piece::COLOR_WHITE);
	board[6][2] = new Pawn(Piece::COLOR_WHITE);
	board[6][3] = new Pawn(Piece::COLOR_WHITE);
	board[6][4] = new Pawn(Piece::COLOR_WHITE);
	board[6][5] = new Pawn(Piece::COLOR_WHITE);
	board[6][6] = new Pawn(Piece::COLOR_WHITE);
	board[6][7] = new Pawn(Piece::COLOR_WHITE);

	board[7][0] = new Rook(Piece::COLOR_WHITE);
	board[7][1] = new Knight(Piece::COLOR_WHITE);
	board[7][2] = new Bishop(Piece::COLOR_WHITE);
	board[7][3] = new Queen(Piece::COLOR_WHITE);
	board[7][4] = new King(Piece::COLOR_WHITE);
	board[7][5] = new Bishop(Piece::COLOR_WHITE);
	board[7][6] = new Knight(Piece::COLOR_WHITE);
	board[7][7] = new Rook(Piece::COLOR_WHITE);
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
	return sizeof(board[0]) / sizeof(Piece *);
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

#include "stdafx.h"
#include "Pieces.h"
#include "Board.h"

Position::Position()
{
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

Position::~Position()
{
}

int Position::getRow()
{
	return x;
}

int Position::getColumn()
{
	return y;
}



Piece::Piece()
{
}

Piece::~Piece()
{
}

int Piece::getColor()
{
	return color;
}

void Piece::addAlong(Board board, Position currentPosition, int stepRow, int stepColumn)
{
	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();
	Position newPosition;

	newPosition = Position(currentRow + stepRow, currentColumn + stepColumn);
	while (board.isInRange(newPosition) && board.isValidPosition(newPosition))
	{
		validMoves.push_back(newPosition);
		newPosition = Position(newPosition.getRow() + stepRow, newPosition.getColumn() + stepColumn);
	}
	if (board.isInRange(newPosition) && board.getPieceAt(newPosition)->getColor() != color)
		validMoves.push_back(newPosition);
}



Pawn::Pawn(int color)
{
	this->color = color;
}

Pawn::~Pawn()
{
}

vector<Position> Pawn::getValidMoves(Board board, Position currentPosition)
{
	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();
	Position newPosition;
	int row, column;
	if (this->color == COLOR_BLACK)
	{
		if (currentRow == 1)
		{
			newPosition = Position(currentRow + 2, currentColumn);
			validateAdd(board, newPosition);
		}
		row = currentRow + 1;
	}
	else if (this->color == COLOR_WHITE)
	{
		if (currentRow == 6)
		{
			newPosition = Position(currentRow - 2, currentColumn);
			validateAdd(board, newPosition);
		}
		row = currentRow - 1;
	}

	for (column = currentColumn - 1; column <= currentColumn + 1; column++)
	{
		newPosition = Position(row, column);
		validateAdd(board, newPosition);
	}

	return validMoves;
}

void Pawn::validateAdd(Board board, Position position)
{
	if (board.isInRange(position) && board.isValidPosition(position))
		validMoves.push_back(position);
	else if (board.isInRange(position) && board.getPieceAt(position)->getColor() != this->getColor())
		validMoves.push_back(position);
}



Knight::Knight(int color)
{
	this->color = color;
}


Knight::~Knight()
{
}

vector<Position> Knight::getValidMoves(Board board, Position currentPosition)
{
	return vector<Position>();
}



Bishop::Bishop(int color)
{
	this->color = color;
}

Bishop::~Bishop()
{
}

vector<Position> Bishop::getValidMoves(Board board, Position currentPosition)
{
	addAlong(board, currentPosition, 1, 1);
	addAlong(board, currentPosition, 1, -1);
	addAlong(board, currentPosition, -1, 1);
	addAlong(board, currentPosition, -1, -1);

	return validMoves;
}



Rook::Rook(int color)
{
	this->color = color;
}

Rook::~Rook()
{
}

vector<Position> Rook::getValidMoves(Board board, Position currentPosition)
{
	addAlong(board, currentPosition, 1, 0);
	addAlong(board, currentPosition, 0, 1);
	addAlong(board, currentPosition, -1, 0);
	addAlong(board, currentPosition, 0, -1);

	return validMoves;
}



Queen::Queen(int color)
{
	this->color = color;
}

Queen::~Queen()
{
}

vector<Position> Queen::getValidMoves(Board board, Position currentPosition)
{
	addAlong(board, currentPosition, 1, 1);
	addAlong(board, currentPosition, 1, -1);
	addAlong(board, currentPosition, -1, 1);
	addAlong(board, currentPosition, -1, -1);
	addAlong(board, currentPosition, 1, 0);
	addAlong(board, currentPosition, 0, 1);
	addAlong(board, currentPosition, -1, 0);
	addAlong(board, currentPosition, 0, -1);

	return validMoves;
}



King::King(int color)
{
	this->color = color;
}

King::~King()
{
}

vector<Position> King::getValidMoves(Board board, Position currentPosition)
{
	return vector<Position>();
}
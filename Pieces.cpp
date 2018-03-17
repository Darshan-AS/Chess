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

	if (this->color == COLOR_BLACK)
	{
		if (currentRow == 1)
		{
			newPosition = Position(currentRow + 2, currentColumn);
			validateAdd(board, newPosition);
		}

		newPosition = Position(currentRow + 1, currentColumn);
		validateAdd(board, newPosition);

		newPosition = Position(currentRow + 1, currentColumn + 1);
		validateAdd(board, newPosition);

		newPosition = Position(currentRow + 1, currentColumn - 1);
		validateAdd(board, newPosition);
	}
	else if (this->color == COLOR_WHITE)
	{
		if (currentRow == 6)
		{
			newPosition = Position(currentRow - 2, currentColumn);
			validateAdd(board, newPosition);
		}

		newPosition = Position(currentRow - 1, currentColumn);
		validateAdd(board, newPosition);

		newPosition = Position(currentRow - 1, currentColumn - 1);
		validateAdd(board, newPosition);

		newPosition = Position(currentRow - 1, currentColumn + 1);
		validateAdd(board, newPosition);
	}

	return validMoves;
}

void Pawn::validateAdd(Board board, Position position)
{
	if (board.isValidPosition(position))
		validMoves.push_back(position);
	else if (board.getPieceAt(position)->getColor() != this->getColor())
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
	validateAdd(board, currentPosition, 1, 1);
	validateAdd(board, currentPosition, 1, -1);
	validateAdd(board, currentPosition, -1, 1);
	validateAdd(board, currentPosition, -1, -1);

	return validMoves;
}

void Bishop::validateAdd(Board board, Position currentPosition, int stepRow, int stepColumn)
{
	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();
	Position newPosition;

	newPosition = Position(currentRow + stepRow, currentColumn + stepColumn);
	while (board.isValidPosition(newPosition))
	{
		validMoves.push_back(newPosition);
		newPosition = Position(newPosition.getRow() + stepRow, newPosition.getColumn() + stepColumn);
	}
	if (board.getPieceAt(newPosition)->getColor() != this->getColor())
		validMoves.push_back(newPosition);
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
	return vector<Position>();
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
	return vector<Position>();
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

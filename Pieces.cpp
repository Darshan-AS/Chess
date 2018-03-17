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

void Piece::addPositionAlong(Board board, Position currentPosition, int stepRow, int stepColumn)
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

void Piece::addPositionAt(Board board, Position position)
{
	if (board.isInRange(position) && board.isValidPosition(position))
		validMoves.push_back(position);
	else if (board.isInRange(position) && board.getPieceAt(position)->getColor() != color)
		validMoves.push_back(position);
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
			addPositionAt(board, newPosition);
		}
		newPosition = Position(currentRow + 1, currentColumn);
		addPositionAt(board, newPosition);

		newPosition = Position(currentRow + 1, currentColumn + 1);
		if (board.isInRange(newPosition) && !board.isValidPosition(newPosition) && board.getPieceAt(newPosition)->getColor() != color)
			validMoves.push_back(newPosition);

		newPosition = Position(currentRow + 1, currentColumn - 1);
		if (board.isInRange(newPosition) && !board.isValidPosition(newPosition) && board.getPieceAt(newPosition)->getColor() != color)
			validMoves.push_back(newPosition);
	}
	else if (this->color == COLOR_WHITE)
	{
		if (currentRow == 6)
		{
			newPosition = Position(currentRow - 2, currentColumn);
			addPositionAt(board, newPosition);
		}
		newPosition = Position(currentRow - 1, currentColumn);
		addPositionAt(board, newPosition);

		newPosition = Position(currentRow - 1, currentColumn - 1);
		if (board.isInRange(newPosition) && !board.isValidPosition(newPosition) && board.getPieceAt(newPosition)->getColor() != color)
			validMoves.push_back(newPosition);

		newPosition = Position(currentRow - 1, currentColumn + 1);
		if (board.isInRange(newPosition) && !board.isValidPosition(newPosition) && board.getPieceAt(newPosition)->getColor() != color)
			validMoves.push_back(newPosition);
	}

	return validMoves;
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
	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();
	Position newPosition;

	int stepColumn = 1;
	for (int row = currentRow - 2; row <= currentRow + 2; row++)
	{
		if (row == currentRow)
		{
			stepColumn--;
			stepColumn = -stepColumn;
			continue;
		}
		newPosition = Position(row, currentColumn + stepColumn);
		addPositionAt(board, newPosition);

		newPosition = Position(row, currentColumn - stepColumn);
		addPositionAt(board, newPosition);

		stepColumn++;
	}

	return validMoves;
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
	addPositionAlong(board, currentPosition, 1, 1);
	addPositionAlong(board, currentPosition, 1, -1);
	addPositionAlong(board, currentPosition, -1, 1);
	addPositionAlong(board, currentPosition, -1, -1);

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
	addPositionAlong(board, currentPosition, 1, 0);
	addPositionAlong(board, currentPosition, 0, 1);
	addPositionAlong(board, currentPosition, -1, 0);
	addPositionAlong(board, currentPosition, 0, -1);

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
	addPositionAlong(board, currentPosition, 1, 1);
	addPositionAlong(board, currentPosition, 1, -1);
	addPositionAlong(board, currentPosition, -1, 1);
	addPositionAlong(board, currentPosition, -1, -1);
	addPositionAlong(board, currentPosition, 1, 0);
	addPositionAlong(board, currentPosition, 0, 1);
	addPositionAlong(board, currentPosition, -1, 0);
	addPositionAlong(board, currentPosition, 0, -1);

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
	int currentRow = currentPosition.getRow();
	int currentColumn = currentPosition.getColumn();
	Position newPosition;

	for (int row = currentRow - 1; row <= currentRow + 1; row++)
	{
		for (int column = currentColumn - 1; column <= currentColumn + 1; column++)
		{
			newPosition = Position(row, column);
			addPositionAt(board, newPosition);
		}
	}

	return validMoves;
}
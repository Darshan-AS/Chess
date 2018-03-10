#include "stdafx.h"
#include "Pieces.h"

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

vector<Position> Pawn::getValidMoves(Position)
{
	vector<Position> validMoves;
	Position p(1, 1);
	cout << p.getRow() << p.getColumn();
	validMoves.push_back(p);

	return vector<Position>();
}

#include "stdafx.h"
#include "Pieces.h"
#include "Board.h"

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
	vector<Position> validMoves;
	Position p(1, 1);
	cout << p.getRow() << p.getColumn();
	validMoves.push_back(p);

	return vector<Position>();
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
	return vector<Position>();
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

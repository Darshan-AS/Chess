#include "stdafx.h"
#include "Pieces.h"


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
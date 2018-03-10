#pragma once

class Position
{
	int x;
	int y;
public:
	Position(int, int);
	~Position();
	int getRow();
	int getColumn();
};



class Piece
{
protected:
	int color;

public:
	static const int COLOR_WHITE = 1;
	static const int COLOR_BLACK = 0;

public:
	Piece();
	~Piece();
	int getColor();
	virtual vector<Position> getValidMoves(Position) = 0;
};



class Pawn :
	public Piece
{
public:
	Pawn(int);
	~Pawn();
	vector<Position> getValidMoves(Position);
};



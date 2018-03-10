#pragma once
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
	virtual void getValidMoves(int, int) = 0;
};

class Pawn :
	public Piece
{
public:
	Pawn(int);
	~Pawn();
};


#pragma once
class Board;

class Position
{
	int x;
	int y;
public:
	Position();
	Position(int, int);
	~Position();
	int getRow();
	int getColumn();
};



class Piece
{
protected:
	int color;
	vector<Position> validMoves;

public:
	static const int COLOR_WHITE = 1;
	static const int COLOR_BLACK = 0;

public:
	Piece();
	~Piece();
	int getColor();
	virtual vector<Position> getValidMoves(Board, Position) = 0;
};



class Pawn :
	public Piece
{
public:
	Pawn(int);
	~Pawn();
	vector<Position> getValidMoves(Board, Position);

private:
	void validateAdd(Board, Position);
};



class Knight :
	public Piece
{
public:
	Knight(int);
	~Knight();
	vector<Position> getValidMoves(Board, Position);
};



class Bishop :
	public Piece
{
public:
	Bishop(int);
	~Bishop();
	vector<Position> getValidMoves(Board, Position);

};



class Rook :
	public Piece
{
public:
	Rook(int);
	~Rook();
	vector<Position> getValidMoves(Board, Position);
};



class Queen :
	public Piece
{
public:
	Queen(int);
	~Queen();
	vector<Position> getValidMoves(Board, Position);
};



class King :
	public Piece
{
public:
	King(int);
	~King();
	vector<Position> getValidMoves(Board, Position);
};

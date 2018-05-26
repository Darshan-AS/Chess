#pragma once
class Board;

class Position {
	int x;
	int y;

public:
	Position();
	Position(int x, int y);

	int getRow();
	int getColumn();
	bool equals(Position position);
	string toString();
};



class Piece {

protected:
	int color;
	vector<Position> validMoves;

public:
	static const int COLOR_WHITE = 1;
	static const int COLOR_BLACK = 0;

public:
	Piece();
	int getColor();
	virtual vector<Position> getValidMoves(Board board, Position currentPosition) = 0;
	bool belongsTo(int playerColor);

protected:
	void addPositionAlong(Board board, Position currentPosition, int stepRow, int stepColumn);
	void addPositionAt(Board board, Position position);
};



class Pawn :
	public Piece {

public:
	Pawn(int color);
	~Pawn();
	vector<Position> getValidMoves(Board board, Position currentPosition);

protected:
	void addPositionAt(Board board, Position position);
	void addPositionToCapture(Board board, Position position);
};



class Knight :
	public Piece {

public:
	Knight(int color);
	~Knight();
	vector<Position> getValidMoves(Board board, Position currentPosition);
};



class Bishop :
	public Piece {

public:
	Bishop(int color);
	~Bishop();
	vector<Position> getValidMoves(Board board, Position currentPosition);
};



class Rook :
	public Piece {

public:
	Rook(int color);
	~Rook();
	vector<Position> getValidMoves(Board board, Position currentPosition);
};



class Queen :
	public Piece {

public:
	Queen(int color);
	~Queen();
	vector<Position> getValidMoves(Board board, Position currentPosition);
};



class King :
	public Piece {

public:
	King(int color);
	~King();
	vector<Position> getValidMoves(Board board, Position currentPosition);
};
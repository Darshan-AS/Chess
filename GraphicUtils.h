#pragma once
#include "Board.h"

class GraphicUtils {

	static Position sourcePosition;
	static vector<Position> validMoves;

public:
	static void drawBoard(Board board);
	static void selectPieceAt(Position sourcePosition, vector<Position> validMoves);
	static void deselectPieceAt();

private:
	static void drawPiece(Piece * piece, int x, int z);
	static void drawKing(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawQueen(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawKnight(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawPawn(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawBishop(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawRook(GLfloat x, GLfloat y, GLfloat z, int color);

	static void drawSmoothUnityEllipsoidPatch(float a1, float a2, float b1, float b2);
	static void drawBottom();
};


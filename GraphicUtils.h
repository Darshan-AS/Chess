#pragma once
#include "Board.h"

class GraphicUtils {

public:
	static void drawBoard(Board board);

private:
	static void drawPiece(Piece * piece, int x, int z);
	static void drawKing(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawQueen(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawKnight(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawPawn(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawBishop(GLfloat x, GLfloat y, GLfloat z, int color);
	static void drawRook(GLfloat x, GLfloat y, GLfloat z, int color);

	static void drawSmoothUnityEllipsoidPatch(float a1, float a2, float b1, float b2);
	static void drawQuad(float x, float y, float z, float r);
	static void drawBottom();
};


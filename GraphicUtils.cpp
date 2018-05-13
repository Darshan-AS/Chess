#include "stdafx.h"
#include "GraphicUtils.h"

void GraphicUtils::drawPiece(Piece * piece, int z, int x) {

	if (piece == nullptr)
		return;

	int color = piece->getColor();

	
	if (color == Piece::COLOR_WHITE)
		glColor3ub(250, 235, 215);
	else if (color == Piece::COLOR_BLACK)
		glColor3ub(15, 25, 30);

	if (dynamic_cast<Pawn*>(piece))
		drawPawn(x, 0, z, color);
	else if (dynamic_cast<Knight*>(piece))
		drawKnight(x, 0, z, color);
	else if (dynamic_cast<Bishop*>(piece))
		drawBishop(x, 0, z, color);
	else if (dynamic_cast<Rook*>(piece))
		drawRook(x, 0, z, color);
	else if (dynamic_cast<Queen*>(piece))
		drawQueen(x, 0, z, color);
	if (dynamic_cast<King*>(piece))
		drawKing(x, 0, z, color);

}

void GraphicUtils::drawBoard(Board board) {

	glPushMatrix();
	glTranslatef(3.5, -0.05, 3.5);
	glScalef(1, 0.25 / 10, 1);
	glColor3ub(102, 51, 0);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glScalef(1, 0.25, 1);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			glPushMatrix();
			if (i % 2 == j % 2)
				glColor3f(0.8, 0.8, 0.8);
			else
				glColor3f(0.2, 0.2, 0.2);
			glTranslatef(i, 0, j);
			glutSolidCube(1);
			glPopMatrix();
		}
	}
	glPopMatrix();

	for (int i = 0; i < Board::MAX_ROWS; i++)
		for (int j = 0; j < Board::MAX_COLUMNS; j++)
			drawPiece(board.getPieceAt(Position(i, j)), i , j);

}

struct point {
	float x;
	float y;
	float z;
};

point spherical(float alpha, float beta, float r) {
	point p;
	p.x = r * cos(alpha)*cos(beta);
	p.y = r * sin(alpha)*cos(beta);
	p.z = r * sin(beta);
	return p;
}

struct Points {
	GLfloat x1, x2, x3, x4;
	GLfloat z1, z2, z3, z4;
	GLfloat y1, y2, y3, y4;
	//ChessPiece *who;
};

void GraphicUtils::drawSmoothUnityEllipsoidPatch(float a1, float a2, float b1, float b2)
{
	int na = 32;
	int nb = 16;

	float alpha;
	float dalpha = (a2 - a1) / na;
	float beta;
	float dbeta = (b2 - b1) / nb;

	beta = b2;
	for (int j = 0; j<nb; j++, beta -= dbeta) {
		alpha = a1;
		for (int i = 0; i<na; i++, alpha += dalpha) {
			point p;
			glBegin(GL_POLYGON);

			p = spherical(alpha, beta, 1);
			glNormal3f(p.x, p.y, p.z);
			glVertex3f(p.x, p.y, p.z);

			p = spherical(alpha + dalpha, beta, 1);
			glNormal3f(p.x, p.y, p.z);
			glVertex3f(p.x, p.y, p.z);

			p = spherical(alpha + dalpha, beta - dbeta, 1);
			glNormal3f(p.x, p.y, p.z);
			glVertex3f(p.x, p.y, p.z);

			p = spherical(alpha, beta - dbeta, 1);
			glNormal3f(p.x, p.y, p.z);
			glVertex3f(p.x, p.y, p.z);

			glEnd();
		}
	}
}

void GraphicUtils::drawBottom() {
	glPushMatrix();
	glTranslatef(0.0f, 0.6f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.5, 1.5, 0.8);
	drawSmoothUnityEllipsoidPatch(0, 2 * 3.14, 0, 3.14 / 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 0.9f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.4, 1.4, 1.0);
	drawSmoothUnityEllipsoidPatch(0, 2 * 3.14, 0, 3.14 / 2);
	glPopMatrix();
}

void GraphicUtils::drawKing(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef(x, 0, z);
	glScalef(0.33f, 0.33f, 0.33f);

	// upper sphere
	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.4);
	glutSolidTorus(0.5f, 0.2f, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 5.9f, 0.0f);
	glutSolidSphere(0.34f, 50, 50);
	glTranslatef(0.0f, 0.55f, 0.0f);
	glPushMatrix();
	glScalef(1.0f, 0.2f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glScalef(0.3f, 1.0f, 0.2f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// upper ellipse ring
	glPushMatrix();
	glTranslatef(0.0f, 4.10f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.3);
	glutSolidTorus(0.6f, 0.2f, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.30f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.4f, 0.2f, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.4f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.4f, 0.2f, 40, 40);
	glPopMatrix();

	//  cone
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(1.05f, 5.1f, 50, 50);
	glRotatef(-180, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glutSolidCone(0.7f, 5.6f, 50, 50);
	glPopMatrix();

	// bottom circle
	glPushMatrix();
	glTranslatef(0.0f, 1.3f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	// bottom Ellipsoid
	drawBottom();

	glPopMatrix();
}

void GraphicUtils::drawQueen(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.33f, 0.34f, 0.33f);

	//upper sphere
	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	glScalef(0.4, 0.4, 0.4);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	//upper extrusion
	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	glScalef(0.45, 0.1, 0.45);
	glutSolidDodecahedron();
	glRotated(-90, 0.0f, 1.0f, 0.0f);
	glutSolidDodecahedron();
	glPopMatrix();

	// upper ellipse rings
	glPushMatrix();
	glTranslatef(0.0f, 4.10f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.34);
	glutSolidTorus(0.6f, 0.2f, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.30f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.4f, 0.2f, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.4f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.4f, 0.2f, 40, 40);
	glPopMatrix();

	//  cone
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(1.05f, 5.1f, 50, 50);
	glRotated(-180, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glutSolidCone(0.7f, 5.6f, 50, 50);
	glPopMatrix();

	// bottom circle
	glPushMatrix();
	glTranslatef(0.0f, 1.3f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	// bottom Ellipsoid
	drawBottom();

	glPopMatrix();
}

void GraphicUtils::drawBishop(GLfloat x, GLfloat y, GLfloat z, int color) {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.34f, 0.31f, 0.34f);

	// upper sphere
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glutSolidSphere(.2f, 40, 40);
	glPopMatrix();

	// upper ellipse ring
	glPushMatrix();
	glTranslatef(0.0f, 3.10f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.25);
	glutSolidTorus(0.6f, 0.2f, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 3.1f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.24);
	glutSolidTorus(0.5f, 0.2f, 40, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 3.3f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.4f, 0.2f, 40, 40);
	glPopMatrix();

	//  cone
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.85f, 4.5f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.4f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glScalef(0.48, 0.48, 1.0);
	glutSolidSphere(1, 40, 40);
	glPopMatrix();

	// middle ring
	glPushMatrix();
	glTranslatef(0.0f, 3.71f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.25);
	glutSolidTorus(0.45f, 0.2f, 40, 40);
	glPopMatrix();

	// bottom circle
	glPushMatrix();
	glTranslatef(0.0f, 1.3f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.85f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.7f, 0.3f, 50, 50);
	glPopMatrix();

	drawBottom();
	glPopMatrix();
}

void GraphicUtils::drawRook(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.29f, 0.30f, 0.29f);
	GLUquadricObj * quadratic;

	// topmost cylendar
	glPushMatrix();
	glTranslatef(0.0, 4.0, 0.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCylinder(1.0f, 1.0f, 32, 32);
	glScalef(1.0, 1.0, 0.1);
	glutSolidTorus(0.9f, 0.1f, 50, 50);
	glPopMatrix();

	// top covering
	glPushMatrix();
	glTranslatef(0.0, 5.0, 0.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.1);
	glutSolidTorus(0.9f, 0.1f, 50, 50);
	glPopMatrix();

	// middle cylendar
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	quadratic = gluNewQuadric();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 1.1f, 0.6f, 3.4f, 32, 32);
	glPopMatrix();

	// inverted cylendar
	glPushMatrix();
	glTranslatef(0.0, 4.5, 0.0);
	quadratic = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.85f, 0.55f, 3.4f, 32, 32);
	glPopMatrix();

	// middle covering
	glPushMatrix();
	glTranslatef(0.0, 3.4, 0.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 3.5);
	glutSolidTorus(0.455f, 0.3f, 50, 50);
	glPopMatrix();

	// bottom Ellipsoid
	drawBottom();
	glPopMatrix();
}

void GraphicUtils::drawKnight(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(x, 0, z);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glScalef(0.29f, 0.29f, 0.29f);

	glPushMatrix();
	glTranslatef(0.0f, 4.0f, 0.0f);
	// uff1
	GLfloat tm12 = 0.8f;
	glTranslatef(0, -0.05f, 0);
	glTranslatef(-0.2f, 0.0f, 0.0f);

	glPushMatrix();
	glScalef(0.8, 0.9, 0.8);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.8f, -2.5f, -tm12);
	glVertex3f(0.8f, -2.5f, -tm12);
	glVertex3f(0.4f, -1.2f, -tm12);
	glVertex3f(-0.4f, -0.5f, -tm12);
	glEnd();

	// back face /
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.2f, 0.0f);
	glVertex3f(-0.8f, -2.5f, -tm12);
	glVertex3f(-0.8f, -2.5f, tm12);
	glVertex3f(-0.4f, -0.5f, tm12);
	glVertex3f(-0.4f, -0.5f, -tm12);
	glEnd();

	// front face
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.2f, 0.0f);
	glVertex3f(0.8f, -2.5f, -tm12);
	glVertex3f(0.8f, -2.5f, tm12);
	glVertex3f(0.2f, -0.5f, tm12);
	glVertex3f(0.2f, -0.5f, -tm12);
	glEnd();

	tm12 = -0.8f;

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.8f, -2.5f, -tm12);
	glVertex3f(0.8f, -2.5f, -tm12);
	glVertex3f(0.4f, -1.2f, -tm12);
	glVertex3f(-0.4f, -0.5f, -tm12);
	glEnd();

	tm12 = .8f;

	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.5f, 0.0f);
	glVertex3f(-0.4f, -0.5f, -tm12);
	glVertex3f(1.0f, 1.4f, -tm12);
	glVertex3f(1.0f, 1.4f, tm12);
	glVertex3f(-0.4f, -0.5f, tm12);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1.0f, -0.4f, 0.0f);
	glVertex3f(0.4f, -1.2f, -tm12);
	glVertex3f(1.0f, 1.4f, -tm12);
	glVertex3f(1.0f, 1.4f, tm12);
	glVertex3f(0.4f, -1.2f, tm12);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 1.4f, -tm12);
	glVertex3f(0.4f, -1.2f, -tm12);
	glVertex3f(-0.4f, -0.5f, -tm12);
	glVertex3f(1.0f, 1.4f, -tm12);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.4f, tm12);
	glVertex3f(0.4f, -1.2f, tm12);
	glVertex3f(-0.4f, -0.5f, tm12);
	glVertex3f(1.0f, 1.4f, tm12);
	glEnd();
	// kte1
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.4f, tm12);
	glVertex3f(0.4f, -1.2f, tm12);
	glVertex3f(-0.4f, -0.5f, tm12);
	glVertex3f(1.0f, 1.4f, tm12);
	glEnd();

	// muh
	glPushMatrix();
	//top m
	glBegin(GL_QUADS);
	glNormal3f(0.3f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.4f, tm12);
	glVertex3f(1.0f, 1.4f, -tm12);
	glVertex3f(2.6f, 0.8f, -tm12 + 0.5f);
	glVertex3f(2.6f, 0.8f, tm12 - 0.5f);
	glEnd();
	//bot m
	glBegin(GL_QUADS);
	glNormal3f(-0.2f, -1.0f, 0.0f);
	glVertex3f(0.5f, -0.2f, tm12);
	glVertex3f(0.5f, -0.2f, -tm12);
	glVertex3f(2.6f, 0.4f, -tm12 + 0.5f);
	glVertex3f(2.6f, 0.4f, tm12 - 0.5f);
	glEnd();

	// left m
	glBegin(GL_QUADS);
	glNormal3f(0.2f, 0.0f, -1.0f);
	glVertex3f(0.5f, -0.2f, -tm12);
	glVertex3f(1.0f, 1.4f, -tm12);
	glVertex3f(2.6f, 0.8f, -tm12 + 0.5f);
	glVertex3f(2.6f, 0.4f, -tm12 + 0.5f);
	glEnd();
	// right m
	glBegin(GL_QUADS);
	glNormal3f(0.2f, 0.0f, 1.0f);
	glVertex3f(0.5f, -0.2f, tm12);
	glVertex3f(1.0f, 1.4f, tm12);
	glVertex3f(2.6f, 0.8f, tm12 - 0.5f);
	glVertex3f(2.6f, 0.4f, tm12 - 0.5f);
	glEnd();

	// front dakhan
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(2.6f, 0.4f, -tm12 + 0.5f);
	glVertex3f(2.6f, 0.8f, -tm12 + 0.5f);
	glVertex3f(2.6f, 0.4f, tm12 - 0.5f);
	glVertex3f(2.6f, 0.8f, tm12 - 0.5f);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// bottom Ellipsoid
	// bottom circle
	glPushMatrix();
	glTranslatef(0.0f, 1.6f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(0.86, 0.86, 0.25);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 1.3f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	drawBottom();
	glPopMatrix();
}

void GraphicUtils::drawPawn(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.29 / 1.0f, 0.3 / 1.0f, 0.29 / 1.0f);

	// upper sphere
	GLfloat Pawn_upper_sphere = 4.0f;
	GLfloat Pawn_upper_spherex = 0.0f, Pawn_upper_ring = 3.30f;
	glPushMatrix();
	glTranslatef(0, Pawn_upper_sphere, -Pawn_upper_spherex);
	glutSolidSphere(0.7f, 50, 50);
	glPopMatrix();

	// upper ellipse ring
	glPushMatrix();
	glTranslatef(0, Pawn_upper_ring, -Pawn_upper_spherex);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.2f, 40, 40);
	glPopMatrix();
	glPopMatrix();

	//  cone
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(1.0f, 3.4f, 50, 50);
	glPopMatrix();

	// bottom circle
	glPushMatrix();
	glTranslatef(0.0f, 1.3f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();


	// bottom Ellipsoid
	drawBottom();
	glPopMatrix();
}

void GraphicUtils::drawQuad(float x, float y, float z, float r) {

	// glPushMatrix();

	glBegin(GL_QUADS);
	// glTranslatef(x, y, z);
	//   glColor3f(1.0f, 1.0f, 1.0f);

	// front
	// glNormal3f(0.0f, 0.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(x - 0.5f, y - 0.2f, z + 0.5f);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(x - 0.5f, y + 0.2f, z + 0.5f);
	glNormal3f(0.0f, 1.0f, 1.0f);
	glVertex3f(x + 0.5f, y + 0.2f, z + 0.5f);
	glNormal3f(0.0f, -1.0f, 1.0f);
	glVertex3f(x + 0.5f, y - 0.2f, z + 0.5f);
	//  glColor3f(0.0f, 1.0f, 1.0f);
	// right
	//    glNormal3f(1.0f, 0.0f, 0.0f);
	glNormal3f(1.0f, -1.0f, 0.0f);
	glVertex3f(x + 0.5f, y - 0.2f, z - 0.5f);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(x + 0.5f, y + 0.2f, z - 0.5f);
	glNormal3f(1.0f, 1.0f, 0.0f);
	glVertex3f(x + 0.5f, y + 0.2f, z + 0.5f);
	glNormal3f(1.0f, -1.0f, 0.0f);
	glVertex3f(x + 0.5f, y - 0.2f, z + 0.5f);
	// glColor3f(1.0f, 0.0f, 1.0f);

	// left
	//    glNormal3f(-1.0f, 0.0f, 0.0f);
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(x - 0.5f, y - 0.2f, z - 0.5f);
	glNormal3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(x - 0.5f, y - 0.2f, z + 0.5f);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(x - 0.5f, y + 0.2f, z + 0.5f);
	glNormal3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(x - 0.5f, y + 0.2f, z - 0.5f);

	//  glColor3f(1.0f, 1.0f, 0.0f);

	// back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(x - 0.5f, y - 0.2f, z - 0.5f);
	glVertex3f(x - 0.5f, y + 0.2f, z - 0.5f);
	glVertex3f(x + 0.5f, y + 0.2f, z - 0.5f);
	glVertex3f(x + 0.5f, y - 0.2f, z - 0.5f);

	//glColor3f(1.0f, 0.0f, 0.0f);

	// top
	//    glNormal3f(0.0f, 0.0f, -1.0f);
	glNormal3f(0.0f, -1.0f, -1.0f);
	glVertex3f(x - 0.5f, y + 0.2f, z - 0.5f);
	glNormal3f(-0.0f, 1.0f, -1.0f);
	glVertex3f(x - 0.5f, y + 0.2f, z + 0.5f);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(x + 0.5f, y + 0.2f, z + 0.5f);
	glNormal3f(0.0f, 1.0f, -1.0f);
	glVertex3f(x + 0.5f, y + 0.2f, z - 0.5f);

	Points block[112];
	int counter_block = 1;

	if (counter_block <= 64) {
		int flg = 0;
		//if(counter_block==0)    { flg=1;counter_block=37;}
		if (counter_block == 0) {
			int counter_block1 = 37;
			block[counter_block1].x1 = x - 0.5f; block[counter_block1].x2 = x - 0.5f;
			block[counter_block1].x3 = x + 0.5f; block[counter_block1].x4 = x + 0.5f;
			block[counter_block1].z1 = z - 0.5f; block[counter_block1].z2 = z + 0.5f;
			block[counter_block1].z3 = z + 0.5f; block[counter_block1].z4 = z - 0.5f;
			block[counter_block1].y1 = y + 0.2f; block[counter_block1].y2 = y + 0.2f;
			block[counter_block1].y3 = y + 0.2f; block[counter_block1].y4 = y + 0.2f;
		} else {
			block[counter_block].x1 = x - 0.5f; block[counter_block].x2 = x - 0.5f;
			block[counter_block].x3 = x + 0.5f; block[counter_block].x4 = x + 0.5f;
			block[counter_block].z1 = z - 0.5f; block[counter_block].z2 = z + 0.5f;
			block[counter_block].z3 = z + 0.5f; block[counter_block].z4 = z - 0.5f;
			block[counter_block].y1 = y + 0.2f; block[counter_block].y2 = y + 0.2f;
			block[counter_block].y3 = y + 0.2f; block[counter_block].y4 = y + 0.2f;
		}
		//if(flg==1)  counter_block=0;

		counter_block++;
	}
	// dead posi

	//  glColor3f(0.7f, 0.7f, 0.8f);
	// bottom

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(x - 0.5f, y - 0.2f, z - 0.5f);
	glVertex3f(x - 0.5f, y - 0.2f, z + 0.5f);
	glVertex3f(x + 0.5f, y - 0.2f, z + 0.5f);
	glVertex3f(x + 0.5f, y - 0.2f, z - 0.5f);
	{
		GLfloat x = -4.0f, y = -5.0f, z = -5.0f;

		for (int counter_block1 = 71; counter_block1<90; counter_block1++) {
			if (counter_block1 == 78) { z = z - 0.7f; x = -4.0f; }
			block[counter_block1].x1 = x - 0.5f; block[counter_block1].x2 = x - 0.5f;
			block[counter_block1].x3 = x + 0.5f; block[counter_block1].x4 = x + 0.5f;
			block[counter_block1].z1 = z - 0.5f; block[counter_block1].z2 = z + 0.5f;
			block[counter_block1].z3 = z + 0.5f; block[counter_block1].z4 = z - 0.5f;
			block[counter_block1].y1 = y + 0.2f; block[counter_block1].y2 = y + 0.2f;
			block[counter_block1].y3 = y + 0.2f; block[counter_block1].y4 = y + 0.2f;
			x = x + 0.7f;// y=y+1.0f;
		}

		x = 3.0f; y = -5.0f; z = 4.0f;

		for (int counter_block1 = 91; counter_block1<110; counter_block1++) {
			if (counter_block1 == 98) { z = z + 0.7f; x = 3.0f; }
			block[counter_block1].x1 = x - 0.5f; block[counter_block1].x2 = x - 0.5f;
			block[counter_block1].x3 = x + 0.5f; block[counter_block1].x4 = x + 0.5f;
			block[counter_block1].z1 = z - 0.5f; block[counter_block1].z2 = z + 0.5f;
			block[counter_block1].z3 = z + 0.5f; block[counter_block1].z4 = z - 0.5f;
			block[counter_block1].y1 = y + 0.2f; block[counter_block1].y2 = y + 0.2f;
			block[counter_block1].y3 = y + 0.2f; block[counter_block1].y4 = y + 0.2f;
			x = x - 0.7f;// y=y+1.0f;
		}
	}
	glEnd();

}
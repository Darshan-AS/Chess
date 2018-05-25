#include "stdafx.h"
#include "GraphicUtils.h"

Position GraphicUtils::sourcePosition = Position(-1, -1);
vector<Position> GraphicUtils::validMoves = vector<Position>();

void GraphicUtils::selectPieceAt(Position source, vector<Position> moves) {
	GraphicUtils::sourcePosition = source;
	GraphicUtils::validMoves = moves;
}

void GraphicUtils::deselectPieceAt() {
	GraphicUtils::sourcePosition = Position(-1, -1);
	GraphicUtils::validMoves.clear();
}

void GraphicUtils::drawPiece(Piece * piece, int z, int x) {

	if (piece == nullptr)
		return;

	int color = piece->getColor();

	
	if (color == Piece::COLOR_WHITE)
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4]{ 0.78f, 0.721f, 0.643f, 1.0f });
	else if (color == Piece::COLOR_BLACK)
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4]{ 0.178f, 0.198f, 0.217f, 1.0f });

	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[4]{ 0.5f, 0.5f, 0.5f, 1.0f });
	glMaterialfv(GL_FRONT, GL_SHININESS, new GLfloat[4]{ 100.0f });

	if (dynamic_cast<Pawn * > (piece))
		drawPawn(x, 0, z, color);
	else if (dynamic_cast<Knight * > (piece))
		drawKnight(x, 0, z, color);
	else if (dynamic_cast<Bishop * > (piece))
		drawBishop(x, 0, z, color);
	else if (dynamic_cast<Rook * > (piece))
		drawRook(x, 0, z, color);
	else if (dynamic_cast<Queen * > (piece))
		drawQueen(x, 0, z, color);
	if (dynamic_cast<King * > (piece))
		drawKing(x, 0, z, color);

}

void GraphicUtils::drawBoard(Board board) {
	// Wooden base
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4] { 0.5f, 0.25f, 0.0f, 1.0f });
	glTranslatef(3.5, -0.001, 3.5);
	glScalef(1, 0.25 / 10, 1);
	glutSolidCube(10);
	glPopMatrix();

	// Light Bubble
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4] { 0.5f, 0.5f, 0.5f, 1.0f });
	glMaterialfv(GL_FRONT, GL_SPECULAR, new GLfloat[4]{ 0.5f, 0.5f, 0.5f, 1.0f });
	glMaterialfv(GL_FRONT, GL_SHININESS, new GLfloat[4]{ 100.0f });
	
	if (board.getCurrentPlayer() == Board::PLAYER_WHITE)
		glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[4]{ 0.2f, 0.5f, 0.2f, 1.0f });
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[4]{ 0.3f, 0.32f, 0.3f, 1.0f });
	glTranslatef(3.5, 0.25 / 2, 8);
	glutSolidSphere(0.25, 50, 50);

	if (board.getCurrentPlayer() == Board::PLAYER_BLACK)
		glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[4]{ 0.2f, 0.5f, 0.2f, 1.0f });
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[4]{ 0.3f, 0.32f, 0.3f, 1.0f });
	glTranslatef(0, 0, -9);
	glutSolidSphere(0.25, 50, 50);

	glMaterialfv(GL_FRONT, GL_EMISSION, new GLfloat[4]{ 0.0f, 0.0f, 0.0f, 1.0f });
	glPopMatrix();

	// Black and White Board
	glPushMatrix();
	glScalef(1, 0.25, 1);
	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			glPushMatrix();
			if (row % 2 == column % 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4] { 0.8f, 0.8f, 0.8f, 1.0f });
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4] { 0.3f, 0.3f, 0.3f, 1.0f });
			glTranslatef(column, 0, row);
			glutSolidCube(1);
			glPopMatrix();
		}
	}

	// Valid moves indication
	if (!sourcePosition.equals(Position(-1, -1))) {
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4] { 1.0f, 0.0f, 0.0f, 1.0f });
		glTranslatef(GraphicUtils::sourcePosition.getColumn(), 0.01, GraphicUtils::sourcePosition.getRow());
		glutSolidCube(1);
		glPopMatrix();

		for (int i = 0; i < validMoves.size(); i++) {
			glPushMatrix();
			if (validMoves[i].getRow() % 2 == validMoves[i].getColumn() % 2)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4] { 0.8f, 1.0f, 0.8f, 1.0f });
			else
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new GLfloat[4] { 0.2f, 0.5f, 0.2f, 1.0f });
			glTranslatef(validMoves[i].getColumn(), 0.01, validMoves[i].getRow());
			glutSolidCube(1);
			glPopMatrix();
		}
	}
	
	glPopMatrix();

	// Draw all pieces
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

	// Top sphere
	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.4);
	glutSolidTorus(0.5f, 0.2f, 40, 40);
	glPopMatrix();

	// Top cross
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

	// Middle rings
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

	// Body cones
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(1.05f, 5.1f, 50, 50);
	glRotatef(-180, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glutSolidCone(0.7f, 5.6f, 50, 50);
	glPopMatrix();

	// Bottom circles
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.7f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	// Bottom ellipsoid
	drawBottom();

	glPopMatrix();
}

void GraphicUtils::drawQueen(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.33f, 0.34f, 0.33f);

	// Upper sphere
	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	glScalef(0.4, 0.4, 0.4);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	// Upper extrusion
	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	glScalef(0.45, 0.1, 0.45);
	glutSolidDodecahedron();
	glRotated(-90, 0.0f, 1.0f, 0.0f);
	glutSolidDodecahedron();
	glPopMatrix();

	// Middle rings
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

	// Body cones
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(1.05f, 5.1f, 50, 50);
	glRotated(-180, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glutSolidCone(0.7f, 5.6f, 50, 50);
	glPopMatrix();

	// Bottom circles
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.7f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	// Bottom ellipsoid
	drawBottom();

	glPopMatrix();
}

void GraphicUtils::drawBishop(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.34f, 0.31f, 0.34f);

	// Upper sphere
	glPushMatrix();
	glTranslatef(0.0f, 5.5f, 0.0f);
	glutSolidSphere(.2f, 40, 40);
	glPopMatrix();

	// Upper rings
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

	// Body cones
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

	// Middle ring
	glPushMatrix();
	glTranslatef(0.0f, 3.71f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.25);
	glutSolidTorus(0.45f, 0.2f, 40, 40);
	glPopMatrix();

	// Bottom circles
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.7f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	//Bottom ellipsoid
	drawBottom();

	glPopMatrix();
}

void GraphicUtils::drawRook(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.29f, 0.30f, 0.29f);
	GLUquadricObj * quadratic;

	// Top cylinder
	glPushMatrix();
	glTranslatef(0.0, 4.0, 0.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCylinder(1.0f, 1.0f, 32, 32);
	glScalef(1.0, 1.0, 0.1);
	glutSolidTorus(0.9f, 0.1f, 50, 50);
	glPopMatrix();

	// Top covering
	glPushMatrix();
	glTranslatef(0.0, 5.0, 0.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.1);
	glutSolidTorus(0.9f, 0.1f, 50, 50);
	glPopMatrix();

	// Body cylinders
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	quadratic = gluNewQuadric();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 1.1f, 0.6f, 3.4f, 32, 32);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 4.5, 0.0);
	quadratic = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.85f, 0.55f, 3.4f, 32, 32);
	glPopMatrix();

	// Middle Covering
	glPushMatrix();
	glTranslatef(0.0, 3.4, 0.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 3.5);
	glutSolidTorus(0.455f, 0.3f, 50, 50);
	glPopMatrix();

	// Bottom circles
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.7f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	// Bottom ellipsoid
	drawBottom();

	glPopMatrix();
}

void GraphicUtils::drawKnight(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);
	GLUquadricObj * quadratic;

	glPushMatrix();
	glTranslatef(x, 0, z);
	if (color == Piece::COLOR_WHITE)
		glRotatef(90, 0.0f, 1.0f, 0.0f);
	else if (color == Piece::COLOR_BLACK)
		glRotatef(-90, 0.0f, 1.0f, 0.0f);
	glScalef(0.29f, 0.29f, 0.29f);

	// Body cylinder
	glPushMatrix();
	glTranslatef(0.0, 1.0, 0.0);
	glScalef(1.0f, 1.0f, 0.8f);
	quadratic = gluNewQuadric();
	glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 1.1f, 0.6f, 3.4f, 32, 32);
	glPopMatrix();

	// Face
	glPushMatrix();
	quadratic = gluNewQuadric();
	glTranslatef(-1.0f, 4.4f, 0.0f);
	glScalef(1.0f, 1.0f, 0.6f);
	glRotatef(-10, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, 0.8f, 0.5f, 2.0f, 32, 32);
	glTranslatef(0.0f, 0.0f, 0.2f);
	glutSolidTorus(0.65f, 0.2f, 40, 40);
	glTranslatef(0.0f, 0.0f, 1.7f);
	glutSolidTorus(0.4f, 0.1f, 40, 40);
	glPopMatrix();

	// Bottom circles
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.7f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	// Bottom ellipsoid
	drawBottom();

	glPopMatrix();
}

void GraphicUtils::drawPawn(GLfloat x, GLfloat y, GLfloat z, int color) {
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glTranslatef(x, 0, z);
	glScalef(0.29 / 1.0f, 0.3 / 1.0f, 0.29 / 1.0f);

	// Upper sphere
	GLfloat Pawn_upper_sphere = 4.0f;
	GLfloat Pawn_upper_spherex = 0.0f, Pawn_upper_ring = 3.30f;
	glPushMatrix();
	glTranslatef(0, Pawn_upper_sphere, -Pawn_upper_spherex);
	glutSolidSphere(0.7f, 50, 50);
	glPopMatrix();

	// Upper rings
	glPushMatrix();
	glTranslatef(0, Pawn_upper_ring, -Pawn_upper_spherex);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.2f, 40, 40);
	glPopMatrix();
	glPopMatrix();

	// Body cones
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glutSolidCone(1.0f, 3.4f, 50, 50);
	glPopMatrix();

	// Bottom circles
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(1.0f, 0.3f, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.7f, 0.0f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);
	glScalef(1.0, 1.0, 0.2);
	glutSolidTorus(0.8f, 0.3f, 50, 50);
	glPopMatrix();

	// Bottom ellipsoid
	drawBottom();

	glPopMatrix();
}
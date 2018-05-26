// Chess.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Board.h"
#include <algorithm>
#include "Chess.h"
#include <GL/freeglut.h>
#include "Matrices.h"
#include <cmath>
#include "GraphicUtils.h"

bool isValidSource(Position sourcePosition) {
	Piece * pieceSelected = board.getPieceAt(sourcePosition);

	if (!board.containsPieceAt(sourcePosition) ||
		!pieceSelected->belongsTo(board.getCurrentPlayer()))
		return false;
	
	return true;
}

void switchPlayer() {

	switch (board.getCurrentPlayer()) {

	case Board::PLAYER_WHITE:
		board.setCurrentPlayer(Board::PLAYER_BLACK);
		break;

	case Board::PLAYER_BLACK:
		board.setCurrentPlayer(Board::PLAYER_WHITE);
		break;
	}
}

void displayGameOver() {
	cout << "CHECKMATE!" << "\n\n";

	switch (board.getCurrentPlayer()) {

	case Piece::COLOR_WHITE:
		cout << "Player Black won!" << "\n\n";
		break;

	case Piece::COLOR_BLACK:
		cout << "Player White WON!" << "\n\n";
		break;
	}

	cout << "Type 'quit' to exit the game.\n";

	string temp;
	while (true) {
		cin >> temp;

		if (temp == "quit")
			exit(0);
	}
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 11, 20);
	//glOrtho(-5, 5, -5, 5, 10, 30);
	gluLookAt(3.5, 10, 16, 3.5, 0, 3.5, 0, 1, 0);
	//gluLookAt(3.5, 0, 20, 3.5, 0, 3.5, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void setUpGameWindow() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//glutInitWindowPosition(340, 0);
	//glutInitWindowSize(1200, 1000);
	glutCreateWindow("Chess!");
	glutFullScreen();
}

void switchLightsOn() {

	glLightfv(GL_LIGHT1, GL_POSITION, new GLfloat[4] { 20.0f, 5.0f, 2.0f, 1.0f });
	glLightfv(GL_LIGHT1, GL_DIFFUSE, new GLfloat[4]{ 0.5f, 0.5f, 0.5f, 1.0f });
	glLightfv(GL_LIGHT1, GL_SPECULAR, new GLfloat[4]{ 1.0f, 1.0f, 1.0f, 1.0f });

	glLightfv(GL_LIGHT2, GL_POSITION, new GLfloat[4]{ 3.5f, 1.5f, 3.5f, 1.0f });
	glLightfv(GL_LIGHT2, GL_DIFFUSE, new GLfloat[4]{ 0.1f, 0.1f, 0.1f, 1.0f });
	glLightfv(GL_LIGHT2, GL_SPECULAR, new GLfloat[4]{ 1.0f, 1.0f, 1.0f, 1.0f });

	glLightfv(GL_LIGHT3, GL_POSITION, new GLfloat[4]{ 2.0f, 5.0f, 20.0f, 1.0f });
	glLightfv(GL_LIGHT3, GL_DIFFUSE, new GLfloat[4]{ 0.5f, 0.5f, 0.5f, 1.0f });
	glLightfv(GL_LIGHT3, GL_SPECULAR, new GLfloat[4]{ 1.0f, 1.0f, 1.0f, 1.0f });
}

void drawGame() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	switchLightsOn();

	glPushMatrix();
	GraphicUtils::drawBoard(board);
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

void showGameOver() {
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
}

void onWindowReshape(int w, int h) {
	glViewport(w/2 - h/2, 0, h , h);
	glutPostRedisplay();
}

void onMouseClick(int button, int state, int xCursor, int yCursor) {
	if (state == GLUT_UP)
		return;

	static int input = 0;
	const int SOURCE_POSITION = 0;
	const int DESTINATION_POSITION = 1;

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	// Obtain the Z position (not world coordinates but in range 0 - 1)
	GLfloat z_cursor;
	glReadPixels(xCursor, height - yCursor, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

	// Obtain the world coordinates
	GLdouble x, y, z;
	gluUnProject((double) xCursor, (double) height - yCursor, (double) z_cursor, modelview, projection, viewport, &x, &y, &z);


	int row = (int) z;
	int column = (int) x;
	
	if (z - row >= 0.5)
		row++;

	if (x - column >= 0.5)
		column++;

	static Position sourcePosition, destinationPosition;
	static Piece * pieceSelected;
	static vector<Position> validMoves;

	if (input == SOURCE_POSITION) {
		if (board.isCheckMate(board.getCurrentPlayer())) {
			displayGameOver();
		}

		sourcePosition = Position(row, column);
		if (!board.isInRange(sourcePosition) || !isValidSource(sourcePosition))
			return;
		
		pieceSelected = board.getPieceAt(sourcePosition);
		validMoves = pieceSelected->getValidMoves(board, sourcePosition);
		GraphicUtils::selectPieceAt(sourcePosition, validMoves);

		if (validMoves.size() == 0)
			return;
		
		input = DESTINATION_POSITION;

	} else if (input == DESTINATION_POSITION) {
		
		destinationPosition = Position(row, column);
		if (!board.isInRange(sourcePosition))
			return;

		bool isValidDestination = false;
		for (int i = 0; i < validMoves.size(); i++)
			if (destinationPosition.getRow() == validMoves[i].getRow() && destinationPosition.getColumn() == validMoves[i].getColumn()) {
				isValidDestination = true;
				break;
			}

		if (!isValidDestination)
			return;

		Piece * destinationPiece = board.getPieceAt(destinationPosition);
		board.movePiece(sourcePosition, destinationPosition);

		if (board.isInCheck(board.getCurrentPlayer())) {

			board.movePiece(destinationPosition, sourcePosition);
			board.setPieceAt(destinationPosition, destinationPiece);

			input = SOURCE_POSITION;
			GraphicUtils::deselectPieceAt();
			return;
		}
		switchPlayer();
		input = SOURCE_POSITION;
		GraphicUtils::deselectPieceAt();
	}
}

void onKeyPressed(unsigned char key, int xCursor, int yCursor) {
	
	switch (key) {

	case '1':
		if (glIsEnabled(GL_LIGHT1))
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);
		break;

	case '2':
		if (glIsEnabled(GL_LIGHT2))
			glDisable(GL_LIGHT2);
		else
			glEnable(GL_LIGHT2);
		break;

	case '3':
		if (glIsEnabled(GL_LIGHT3))
			glDisable(GL_LIGHT3);
		else
			glEnable(GL_LIGHT3);
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

int main(int count, char** arguments) {
	glutInit(&count, arguments);

	setUpGameWindow();
	init();

	glutDisplayFunc(drawGame);
	glutMouseFunc(onMouseClick);
	glutKeyboardFunc(onKeyPressed);
	glutReshapeFunc(onWindowReshape);

	glutMainLoop();
	return 0;
}

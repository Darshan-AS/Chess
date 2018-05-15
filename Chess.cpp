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

	if (!board.containsPieceAt(sourcePosition)) {

		//cout << "No Piece found at " << sourcePosition.toString() << "\n\n";
		return false;

	} else if (!pieceSelected->belongsTo(board.getCurrentPlayer())) {

		//cout << "The " << getPieceName(pieceSelected) << " at " << sourcePosition.toString() << " belongs to the opponent.\n\n";
		return false;
	}

	return true;
}

void switchPlayer() {

	switch (board.getCurrentPlayer()) {

	case Piece::COLOR_WHITE:
		board.setCurrentPlayer(Piece::COLOR_BLACK);
		cout << "Player Black's turn\n\n";
		break;

	case Piece::COLOR_BLACK:
		board.setCurrentPlayer(Piece::COLOR_WHITE);
		cout << "Player White's turn\n\n";
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

void setUpGameWindow() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//glutInitWindowPosition(440, 0);
	//glutInitWindowSize(1080, 1080);
	glutCreateWindow("Chess!");

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 12, 20);
	//glOrtho(-5, 5, -5, 5, 10, 30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);
}


void drawGame() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(3.5, 10, 16, 3.5, 0, 3.5, 0, 1, 0);
	//gluLookAt(3.5, 16, 3.5, 3.5, 0, 3.5, 0, 0, -1);

	glPushMatrix();
	GraphicUtils::drawBoard(board);
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}

void onWindowReshape(int w, int h) {
	glViewport(w/2 - h/2, 0, h , h);
	glutPostRedisplay();
}

void onMouseClick(int button, int state, int x_cursor, int y_cursor) {
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

	// obtain the Z position (not world coordinates but in range 0 - 1)
	GLfloat z_cursor;
	glReadPixels(x_cursor, height - y_cursor, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

	// obtain the world coordinates
	GLdouble x, y, z;
	gluUnProject((double) x_cursor, (double) height - y_cursor, (double) z_cursor, modelview, projection, viewport, &x, &y, &z);
	//x += 0.05;
	//z += 0.15;
	cout << z << " " << x << "\n";

	int row = (int) z;
	int column = (int) x;
	
	if (z - row >= 0.5)
		row++;

	if (x - column >= 0.5)
		column++;

	cout << row << " " << column << "\n";

	static Position sourcePosition, destinationPosition;
	static Piece * pieceSelected;
	static vector<Position> validMoves;

	if (input == SOURCE_POSITION) {
		if (board.isInCheck(board.getCurrentPlayer())) {
			if (board.isCheckMate(board.getCurrentPlayer()))
				displayGameOver();
			cout << "CHECK!\n\n";
		}

		sourcePosition = Position(row, column);
		if (!board.isInRange(sourcePosition) || !isValidSource(sourcePosition)) {
			cout << "Position " << sourcePosition.toString() << " is Invalid." << "\n\n";
			return;
		}
		
		pieceSelected = board.getPieceAt(sourcePosition);
		validMoves = pieceSelected->getValidMoves(board, sourcePosition);
		GraphicUtils::select(sourcePosition, validMoves);

		if (validMoves.size() == 0) {
			//cout << "The " << getPieceName(pieceSelected) << " at " << sourcePosition.toString() << " can't move.\n\n";
			return;
		}
		
		input = DESTINATION_POSITION;

	} else if (input == DESTINATION_POSITION) {
		
		destinationPosition = Position(row, column);
		if (!board.isInRange(sourcePosition)) {
			cout << "Position " << destinationPosition.toString() << " is Invalid." << "\n\n";
			return;
		}

		bool isValidDestination = false;
		for (int i = 0; i < validMoves.size(); i++)
			if (destinationPosition.getRow() == validMoves[i].getRow() && destinationPosition.getColumn() == validMoves[i].getColumn()) {
				isValidDestination = true;
				break;
			}

		if (!isValidDestination) {
			cout << "Position " << destinationPosition.toString() << " is not a valid destination\n\n";
			return;
		}

		Piece * destinationPiece = board.getPieceAt(destinationPosition);
		board.movePiece(sourcePosition, destinationPosition);

		if (board.isInCheck(board.getCurrentPlayer())) {

			board.movePiece(destinationPosition, sourcePosition);
			board.setPieceAt(destinationPosition, destinationPiece);

			/*cout << "Moving " << getPieceName(pieceSelected) << " from " << sourcePosition.toString()
				<< " to " << destinationPosition.toString() << " is Invalid." << "\n"
				<< "CHECK not resolved or move leads to CHECK!" << "\n\n";*/
			input = SOURCE_POSITION;

			return;
		}
		switchPlayer();
		input = SOURCE_POSITION;
		GraphicUtils::deselect();
	}
}

int main(int count, char** arguments) {
	glutInit(&count, arguments);

	setUpGameWindow();
	glutFullScreen();
	glutDisplayFunc(drawGame);
	glutMouseFunc(onMouseClick);
	glutReshapeFunc(onWindowReshape);

	glutMainLoop();
	return 0;
}

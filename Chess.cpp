// Chess.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Board.h"
#include <algorithm>
#include "Chess.h"
#include <GL/freeglut.h>
#include "Matrices.h"
#include <cmath>
#include "GraphicUtils.h"

string getPieceName(Piece * piece) {
	string name;

	if (piece == nullptr) {
		name = "-";
		return name;
	} 

	if (dynamic_cast<Pawn*>(piece))
		name = "pawn";
	else if (dynamic_cast<Knight*>(piece))
		name = "knight";
	else if (dynamic_cast<Bishop*>(piece))
		name = "bishop";
	else if (dynamic_cast<Rook*>(piece))
		name = "rook";
	else if (dynamic_cast<Queen*>(piece))
		name = "queen";
	else if (dynamic_cast<King*>(piece))
		name = "king";

	if (piece->belongsTo(Piece::COLOR_WHITE))
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		
	return name;
}

void displayBoard() {
	string name;

	cout << "-------------------------------------------------------------------------------------------------------\n";
	for (int j = 0; j < Board::MAX_COLUMNS; j++)
		cout << "\t" << j;
	cout << "\n\n";

	for (int i = 0; i < Board::MAX_ROWS; i++) {
		cout << " " << i << "\t";

		for (int j = 0; j < Board::MAX_COLUMNS; j++) {
			Piece * piece = board.getPieceAt(Position(i, j));
			name = getPieceName(piece);
			cout << name << "\t";
		}
		cout << "\n\n";
	}

	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << "\n";
}

void displayInstructions() {
	cout << "Welocme to Chess!\n\n";
	cout << "The uppercase pieces represents WHITE and the lowercase represents BLACK.\n";
	cout << "Enter <8 8> as <Row Column> values to quit.\n\n";
}

Position readSourcePosition() {
	int sourceRow, sourceColumn;

	cout << "Which Piece? <Row Column> : ";
	cin >> sourceRow >> sourceColumn;
	cout << "\n";

	if (sourceRow == 8 && sourceColumn == 8)
		exit(0);

	Position sourcePosition = Position(sourceRow, sourceColumn);
	if (!board.isInRange(sourcePosition)) {
		cout << "Position " << sourcePosition.toString() << " is Invalid." << "\n\n";
		readSourcePosition();
	}
	
	return sourcePosition;
}

bool isValidSource(Position sourcePosition) {
	Piece * pieceSelected = board.getPieceAt(sourcePosition);

	if (!board.containsPieceAt(sourcePosition)) {

		cout << "No Piece found at " << sourcePosition.toString() << "\n\n";
		return false;

	} else if (!pieceSelected->belongsTo(board.getCurrentPlayer())) {

		cout << "The " << getPieceName(pieceSelected) << " at " << sourcePosition.toString() << " belongs to the opponent.\n\n";
		return false;
	}

	return true;
}

void displayValidMoves(vector<Position> validMoves) {
	cout << "Valid Moves <Row Column> : ";

	for (int i = 0; i < validMoves.size(); i++)
		cout << validMoves[i].toString() << "    ";
	cout << "\n\n";
}

Position readDestinationPosition(vector<Position> validMoves) {
	int  destinatonRow, destinationColumn;

	cout << "Where to? <Row Column> : ";
	cin >> destinatonRow >> destinationColumn;
	cout << "\n";

	if (destinatonRow == 8 && destinationColumn == 8)
		exit(0);

	Position destinationPosition = Position(destinatonRow, destinationColumn);
	for (int i = 0; i < validMoves.size(); i++)
		if (destinatonRow == validMoves[i].getRow() && destinationColumn == validMoves[i].getColumn())
			return destinationPosition;

	cout << "Position " << destinationPosition.toString() << " is not a valid destination\n\n";
	destinationPosition = readDestinationPosition(validMoves);
	return destinationPosition;
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

//int main() {
//	displayInstructions();
//	displayBoard();
//
//	cout << "Player White's turn.\n\n";
//	Position sourcePosition, destinationPosition;
//	Piece * pieceSelected;
//
//	while (true) {
//
//		if (board.isInCheck(board.getCurrentPlayer())) {
//			if (board.isCheckMate(board.getCurrentPlayer()))
//				displayGameOver();
//			cout << "CHECK!\n\n";
//		}
//
//		sourcePosition = readSourcePosition();
//		if (isValidSource(sourcePosition))
//			pieceSelected = board.getPieceAt(sourcePosition);
//		else
//			continue;
//
//		vector<Position> validMoves = pieceSelected->getValidMoves(board, sourcePosition);
//		if (validMoves.size() == 0) {
//			cout << "The " << getPieceName(pieceSelected) << " at " << sourcePosition.toString() << " can't move.\n\n";
//			continue;
//		}
//		displayValidMoves(validMoves);
//
//		destinationPosition = readDestinationPosition(validMoves);
//		Piece * destinationPiece = board.getPieceAt(destinationPosition);
//		board.movePiece(sourcePosition, destinationPosition);
//
//		if (board.isInCheck(board.getCurrentPlayer())) {
//
//			board.movePiece(destinationPosition, sourcePosition);
//			board.setPieceAt(destinationPosition, destinationPiece);
//
//			cout << "Moving " << getPieceName(pieceSelected) << " from " << sourcePosition.toString()
//				<< " to " << destinationPosition.toString() << " is Invalid." << "\n"
//				<< "CHECK not resolved or move leads to CHECK!" << "\n\n";
//
//			continue;
//		}
//
//		displayBoard();
//		switchPlayer();
//	}
//
//	return 0;
//}

void setUpGameWindow() {
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Chess!");

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-5, 12, -3, 3, 10, 30);
	glFrustum(-5, 5, -5, 5, 10, 30);
	//glOrtho(-2, 9, -2, 9, -2, 10);
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

	//displayInstructions();
	//displayBoard();
	glPushMatrix();
	GraphicUtils::drawBoard(board);
	glPopMatrix();

	//glutSwapBuffers();
	//glFlush();
	//
	//cout << "Player White's turn.\n\n";
	//Position sourcePosition, destinationPosition;
	//Piece * pieceSelected = nullptr;
	//
	////while (true) {
	//
	//	if (board.isInCheck(board.getCurrentPlayer())) {
	//		if (board.isCheckMate(board.getCurrentPlayer()))
	//			displayGameOver();
	//			cout << "CHECK!\n\n";
	//		}
	//
	//	sourcePosition = readSourcePosition();
	//	if (isValidSource(sourcePosition))
	//		pieceSelected = board.getPieceAt(sourcePosition);
	//	else
	//		glutPostRedisplay();
	//		//continue;
	//
	//	vector<Position> validMoves = pieceSelected->getValidMoves(board, sourcePosition);
	//	if (validMoves.size() == 0) {
	//		cout << "The " << getPieceName(pieceSelected) << " at " << sourcePosition.toString() << " can't move.\n\n";
	//		glutPostRedisplay();
	//		//continue;
	//	}
	//	displayValidMoves(validMoves);
	//
	//	destinationPosition = readDestinationPosition(validMoves);
	//	Piece * destinationPiece = board.getPieceAt(destinationPosition);
	//	board.movePiece(sourcePosition, destinationPosition);
	//
	//	if (board.isInCheck(board.getCurrentPlayer())) {
	//
	//		board.movePiece(destinationPosition, sourcePosition);
	//		board.setPieceAt(destinationPosition, destinationPiece);
	//
	//		cout << "Moving " << getPieceName(pieceSelected) << " from " << sourcePosition.toString()
	//			<< " to " << destinationPosition.toString() << " is Invalid." << "\n"
	//			<< "CHECK not resolved or move leads to CHECK!" << "\n\n";
	//		glutPostRedisplay();
	//			//continue;
	//	}
	//
	//	displayBoard();
	//	GraphicUtils::drawBoard(board);
	//	switchPlayer();
	glutSwapBuffers();
	glFlush();
	//}
}

void onWindowReshape(int w, int h) {
	glViewport(0, 0, h * 3, h);
	glutPostRedisplay();
}

int clicks = 0;
void onMouseClick(int button, int state, int x_cursor, int y_cursor) {
	if (state == GLUT_UP)
		return;

	clicks++;
	int width = glutGet(GLUT_WINDOW_WIDTH);

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	// obtain the Z position (not world coordinates but in range 0 - 1)
	GLfloat z_cursor;
	glReadPixels(x_cursor, width - y_cursor, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z_cursor);

	// obtain the world coordinates
	GLdouble x, y, z;
	gluUnProject(x_cursor, width - y_cursor, z_cursor, modelview, projection, viewport, &x, &y, &z);

	int row = (int) z;
	int column = (int) x;

	if (z - row >= 0.5)
		row++;

	if (x - column >= 0.5)
		column++;

	static int sourceRow, sourceColumn;

	if (clicks % 2 == 1) {
		sourceRow = row;
		sourceColumn = column;
	}

	Position sourcePosition = Position(sourceRow, sourceColumn);
	if (!board.isInRange(sourcePosition))
		cout << "Position " << sourcePosition.toString() << " is Invalid." << "\n\n";

	static int  destinatonRow, destinationColumn;

	if (clicks % 2 == 0) {
		destinatonRow = row;
		destinationColumn = column;
	} else {
		return;
	}

	Position destinationPosition = Position(destinatonRow, destinationColumn);

	/*for (int i = 0; i < validMoves.size(); i++)
		if (destinatonRow == validMoves[i].getRow() && destinationColumn == validMoves[i].getColumn())
			return destinationPosition;

	cout << "Position " << destinationPosition.toString() << " is not a valid destination\n\n";*/
	
	Piece * destinationPiece = board.getPieceAt(destinationPosition);
	board.movePiece(sourcePosition, destinationPosition);
}

int main(int count, char** arguments) {
	glutInit(&count, arguments);

	setUpGameWindow();
	//glutFullScreen();
	glutDisplayFunc(drawGame);
	glutMouseFunc(onMouseClick);
	//glutReshapeFunc(onWindowReshape);

	glutMainLoop();
	return 0;
}

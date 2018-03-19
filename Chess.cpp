// Chess.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Board.h"
#include <algorithm>

Board chessBoard;

string getPieceName(Piece * piece) {
	string name;
	if (piece == nullptr)
	{
		name = "-";
		return name;
	} 
	else if (dynamic_cast<Pawn*>(piece))
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

	if (piece->getColor() == Piece::COLOR_WHITE)
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		
	return name;
}

void displayBoard() {
	string name;

	cout << "-------------------------------------------------------------------------------------------------------\n";
	for (int j = 0; j < Board::MAX_COLUMNS; j++)
		cout << "\t" << j;
	cout << "\n\n";
	for (int i = 0; i < Board::MAX_ROWS; i++)
	{
		cout << " " << i << "\t";
		for (int j = 0; j < Board::MAX_COLUMNS; j++)
		{
			Piece * piece = chessBoard.getPieceAt(Position(i, j));
			name = getPieceName(piece);
			cout << name << "\t";
		}
		cout << "\n\n";
	}
	cout << "-------------------------------------------------------------------------------------------------------\n";
	cout << "\n";
}

void displayInstructions()
{
	cout << "Welocme to Chess!\n\n";
	cout << "The Capitalized pieces represents White and the other represents Black.\n";
	cout << "Enter <Row Column> as (8,8) to quit.\n\n";
}

Position readSourcePosition()
{
	int sourceRow, sourceColumn;
	cout << "Which Piece? <Row Column> : ";
	cin >> sourceRow >> sourceColumn;
	cout << "\n";

	if (sourceRow == 8 && sourceColumn == 8)
		exit(0);

	Position sourcePosition = Position(sourceRow, sourceColumn);
	if (!chessBoard.isInRange(sourcePosition))
	{
		cout << "Invalid Position\n\n";
		readSourcePosition();
	}
	
	return sourcePosition;
}

bool isValidSource(Position sourcePosition)
{
	Piece * pieceSelected = chessBoard.getPieceAt(sourcePosition);
	if (pieceSelected == nullptr)
	{
		cout << "No Piece found at <" << sourcePosition.getRow() << "," << sourcePosition.getColumn() << ">\n\n";
		return false;
	}
	else if (pieceSelected->getColor() != chessBoard.getCurrentPlayer())
	{
		cout << "The " << getPieceName(pieceSelected) << " at <" << sourcePosition.getRow() << "," << sourcePosition.getColumn() << "> belongs to the opponent.\n\n";
		return false;
	}
	return true;
}

void displayValidMoves(vector<Position> validMoves)
{
	cout << "Valid Moves <Row Column> : ";
	for (int i = 0; i < validMoves.size(); i++)
		cout << "<" << validMoves[i].getRow() << " " << validMoves[i].getColumn() << ">    ";
	cout << "\n\n";
}

Position readDestinationPosition(vector<Position> validMoves)
{
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

	cout << "Position <" << destinatonRow << "," << destinationColumn << "> is not a valid destination\n\n";
	destinationPosition = readDestinationPosition(validMoves);
	return destinationPosition;
}

void checkForWinner(Position destinationPosition)
{
	if (dynamic_cast<King*>(chessBoard.getPieceAt(destinationPosition)))
	{
		string playerColor;
		if (chessBoard.getCurrentPlayer() == Piece::COLOR_WHITE)
			playerColor = "WHITE";
		else if (chessBoard.getCurrentPlayer() == Piece::COLOR_BLACK)
			playerColor = "BLACK";
		cout << "Player " << playerColor << " won!\n\n";

		cout << "Type 'quit' to exit the game.\n";
		string temp;
		while (true)
		{
			cin >> temp;
			if (temp == "quit")
				exit(0);
		}
	}
}

void switchPlayer()
{
	switch (chessBoard.getCurrentPlayer())
	{
	case Piece::COLOR_WHITE:
		chessBoard.setCurrentPlayer(Piece::COLOR_BLACK);
		cout << "Player Black's turn\n\n";
		break;
	case Piece::COLOR_BLACK:
		chessBoard.setCurrentPlayer(Piece::COLOR_WHITE);
		cout << "Player White's turn\n\n";
		break;
	}
}

int main()
{
	displayInstructions();
	displayBoard();

	cout << "Player White's turn\n\n";
	Position sourcePosition, destinationPosition;
	Piece * pieceSelected;
	while (true)
	{
		if (chessBoard.isInCheck(chessBoard.getCurrentPlayer()))
			cout << "CHECK!\n\n";

		sourcePosition = readSourcePosition();
		if (isValidSource(sourcePosition))
			pieceSelected = chessBoard.getPieceAt(sourcePosition);
		else
			continue;

		vector<Position> validMoves = pieceSelected->getValidMoves(chessBoard, sourcePosition);
		if (validMoves.size() == 0)
		{
			cout << "The Piece selected can't move.\n\n";
			continue;
		}
		displayValidMoves(validMoves);

		destinationPosition = readDestinationPosition(validMoves);
		Piece * destinationPiece = chessBoard.getPieceAt(destinationPosition);
		chessBoard.movePiece(sourcePosition, destinationPosition);
		if (chessBoard.isInCheck(chessBoard.getCurrentPlayer()))
		{
			chessBoard.movePiece(destinationPosition, sourcePosition);
			chessBoard.setPieceAt(destinationPosition, destinationPiece);
			cout << "Moving " << getPieceName(pieceSelected) << " from <" << sourcePosition.getRow() << "," << sourcePosition.getColumn()
				<< "> to <" << destinationPosition.getRow() << "," << destinationPosition.getColumn() << "> causes CHECK!\n\n";
			continue;
		}

		displayBoard();

		switchPlayer();
	}

	return 0;
}

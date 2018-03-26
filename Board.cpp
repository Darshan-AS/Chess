#include "stdafx.h"
#include "Board.h"


Board::Board() {

	board[0][0] = new Rook(Piece::COLOR_BLACK);
	board[0][1] = new Knight(Piece::COLOR_BLACK);
	board[0][2] = new Bishop(Piece::COLOR_BLACK);
	board[0][3] = new Queen(Piece::COLOR_BLACK);
	board[0][4] = new King(Piece::COLOR_BLACK);
	board[0][5] = new Bishop(Piece::COLOR_BLACK);
	board[0][6] = new Knight(Piece::COLOR_BLACK);
	board[0][7] = new Rook(Piece::COLOR_BLACK);

	board[1][0] = new Pawn(Piece::COLOR_BLACK);
	board[1][1] = new Pawn(Piece::COLOR_BLACK);
	board[1][2] = new Pawn(Piece::COLOR_BLACK);
	board[1][3] = new Pawn(Piece::COLOR_BLACK);
	board[1][4] = new Pawn(Piece::COLOR_BLACK);
	board[1][5] = new Pawn(Piece::COLOR_BLACK);
	board[1][6] = new Pawn(Piece::COLOR_BLACK);
	board[1][7] = new Pawn(Piece::COLOR_BLACK);

	board[6][0] = new Pawn(Piece::COLOR_WHITE);
	board[6][1] = new Pawn(Piece::COLOR_WHITE);
	board[6][2] = new Pawn(Piece::COLOR_WHITE);
	board[6][3] = new Pawn(Piece::COLOR_WHITE);
	board[6][4] = new Pawn(Piece::COLOR_WHITE);
	board[6][5] = new Pawn(Piece::COLOR_WHITE);
	board[6][6] = new Pawn(Piece::COLOR_WHITE);
	board[6][7] = new Pawn(Piece::COLOR_WHITE);

	board[7][0] = new Rook(Piece::COLOR_WHITE);
	board[7][1] = new Knight(Piece::COLOR_WHITE);
	board[7][2] = new Bishop(Piece::COLOR_WHITE);
	board[7][3] = new Queen(Piece::COLOR_WHITE);
	board[7][4] = new King(Piece::COLOR_WHITE);
	board[7][5] = new Bishop(Piece::COLOR_WHITE);
	board[7][6] = new Knight(Piece::COLOR_WHITE);
	board[7][7] = new Rook(Piece::COLOR_WHITE);
}

Piece * Board::getPieceAt(Position position) {
	return board[position.getRow()][position.getColumn()];
}

void Board::setPieceAt(Position position, Piece * piece) {
	board[position.getRow()][position.getColumn()] = piece;
}

bool Board::containsPieceAt(Position position) {
	if (getPieceAt(position) == nullptr)
		return false;

	return true;
}

void Board::movePiece(Position currentPosition, Position destinationPosition) {
	Piece * piece = getPieceAt(currentPosition);

	board[destinationPosition.getRow()][destinationPosition.getColumn()] = piece;
	board[currentPosition.getRow()][currentPosition.getColumn()] = 0;

	if (dynamic_cast<King*>(piece)) {

		if (piece->getColor() == Piece::COLOR_WHITE)
			whiteKingPosition = destinationPosition;
		else if (piece->getColor() == Piece::COLOR_BLACK)
			blackKingPosition = destinationPosition;
	}
}

bool Board::isInRange(Position position) {

	if (position.getRow() >= MAX_ROWS ||
		position.getColumn() >= MAX_COLUMNS ||
		position.getRow() < 0 ||
		position.getColumn() < 0)
		return false;

	return true;
}

bool Board::isInCheck(int playerColor) {
	Position selfKingPosition;

	if (playerColor == Piece::COLOR_BLACK)
		selfKingPosition = blackKingPosition;
	else if (playerColor == Piece::COLOR_WHITE)
		selfKingPosition = whiteKingPosition;

	for (int row = 0; row < MAX_ROWS; row++)
		for (int column = 0; column < MAX_COLUMNS; column++) {

			Position position = Position(row, column);
			Piece * piece = getPieceAt(position);

			if (piece == nullptr || piece->getColor() == playerColor)
				continue;

			vector<Position> validMoves = piece->getValidMoves(*this, position);
			for (int i = 0; i < validMoves.size(); i++)
				if (validMoves[i].equals(selfKingPosition))
					return true;
		}

	return false;
}

bool Board::isCheckMate(int playerColor) {

	for (int row = 0; row < MAX_ROWS; row++)
		for (int column = 0; column < MAX_COLUMNS; column++) {

			Position sourcePosition = Position(row, column);
			Piece * sourcePiece = getPieceAt(sourcePosition);

			if (sourcePiece == nullptr || sourcePiece->getColor() != playerColor)
				continue;

			vector<Position> validMoves = sourcePiece->getValidMoves(*this, sourcePosition);
			if (validMoves.size() == 0)
				continue;

			for (int i = 0; i < validMoves.size(); i++) {

				Piece * destinationPiece = getPieceAt(validMoves[i]);
				movePiece(sourcePosition, validMoves[i]);

				if (!isInCheck(playerColor)) {
					movePiece(validMoves[i], sourcePosition);
					setPieceAt(validMoves[i], destinationPiece);
					return false;
				}

				movePiece(validMoves[i], sourcePosition);
				setPieceAt(validMoves[i], destinationPiece);
			}
		}

	return true;
}

int Board::getCurrentPlayer() {
	return currentPlayer;
}

void Board::setCurrentPlayer(int color) {
	currentPlayer = color;
}
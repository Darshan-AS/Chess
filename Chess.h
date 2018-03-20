Board board;

string getPieceName(Piece * piece);
void displayBoard();
void displayInstructions();
Position readSourcePosition();
bool isValidSource(Position sourcePosition);
void displayValidMoves(vector<Position> validMoves);
Position readDestinationPosition(vector<Position> validMoves);
void switchPlayer();
void displayGameOver();
Board board;

bool isValidSource(Position sourcePosition);
void switchPlayer();
void displayGameOver();

void init();
void setUpGameWindow();
void switchLightsOn();
void drawGame();
void showGameOver();
void onWindowReshape(int w, int h);
void onMouseClick(int button, int state, int xCursor, int yCursor);
void onKeyPressed(unsigned char key, int xCursor, int yCursor);
int main(int count, char** arguments);
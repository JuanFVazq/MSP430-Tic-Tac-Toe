#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

extern char currentPlayer; // Declare as extern
void placePiece(int row, int col);  // Declare placePiece
void initGrid();
int checkWin();
int checkDraw();
void playGame();

#endif


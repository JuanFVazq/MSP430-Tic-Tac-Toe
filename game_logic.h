#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define GRID_SIZE 3

extern char grid[GRID_SIZE][GRID_SIZE];
extern char currentPlayer;

void placePiece(int row, int col);
void initGrid();
int checkWin();
int checkDraw();

#endif

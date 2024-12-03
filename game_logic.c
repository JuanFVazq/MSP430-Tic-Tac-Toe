#include "grid.h"
#include "game_logic.h"
#include "lcdLib/lcdutils.h"
#include "lcdLib/lcddraw.h"

#define GRID_SIZE 3

static char grid[GRID_SIZE][GRID_SIZE];
char currentPlayer = 'X';

// Initialize the game grid
void initGrid() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      grid[i][j] = ' ';
    }
  }
}

// Check for a win
int checkWin() {
  for (int i = 0; i < GRID_SIZE; i++) {
    if (grid[i][0] == currentPlayer && grid[i][1] == currentPlayer && grid[i][2] == currentPlayer)
      return 1;
    if (grid[0][i] == currentPlayer && grid[1][i] == currentPlayer && grid[2][i] == currentPlayer)
      return 1;
  }
  if (grid[0][0] == currentPlayer && grid[1][1] == currentPlayer && grid[2][2] == currentPlayer)
    return 1;
  if (grid[0][2] == currentPlayer && grid[1][1] == currentPlayer && grid[2][0] == currentPlayer)
    return 1;
  return 0;
}

void placePiece(int row, int col) {
  if (grid[row][col] == ' ') {  // If the cell is empty
    drawMark(row, col, currentPlayer);  // Draw the current player's mark
    grid[row][col] = currentPlayer;    // Update the grid state
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';  // Switch player
  }
}

// Check for a draw
int checkDraw() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (grid[i][j] == ' ')
	return 0;
    }
  }
  return 1;
}

// Main game loop
void playGame() {
  int row = 0, col = 0;
  initGrid();
  drawGrid();

  while (1) {
    highlightCell(row, col,COLOR_PINK);
    // Wait for button press to navigate or select
    // Simulated input: Update row/col based on navigation buttons
    grid[row][col] = currentPlayer;
    drawMark(row, col, currentPlayer);
    if (checkWin()) {
      clearScreen(COLOR_BLACK);
      drawString5x7(20, 20, "WINNER", COLOR_GREEN, COLOR_BLACK);
      break;
    }
    if (checkDraw()) {
      clearScreen(COLOR_BLACK);
      drawString5x7(20, 20, "DRAW", COLOR_RED, COLOR_BLACK);
      break;
    }
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';  // Switch player
  }
}

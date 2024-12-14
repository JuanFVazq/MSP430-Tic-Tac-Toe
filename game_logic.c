#include "grid.h"
#include "game_logic.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"

#define GRID_SIZE 3

char grid[GRID_SIZE][GRID_SIZE];
char currentPlayer = 'X';


extern volatile int need_draw_mark;
extern volatile int placed_row, placed_col;

void initGrid() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      grid[i][j] = 0; 
    }
  }
}

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

int checkDraw() {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (grid[i][j] == 0)
	return 0;
    }
  }
  return 1;
}

void placePiece(int row, int col) {
  if (grid[row][col] == 0) {
    grid[row][col] = currentPlayer;

    
    placed_row = row;
    placed_col = col;
    need_draw_mark = 1;

    if (checkWin()) {
      
      buzzer_set_period(1000);
      __delay_cycles(500000);
      buzzer_set_period(0);  
   
      clearScreen(COLOR_BLACK);
      drawString11x16(20, 50, "WINNER!", COLOR_GREEN, COLOR_BLACK);
    } else if (checkDraw()) {
      
      buzzer_set_period(2000);
      __delay_cycles(500000);
      buzzer_set_period(0);  

      
      clearScreen(COLOR_BLACK);
      drawString11x16(30, 50, "DRAW", COLOR_RED, COLOR_BLACK);
    } else {
      
      currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
  }
}

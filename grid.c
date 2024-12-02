#include "lcdutils.h"
#include "lcddraw.h"
#include "grid.h"
#include <stdint.h>

#define GRID_SIZE 3
#define CELL_WIDTH (SHORT_EDGE_PIXELS / GRID_SIZE)
#define CELL_HEIGHT (LONG_EDGE_PIXELS / GRID_SIZE)

// Draw the Tic Tac Toe grid
void drawGrid() {
  for (int i = 1; i < GRID_SIZE; i++) {
    fillRectangle(i * CELL_WIDTH, 0, 1, LONG_EDGE_PIXELS, COLOR_WHITE); // Vertical lines
    fillRectangle(0, i * CELL_HEIGHT, SHORT_EDGE_PIXELS, 1, COLOR_WHITE); // Horizontal lines
  }
}

// Draw a player's mark ('X' or 'O') in a specific cell
void drawMark(int row, int col, char player) {
  u_char x = col * CELL_WIDTH + CELL_WIDTH / 4;
  u_char y = row * CELL_HEIGHT + CELL_HEIGHT / 4;
  if (player == 'X') {
    drawString5x7(x, y, "X", COLOR_RED, COLOR_BLACK);
  } else if (player == 'O') {
    drawString5x7(x, y, "O", COLOR_BLUE, COLOR_BLACK);
  }
}

// Highlight the current selection on the grid
void highlightCell(int row, int col, uint16_t color) {
  u_char x = col * CELL_WIDTH;
  u_char y = row * CELL_HEIGHT;
  fillRectangle(x, y, CELL_WIDTH, CELL_HEIGHT, color);
}

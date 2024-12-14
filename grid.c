#include "lcdutils.h"
#include "lcddraw.h"
#include "grid.h"
#include "game_logic.h"
#include <stdint.h>

#define GRID_SIZE 3
#define CELL_WIDTH (SHORT_EDGE_PIXELS / GRID_SIZE)
#define CELL_HEIGHT (LONG_EDGE_PIXELS / GRID_SIZE)


extern char grid[GRID_SIZE][GRID_SIZE];

void drawGrid() {
  for (int i = 1; i < GRID_SIZE; i++) {
    fillRectangle(i * CELL_WIDTH - 1, 0, 1, LONG_EDGE_PIXELS, COLOR_WHITE);
    fillRectangle(0, i * CELL_HEIGHT - 1, SHORT_EDGE_PIXELS, 1, COLOR_WHITE);
  }
}

void drawCellGridLines(int row, int col) {
  u_char x = col * CELL_WIDTH;
  u_char y = row * CELL_HEIGHT;

  
  fillRectangle(x, y, 1, CELL_HEIGHT, COLOR_WHITE);
  
  fillRectangle(x + CELL_WIDTH - 1, y, 1, CELL_HEIGHT, COLOR_WHITE);
  
  fillRectangle(x, y, CELL_WIDTH, 1, COLOR_WHITE);
  
  fillRectangle(x, y + CELL_HEIGHT - 1, CELL_WIDTH, 1, COLOR_WHITE);
}

void highlightCell(int row, int col, uint16_t color) {
  if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
    u_char x = col * CELL_WIDTH;
    u_char y = row * CELL_HEIGHT;

    int border_thickness = 5;
    fillRectangle(x, y, CELL_WIDTH, border_thickness, color);
    fillRectangle(x, y + CELL_HEIGHT - border_thickness, CELL_WIDTH, border_thickness, color);
    fillRectangle(x, y, border_thickness, CELL_HEIGHT, color);
    fillRectangle(x + CELL_WIDTH - border_thickness, y, border_thickness, CELL_HEIGHT, color);

    
    drawCellGridLines(row, col);

    if (grid[row][col] != 0) {
      drawMark(row, col, grid[row][col]);
    }
  }
}

void drawMark(int row, int col, char player) {
  u_char x = col * CELL_WIDTH + CELL_WIDTH / 2 - 3;
  u_char y = row * CELL_HEIGHT + CELL_HEIGHT / 2 - 8;
  int border_thickness = 5;

  x += border_thickness / 2;
  y += border_thickness / 2;

  if (player == 'X') {
    drawChar11x16(x, y, 'X', COLOR_RED, COLOR_PURPLE);
  } else if (player == 'O') {
    drawChar11x16(x, y, 'O', COLOR_BLUE, COLOR_PURPLE);
  }
  drawCellGridLines(row, col);
}

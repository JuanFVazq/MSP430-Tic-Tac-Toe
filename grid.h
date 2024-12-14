#ifndef GRID_H
#define GRID_H
#include <stdint.h>

void drawGrid();
void drawMark(int row, int col, char player);
void highlightCell(int row, int col, uint16_t color);
void drawCellGridLines(int row, int col);

#endif

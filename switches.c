#include <msp430.h>
#include "switches.h"
#include "grid.h"
#include "game_logic.h"
#include "lcdutils.h"

// Global variables for the current position on the board
int cursor_row = 0, cursor_col = 0;

void switch_init() {
  P2REN |= SWITCHES;   // Enable pull-up resistors
  P2IE |= SWITCHES;    // Enable interrupts
  P2OUT |= SWITCHES;   // Configure as pull-ups
  P2DIR &= ~SWITCHES;  // Set switches as inputs
  P1REN |= BIT3;       // Enable pull-up for P1 button
  P1OUT |= BIT3;       // Configure P1 button as pull-up
  P1IE |= BIT3;        // Enable interrupt for P1 button
  P1IFG &= ~BIT3;      // Clear P1 interrupt flag
}

void handle_board_movement() {
  // Clear the previous position (optional visual feedback)
  // drawMark(cursor_row, cursor_col, ' '); // Assuming you clear this way
  highlightCell(cursor_row, cursor_col, COLOR_BLACK);
  
  if (!(P2IN & SW1)) {  // Move up
    if (cursor_row > 0) cursor_row--;
  }
  if (!(P2IN & SW2)) {  // Move down
    if (cursor_row < 2) cursor_row++;
  }
  if (!(P2IN & SW3)) {  // Move left
    if (cursor_col > 0) cursor_col--;
  }
  if (!(P2IN & SW4)) {  // Move right
    if (cursor_col < 2) cursor_col++;
  }

  // Draw the updated cursor
  highlightCell(cursor_row, cursor_col, COLOR_YELLOW);  // Assuming you use a highlight function
}

void switch_interrupt_handler() {
  if (P1IFG & BIT3) {  // P1 button pressed
    placePiece(cursor_row, cursor_col);  // Place piece
    P1IFG &= ~BIT3;  // Clear interrupt flag
  } else {
    handle_board_movement();  // Handle movement
  }

  P2IFG &= ~SWITCHES;  // Clear all P2 interrupt flags
}

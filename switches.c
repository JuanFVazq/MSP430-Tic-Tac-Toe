#include <msp430.h>
#include "switches.h"
#include "grid.h"
#include "game_logic.h"
#include "lcdutils.h"

// Global variables for the current position on the board
int cursor_row = 0, cursor_col = 0;

void switch_init() {
  P2REN |= SWITCHES;   // Enable pull-up resistors for switches
  P2OUT |= SWITCHES;   // Set switches to pull-up mode
  P2DIR &= ~SWITCHES;  // Configure switches as inputs
  P2IE |= SWITCHES;    // Enable interrupts for P2 switches
  P2IFG &= ~SWITCHES;  // Clear all interrupt flags for P2

  P1REN |= BIT3;       // Enable pull-up resistor for P1
  P1OUT |= BIT3;       // Configure P1 as pull-up
  P1DIR &= ~BIT3;      // Set P1 as input
  P1IE |= BIT3;        // Enable interrupt for P1
  P1IFG &= ~BIT3;      // Clear interrupt flag for P1
}

void handle_board_movement() {
  static int prev_row = -1, prev_col = -1;

  // Update cursor position based on button states
  if (!(P2IN & SW1) && cursor_row > 0) {  // S1 - Move up
    cursor_row--;
  } else if (!(P2IN & SW2) && cursor_row < 2) {  // S2 - Move down
    cursor_row++;
  } else if (!(P2IN & SW3) && cursor_col > 0) {  // S3 - Move left
    cursor_col--;
  } else if (!(P2IN & SW4) && cursor_col < 2) {  // S4 - Move right
    cursor_col++;
  }

  // Redraw highlights if the cursor moved
  if (prev_row != cursor_row || prev_col != cursor_col) {
    highlightCell(prev_row, prev_col, COLOR_BLACK);  // Clear previous highlight
    highlightCell(cursor_row, cursor_col, COLOR_YELLOW);  // Highlight current cell
    prev_row = cursor_row;
    prev_col = cursor_col;
  }
}

void switch_interrupt_handler() {

  P1OUT ^= BIT6;
  char p2val = P2IN;
  
  if (!(p2val & SW1) || !(p2val & SW2) || !(p2val & SW3) || !(p2val & SW4)) {
    handle_board_movement();  // Handle cursor movement
  }

  if (P1IFG & BIT3) {  // P1 button pressed
    placePiece(cursor_row, cursor_col);  // Place a piece
    P1IFG &= ~BIT3;  // Clear interrupt flag for P1
  }

  P2IFG &= ~SWITCHES;  // Clear interrupt flags for P2 switches
}

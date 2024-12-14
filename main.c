#include <msp430.h>
#include "lcdLib/lcdutils.h"
#include "lcdLib/lcddraw.h"
#include "grid.h"
#include "game_logic.h"
#include "timerLib/libTimer.h"
#include "switches.h"
#include "buzzer.h"
#include "assemblyFunction.h"

volatile int sleepMode = 0;
volatile int need_redraw = 0;
volatile int need_draw_mark = 0;
volatile int placed_row = 0, placed_col = 0;
volatile int timer_counter = 0;


int cursor_row = 0, cursor_col = 0;
int prev_row = 0, prev_col = 0;

void main() {
  WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
  configureClocks();         // Configure system clocks
  lcd_init();                // Initialize the LCD
  buzzer_init();             // Initialize the buzzer
  switch_init();             // Initialize switches
  initGrid();                // Initialize the game grid
  clearScreen(COLOR_PURPLE); // Clear the screen
  drawGrid();                // Draw the initial grid

  // Initialize P1.0 and P1.6 as outputs for LED indicators
  P1DIR |= BIT0 | BIT6;
  P1OUT &= ~(BIT0 | BIT6);  // Turn off LEDs initially

  assemblyFunction();  // Call the assembly function

  __enable_interrupt();      // Enable interrupts globally

  
  highlightCell(cursor_row, cursor_col, COLOR_YELLOW);

  while (1) {
    if (need_redraw) {
      highlightCell(prev_row, prev_col, COLOR_PURPLE);
      highlightCell(cursor_row, cursor_col, COLOR_YELLOW);
      prev_row = cursor_row;
      prev_col = cursor_col;
      need_redraw = 0;
      
    }
    if (need_draw_mark) {
      drawMark(placed_row, placed_col, grid[placed_row][placed_col]);
      need_draw_mark = 0;
    }
    
    if (timer_counter >= 1) {
      timer_counter = 0;
      P1OUT ^= BIT6;
    }

    
    if (sleepMode) {
      __bis_SR_register(LPM0_bits + GIE);
    }
  }
}

#include <msp430.h>
#include "lcdLib/lcdutils.h"
#include "lcdLib/lcddraw.h"
#include "grid.h"
#include "game_logic.h"
#include "timerLib/libTimer.h"
#include "switches.h"

void main() {
  WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
  configureClocks();         // Configure system clocks
  lcd_init();                // Initialize the LCD
  clearScreen(COLOR_PURPLE); // Clear the screen once
  switch_init();             // Initialize switches
  __enable_interrupt();      // Enable interrupts globally

  drawGrid();                // Draw the initial grid
  highlightCell(0, 0, COLOR_YELLOW);  // Highlight starting position

  while (1) {
    // Interrupt-driven logic handles all actions
  }
}

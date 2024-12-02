#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include "lcdLib/lcdutils.h"
#include "lcdLib/lcddraw.h"
#include "grid.h"
#include "game_logic.h"
#include "timerLib/libTimer.h"
#include "switches.h"



void main() {
  WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
  configureClocks();         // Configure system clocks
  lcd_init(); // Initialize the LCD screen
  clearScreen(COLOR_PURPLE);
  switch_init();  // Initialize P2 and P1 buttons
  __enable_interrupt();  // Enable global interrupts

  drawGrid();  // Draw the Tic-Tac-Toe grid

  while (1) {
    // Main game logic is handled by interrupts
  }
}

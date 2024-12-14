#include <msp430.h>
#include "switches.h"
#include "grid.h"
#include "game_logic.h"
#include "lcdutils.h"

extern volatile int sleepMode;
extern volatile int need_redraw;
extern volatile int cursor_row, cursor_col;
extern int prev_row, prev_col;

void switch_init() {
  
  P2REN |= SWITCHES; 
  P2OUT |= SWITCHES; 
  P2DIR &= ~SWITCHES;
  P2IE  |= SWITCHES; 
  P2IES |= SWITCHES; 
  P2IFG &= ~SWITCHES;
}

void switch_interrupt_handler() {
  if (P2IFG & SW3) {  
    sleepMode ^= 1;  
    if (sleepMode) {
      P1OUT |= BIT0; 
    } else {
      P1OUT &= ~BIT0;
    }
    P2IFG &= ~SW3;
  }

  if (!sleepMode) {
    if (P2IFG & SW1) { 
      cursor_row = (cursor_row > 0) ? cursor_row - 1 : 2;
      need_redraw = 1;
      P2IFG &= ~SW1;
    }
    if (P2IFG & SW2) {  
      cursor_col = (cursor_col < 2) ? cursor_col + 1 : 0;
      need_redraw = 1;
      P2IFG &= ~SW2;    
    }
    if (P2IFG & SW4) {  
      placePiece(cursor_row, cursor_col);
      need_redraw = 1;  
      P2IFG &= ~SW4;    
    }
  }



}


void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & SWITCHES) {
    switch_interrupt_handler();
    __bic_SR_register_on_exit(LPM0_bits);
  }
}

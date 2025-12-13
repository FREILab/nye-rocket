#include <msp430.h> 
#include "Board.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    /* initialization of all functions we use */
    LED_init();
//    KEY_init();
    TIMER_init();
//    COMP_init();
//    FLASH_init();

    __bis_SR_register(LPM0_bits | GIE);  // turn CPU off but keep Interrupts on
    // code after this line will never be reached
}

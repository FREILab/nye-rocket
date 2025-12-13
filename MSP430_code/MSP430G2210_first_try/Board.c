/*
 * Board.c
 *
 *  Created on: 25.08.2022
 *      Author: marcihle
 */


#include <msp430.h>
#include "Board.h"

/* ****************************************************************************************
LED functions
**************************************************************************************** */

void LED_init(void)
{
    P1SEL = 0x00;
    P1OUT = LED_PIN;
    LED_OFF();
    P1DIR = 0x00;                                                   // set all ports as input
    P1DIR = P1DIR | LED_PIN;                                        // set LED-Pin as output

}

void LED_ON(void)
{
    P1OUT |= LED_PIN;
}


void LED_OFF(void)
{
    P1OUT &= ~LED_PIN;
}

void LED_TOGGLE (void)
{
    P1OUT ^= LED_PIN;
}

void set_LED (bool in)
{
    if (in)
    {
        LED_ON();
    } else
    {
        LED_OFF();
    }
}

/* ****************************************************************************************
KEY functions
**************************************************************************************** */

void KEY_init(void)
{
    P1DIR &= ~KEY_PIN;                                 // als Eingang setzen
    P1REN |= KEY_PIN;                                  // enable pull-up/down resistor
    P1OUT |= KEY_PIN;                                  // use pull-up as KEY is connected to GND
 }

bool read_KEY(void)
{
    bool out;
    out = ~(P1IN >> KEY_BIT) & 0x01;                                        // maskierten Eingang lesen
    return(out);
}


/* ****************************************************************************************
Compare functions
**************************************************************************************** */

void COMP_init(void)
{
    P1DIR &= ~SIGNAL_PIN;                              // als Eingang setzen
    P1REN &= ~SIGNAL_PIN;                                  // disable pull-up/down resistor
    CACTL2 = P2CA3|P2CA1;                               // P1.5 = CA5
    CACTL1 = CAREF_1 | CAON;                            // 0.25*Vcc on P1.2, Comp. on
}

bool read_COMP(void)
{
    bool out;
    out = ~(CACTL2 & CAOUT) & 0x01;                                        // maskierten Eingang lesen
    return(out);
}

/* ****************************************************************************************
TIMER functions
**************************************************************************************** */

void TIMER_init(void)
{
    BCSCTL3  |= LFXT1S_2;                     // Select VLO as low freq clock
    TA0CCTL0 = CCIE;                          // TA0CCR0 interrupt enabled
    TA0CCR0 = 0xFFFE;
    TA0CTL = TASSEL_2 | MC_2 | ID_1;          // SMCLK, count mode: continuous up, div 2
    __bis_SR_register(GIE);                   // Stay in active mode w/ interrupt
}



// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERA0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    P1OUT ^= LED_PIN;    // toggle LED
}

/* ****************************************************************************************
FLASH functions
**************************************************************************************** */

void FLASH_init(void)
{
    BCSCTL3  |= LFXT1S_2;                       // Select VLO as low freq clock

    if (CALBC1_1MHZ==0xFF)                      // If calibration constant erased
    {
        while(1);                               // do not load, trap CPU!!
    }
    DCOCTL = 0;                               // Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ;
    FCTL2 = FWKEY | FSSEL0 | FN1;             // MCLK/3 for Flash Timing Generator
}

/* function to pattern the whole segment with a single value (for test purposes) */
void write_SegC (char value)
{
    char *Flash_ptr;                          // Flash pointer
    unsigned int i;

    Flash_ptr = (char *) FLASH_C;             // Initialize Flash pointer
    FCTL1 = FWKEY | ERASE;                    // Set Erase bit
    FCTL3 = FWKEY;                            // Clear Lock bit
    *Flash_ptr = 0;                           // Dummy write to erase Flash segment

    FCTL1 = FWKEY | WRT;                      // Set WRT bit for write operation

    for (i=0; i<64; i++)
    {
        *Flash_ptr++ = value;                   // Write value to flash
    }

    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY | LOCK;                     // Set LOCK bit
}

void copy_C2D (void)
{
    char *Flash_ptrC;                         // Segment C pointer
    char *Flash_ptrD;                         // Segment D pointer
    unsigned int i;

    Flash_ptrC = (char *) FLASH_C;             // Initialize Flash segment C pointer
    Flash_ptrD = (char *) FLASH_D;             // Initialize Flash segment D pointer
    FCTL1 = FWKEY | ERASE;                    // Set Erase bit
    FCTL3 = FWKEY;                            // Clear Lock bit
    *Flash_ptrD = 0;                          // Dummy write to erase Flash segment D
    FCTL1 = FWKEY | WRT;                      // Set WRT bit for write operation

    for (i=0; i<64; i++)
    {
        *Flash_ptrD++ = *Flash_ptrC++;          // copy value segment C to segment D
    }

    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY | LOCK;                     // Set LOCK bit
}

void copy_mem2flash (unsigned char *Source_ptr, unsigned char *Flash_ptr )
{
    unsigned int i;


    FCTL1 = FWKEY | ERASE;                    // Set Erase bit
    FCTL3 = FWKEY;                            // Clear Lock bit
    *Flash_ptr = 0;                           // Dummy write to erase Flash segment

    FCTL1 = FWKEY | WRT;                      // Set WRT bit for write operation

    for (i=0; i<64; i++)
    {
        *Flash_ptr++ = *Source_ptr++;         // Copy values to flash
    }


    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY | LOCK;                     // Set LOCK bit
}




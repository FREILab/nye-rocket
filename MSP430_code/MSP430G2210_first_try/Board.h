/*
 * Board.h
 *
 *  Created on: 25.08.2022
 *      Author: marcihle
 */

#include <stdint.h>

#ifndef BOARD_H_
#define BOARD_H_


// typedef enum { false, true } bool;
typedef int bool;
enum { false, true };


#define LED_BIT    (7)                  // LED is connected to P1.7 (Pin 5)
#define KEY_BIT    (6)                  // KEY is connected to P1.6 (Pin 4)
#define SIGNAL_BIT (5)                  // SIGNAL is connected to P1.5 (Pin 3)

#define LED_PIN    (1<<LED_BIT)
#define KEY_PIN    (1<<KEY_BIT)
#define SIGNAL_PIN (1<<SIGNAL_BIT)


#define FLASH_A     (0x10C0)            // Segment A address
#define FLASH_B     (0x1080)            // Segment B address
#define FLASH_C     (0x1040)            // Segment C address
#define FLASH_D     (0x1000)            // Segment D address


#endif /* BOARD_H_ */

/* LED-Functions */
void LED_init(void);
void LED_ON(void);
void LED_OFF(void);
void LED_TOGGLE (void);
void set_LED (bool in);

/* KEY-Functions */
void KEY_init(void);
bool read_KEY(void);

/* COMP-Functions */
void COMP_init(void);
bool read_COMP(void);

/* Timer-Functions */
void TIMER_init(void);

/* FLASH-Functions */
void FLASH_init(void);
void write_SegC (char value);
void copy_C2D (void);

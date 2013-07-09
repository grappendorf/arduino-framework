// ATMEL ATMEGA644P / SANGUINO
//
//                   +---\/---+
//  INT0 (D 0) PB0  1|        |40  PA0 (AI 0 / D31)
//  INT1 (D 1) PB1  2|        |39  PA1 (AI 1 / D30)
//  INT2 (D 2) PB2  3|        |38  PA2 (AI 2 / D29)
//   PWM (D 3) PB3  4|        |37  PA3 (AI 3 / D28)
//   PWM (D 4) PB4  5|        |36  PA4 (AI 4 / D27)
//  MOSI (D 5) PB5  6|        |35  PA5 (AI 5 / D26)
//  MISO (D 6) PB6  7|        |34  PA6 (AI 6 / D25)
//   SCK (D 7) PB7  8|        |33  PA7 (AI 7 / D24)
//             RST  9|        |32  AREF
//             VCC 10|        |31  GND
//             GND 11|        |30  AVCC
//           XTAL2 12|        |29  PC7 (D 23)
//           XTAL1 13|        |28  PC6 (D 22)
//  RX0 (D 8)  PD0 14|        |27  PC5 (D 21) TDI
//  TX0 (D 9)  PD1 15|        |26  PC4 (D 20) TDO
//  RX1 (D 10) PD2 16|        |25  PC3 (D 19) TMS
//  TX1 (D 11) PD3 17|        |24  PC2 (D 18) TCK
//  PWM (D 12) PD4 18|        |23  PC1 (D 17) SDA
//  PWM (D 13) PD5 19|        |22  PC0 (D 16) SCL
//  PWM (D 14) PD6 20|        |21  PD7 (D 15) PWM
//                   +--------+

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>
#undef PROGMEM
#define PROGMEM __attribute((section(".progmem.data")))

#define NOT_A_PIN 0
#define NOT_A_PORT 0

#define NOT_ON_TIMER 0
#define TIMER0A 1
#define TIMER0B 2
#define TIMER1A 3
#define TIMER1B 4
#define TIMER2  5
#define TIMER2A 6
#define TIMER2B 7


extern const uint8_t PROGMEM digital_pin_to_port_PGM[];
extern const uint8_t PROGMEM digital_pin_to_bit_PGM[];
extern const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[];

extern const uint8_t PROGMEM digital_pin_to_timer_PGM[];

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.
//
// These perform slightly better as macros compared to inline functions
//
#define digitalPinToPort(P) ( pgm_read_byte( digital_pin_to_port_PGM + (P) ) )
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) )
#define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
#define analogInPinToBit(P) (P)
#define digitalPinToPCICR(p)    (((p) >= 0 && (p) <= 21) ? ((uint8_t *) (&PCICR)) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 2 : (((p) <= 13) ? 0 : 1))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK2) : (((p) <= 13) ? (&PCMSK0) : (((p) <= 21) ? (&PCMSK1) : ((uint8_t *)0))))
#define digitalPinToPCMSKbit(p) (((p) <= 7) ? (p) : (((p) <= 13) ? ((p) - 8) : ((p) - 14)))

const static uint8_t SS   = 53;
const static uint8_t MOSI = 51;
const static uint8_t MISO = 50;
const static uint8_t SCK  = 52;

const static uint8_t SDA = 20;
const static uint8_t SCL = 21;
const static uint8_t LED_BUILTIN = 13;

const static uint8_t A0 = 54;
const static uint8_t A1 = 55;
const static uint8_t A2 = 56;
const static uint8_t A3 = 57;
const static uint8_t A4 = 58;
const static uint8_t A5 = 59;
const static uint8_t A6 = 60;
const static uint8_t A7 = 61;
const static uint8_t A8 = 62;
const static uint8_t A9 = 63;
const static uint8_t A10 = 64;
const static uint8_t A11 = 65;
const static uint8_t A12 = 66;
const static uint8_t A13 = 67;
const static uint8_t A14 = 68;
const static uint8_t A15 = 69;

#define PA 1
#define PB 2
#define PC 3
#define PD 4

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] =
{
        NOT_A_PORT,
        (uint16_t) &DDRA,
        (uint16_t) &DDRB,
        (uint16_t) &DDRC,
        (uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] =
{
        NOT_A_PORT,
        (uint16_t) &PORTA,
        (uint16_t) &PORTB,
        (uint16_t) &PORTC,
        (uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] =
{
        NOT_A_PORT,
        (uint16_t) &PINA,
        (uint16_t) &PINB,
        (uint16_t) &PINC,
        (uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
{
        PB, /* 0 */
        PB,
        PB,
        PB,
        PB,
        PB,
        PB,
        PB,
        PD, /* 8 */
        PD,
        PD,
        PD,
        PD,
        PD,
        PD,
        PD,
        PC, /* 16 */
        PC,
        PC,
        PC,
        PC,
        PC,
        PC,
        PC,
        PA, /* 24 */
        PA,
        PA,
        PA,
        PA,
        PA,
        PA,
        PA  /* 31 */
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
        _BV(0), /* 0, port B */
        _BV(1),
        _BV(2),
        _BV(3),
        _BV(4),
        _BV(5),
        _BV(6),
        _BV(7),
        _BV(0), /* 8, port D */
        _BV(1),
        _BV(2),
        _BV(3),
        _BV(4),
        _BV(5),
        _BV(6),
        _BV(7),
        _BV(0), /* 16, port C */
        _BV(1),
        _BV(2),
        _BV(3),
        _BV(4),
        _BV(5),
        _BV(6),
        _BV(7),
        _BV(7), /* 24, port A */
        _BV(6),
        _BV(5),
        _BV(4),
        _BV(3),
        _BV(2),
        _BV(1),
        _BV(0)
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
        NOT_ON_TIMER,   /* 0  - PB0 */
        NOT_ON_TIMER,   /* 1  - PB1 */
        NOT_ON_TIMER,   /* 2  - PB2 */
        TIMER0A,        /* 3  - PB3 */
        TIMER0B,                /* 4  - PB4 */
        NOT_ON_TIMER,   /* 5  - PB5 */
        NOT_ON_TIMER,   /* 6  - PB6 */
        NOT_ON_TIMER,   /* 7  - PB7 */
        NOT_ON_TIMER,   /* 8  - PD0 */
        NOT_ON_TIMER,   /* 9  - PD1 */
        NOT_ON_TIMER,   /* 10 - PD2 */
        NOT_ON_TIMER,   /* 11 - PD3 */
        TIMER1B,        /* 12 - PD4 */
        TIMER1A,        /* 13 - PD5 */
        TIMER2B,        /* 14 - PD6 */
        TIMER2A,        /* 15 - PD7 */
        NOT_ON_TIMER,   /* 16 - PC0 */
        NOT_ON_TIMER,   /* 17 - PC1 */
        NOT_ON_TIMER,   /* 18 - PC2 */
        NOT_ON_TIMER,   /* 19 - PC3 */
        NOT_ON_TIMER,   /* 20 - PC4 */
        NOT_ON_TIMER,   /* 21 - PC5 */
        NOT_ON_TIMER,   /* 22 - PC6 */
        NOT_ON_TIMER,   /* 23 - PC7 */
        NOT_ON_TIMER,   /* 24 - PA0 */
        NOT_ON_TIMER,   /* 25 - PA1 */
        NOT_ON_TIMER,   /* 26 - PA2 */
        NOT_ON_TIMER,   /* 27 - PA3 */
        NOT_ON_TIMER,   /* 28 - PA4 */
        NOT_ON_TIMER,   /* 29 - PA5 */
        NOT_ON_TIMER,   /* 30 - PA6 */
        NOT_ON_TIMER   /* 31 - PA7 */
};

#endif

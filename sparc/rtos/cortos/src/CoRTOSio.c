/*	CoRTOSio.c - CoRTOS i/o module for superblinky et. al. demonstrations

	2018.12.12 12:00	Release 1.10

	(c) 2016-2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	This module provides I/O for demonstration board LEDs,
	it is only used with the test suites.

	The module is only a quick & dirty implementation doing the
	minimum to get things going.  It shouldn't be followed
	slavishly in your application.  The initialization of the
	ports and the port control registers will need to be changed
	to match your particular hardware setup.

*/

#include "CoRTOSup.h"

#ifdef uP_Cortex_M0
/* Needs to go before CoRTOScomdefs.h to resolve typedef collisions. */
#include "sam.h"
#endif

#include "CoRTOScomdefs.h"
#include "CoRTOSio.h"

#ifdef uP_AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/parity.h>
#endif

static uint8_t number_of_leds = 1;
static boolean translate_control;

/*	Compressing 1 of 256 LED values to 0 of 19, mostly
	random(ish) with a flat frequency distribution. */
static uint8_t to_20 [] = {
		0x08,0x12,0x02,0x09,0x0c,0x12,0x13,0x12,0x01,0x06,0x13,0x00,0x00,0x09,0x0a,0x06,
		0x0a,0x0d,0x13,0x02,0x04,0x0e,0x03,0x0f,0x0d,0x12,0x0e,0x07,0x13,0x03,0x13,0x10,
		0x11,0x0e,0x02,0x13,0x10,0x01,0x0f,0x11,0x05,0x01,0x0a,0x00,0x08,0x08,0x10,0x0b,
		0x09,0x06,0x0b,0x13,0x04,0x0d,0x05,0x09,0x06,0x05,0x0b,0x07,0x0c,0x12,0x0c,0x06,
		0x08,0x00,0x01,0x10,0x0e,0x04,0x0e,0x0b,0x0b,0x02,0x04,0x11,0x03,0x0a,0x06,0x07,
		0x04,0x07,0x08,0x02,0x09,0x11,0x07,0x13,0x0e,0x11,0x02,0x0d,0x0b,0x01,0x0d,0x01,
		0x06,0x04,0x09,0x00,0x08,0x0f,0x05,0x00,0x02,0x0b,0x08,0x05,0x02,0x01,0x0f,0x04,
		0x0c,0x02,0x05,0x0d,0x03,0x0a,0x12,0x01,0x08,0x10,0x0c,0x12,0x06,0x06,0x05,0x0d,
		0x03,0x0a,0x10,0x10,0x0c,0x0e,0x08,0x02,0x06,0x10,0x00,0x02,0x0c,0x05,0x0a,0x09,
		0x05,0x03,0x0f,0x0f,0x01,0x0d,0x09,0x03,0x0e,0x06,0x03,0x0d,0x12,0x0f,0x07,0x08,
		0x01,0x0d,0x00,0x13,0x03,0x0b,0x0c,0x01,0x01,0x04,0x0c,0x05,0x0a,0x09,0x00,0x0c,
		0x08,0x09,0x02,0x04,0x04,0x03,0x07,0x0d,0x0d,0x0f,0x0b,0x06,0x06,0x10,0x12,0x02,
		0x09,0x0a,0x07,0x0a,0x0f,0x07,0x13,0x08,0x03,0x00,0x08,0x01,0x0f,0x12,0x13,0x0a,
		0x0e,0x0e,0x12,0x0f,0x0b,0x03,0x0b,0x05,0x0a,0x03,0x0f,0x11,0x0c,0x10,0x04,0x0f,
		0x11,0x12,0x11,0x0b,0x07,0x11,0x07,0x04,0x12,0x05,0x11,0x00,0x0c,0x10,0x0a,0x0d,
		0x10,0x0c,0x10,0x09,0x0e,0x07,0x0b,0x07,0x00,0x13,0x0e,0x00,0x13,0x11,0x05,0x11};

static uint8_t led_xlate (uint8_t led) {
/*	Returns the number of bits that a '1' needs to be
	shifted to turn a specific LED on or off. */
	uint8_t retval;
	if (translate_control == false)
		return (led);
	retval = to_20[led];
	switch (number_of_leds) {
		case 1:
			/*	0 */
			retval = 0;
			break;
		case 2:
			/*	0-1 */
			retval = 0x01 & retval;
			break;
		case 3:
			/* 0-2 */
			if ((retval &= 0x03) > 2) retval = 0;
			break;
		case 4:
			/*	0-3 */
			retval = 0x03 & retval;
			break;
		case 8:
			/*	0-7 */
			retval = 0x07 & retval;
			break;
		case 20:
			break;
		default:
			retval = 0;
	}
	return (retval);
}

void led_translate (boolean control) {
	translate_control = control;
}

/*****************************************************************
******************************************************************
**
**		AVR
**
******************************************************************
*****************************************************************/
#ifdef uP_AVR

/************************************************************************
*	AVR I/O initialization
************************************************************************/

void initialize_IO (void)
{
/*	Power reduction register, 1 turns subsys off.  Turn on subsys before
	setting it up.

		7	1	PRTWI		2-wire interface
		6	1	PRTIM2	Timer/counter 2
		5	1	PRTIM0	Timer/counter 0
		4	0	-
		3	0	PRTIM1	Timer/counter 1
		2	0	PRSPI		Serial peripheral interface - NEEDED FOR DEBUGING
		1	1	PRUSART0	UART 0
		0	1	PRADC		ADC

			  76543210 */
/*	PRR = 0b11100011; */

#ifdef uP_platform_ATMEGA1284P_XPLD
	/* PB0	LED0 / SW0
		PB1	LED2 / SW1
		PB2	LED3 / SW2
		PB3	LED1
		PB4	SPI SS
		PB5	MOSI
		PB6	MISO
		PB7	SCK

				 76543210 */
	PORTB = 0b00001111;
	DDRB =  0b00001111;
	number_of_leds = 4;
#endif

#ifdef uP_platform_ATMEGA328P_XMINI_sheild
	/* ATMEGA328P_XMINI w/ & w/o sheild
		PB0	LEDs
		PB1	""
		PB2	""
		PB3	""
		PB4	""
		PB5	""
		PB6	??? on XMINI
		PB7	Push button on XMINI
				 76543210 */
	PORTB = 0b11000000;
	DDRB =  0b00111111;

/*		Port C set to inputs w/ pullups
		PC0	LEDs on XMINI sheild
		PC1	""
		PC2	""
		PC3	""
		PC4	""
		PC5	""
		PC6	Reset/Debug wire

				 76543210 */
	PORTC = 0b01000000;
	DDRC =  0b00111111;

/*		Port D set to outputs - LEDs on STK500 & XMINI
		PD0
		PD1
		PD2
		PD3
		PD4
		PD5
		PD6
		PD7

			    76543210 */
	PORTD = 0b00000000;
	DDRD =  0b11111111;
	number_of_leds = 20;
#endif

#ifdef uP_platform_SDK_500
/*		Port D set to outputs - LEDs on STK500 & XMINI
		PD0
		PD1
		PD2
		PD3
		PD4
		PD5
		PD6
		PD7

			    76543210 */
	PORTD = 0b00000000;
	DDRD =  0b11111111;
	number_of_leds = 8;
#endif

	/*	See rtavrin.c for timer/counter #1 setup & control - it is used as the
		RTOS timer. */

	/*	Digital Input Disable register, set if the input is only for analog */
	DIDR0 = 0b00111111;

#ifdef uP_platform_SDK_500
	number_of_leds = 8;
#elif uP_platform_ATMEGA328P_XMINI_sheild
	number_of_leds = 20;
#elif uP_platform_ATMEGA328P_XMINI
	number_of_leds = 1;
#elif uP_platform_ATMEGA1284P_XPLD
	number_of_leds = 4;
#endif
}

/************************************************************************
*	AVR LED driver for development boards:
*		Atmel Xplained Mini ATmega328PB_XMINI w/ LED sheild
*		Atmel Xplained Mini ATmega328PB_XMINI
*		Atmel STK500
*		Atmel Explorer board ATMEGA1284P_XPLD
*
*	These are used by the maint_xxx.c test files
************************************************************************/

/*	Turn on/off/toggle one of n LEDs, where n is > number of LEDs on board. */

void led_on (uint8_t led) {
	led = led_xlate (led);
#ifdef uP_platform_ATMEGA328P_XMINI
	PORTB |= bit5;
#elif uP_platform_ATMEGA328P_XMINI_sheild
	if (led < 8)
		PORTD |= 1 << led;
	else if (led < 14)
		PORTB |= 1 << (led - 8);
	else
		PORTC |= 1 << (led - 14);
#elif uP_platform_ATMEGA1284P_XPLD
	/*	4 leds, low true */
	PORTB &= ~(1 << led);
#else // uP_platform_SDK_500
	PORTD |= 1 << led;
#endif
}

void led_off (uint8_t led) {
	led = led_xlate (led);
#ifdef uP_platform_ATMEGA328P_XMINI
	PORTB &= ~bit5;
#elif uP_platform_ATMEGA328P_XMINI_sheild
	if (led < 8)
		PORTD &= ~(1 << led);
	else if (led < 14)
		PORTB &= ~(1 << (led - 8));
	else
		PORTC &= ~(1 << (led - 14));
#elif uP_platform_ATMEGA1284P_XPLD
	/*	4 leds, low true */
	PORTB |= 1 << led;
#else // uP_platform_SDK_500
	PORTD &= ~(1 << led);
#endif
}

void led_toggle (uint8_t led) {
	led = led_xlate (led);
#ifdef uP_platform_ATMEGA328P_XMINI
	PORTB ^= bit5;
#elif uP_platform_ATMEGA328P_XMINI_sheild
	if (led < 8)
		PORTD ^= 1 << led;
	else if (led < 14)
		PORTB ^= 1 << (led - 8);
	else
		PORTC ^= 1 << (led - 14);
#elif uP_platform_ATMEGA1284P_XPLD
	/*	4 leds, low true */
	PORTB ^= 1 << led;
#else // uP_platform_SDK_500
	PORTD ^= 1 << led;
#endif
}

#endif // uP_AVR

/*****************************************************************
******************************************************************
**
**		MSP430
**
******************************************************************
*****************************************************************/
#ifdef uP_MSP430

#ifdef variant_MSP430FR5994
#include "msp430FR5994.h"
#elif variant_MSP430FR5969
#include "msp430FR5969.h"
#elif variant_MSP430FR6989
#include "msp430FR6989.h"
#else
#include <msp430.h>
#endif

/*	Explorer board port assignments

	MSP-EXP43FR5994 256K/8K, vector math
		P1.0	Red LED
		P1.1	Green LED
		P5.6	Pushbutton 1
		P5.5	Pushbutton 2

	MSP-EXP43FR5969 64K/2K
		P4.6	Red LED
		P1.0	Green LED
		P4.5	Pushbutton 1
		P1.1	Pushbutton 2

	MSP-EXP43FR6989 128K/2K HDW MPY
		P1.0	Red LED 1
		P9.7	Green LED 2
		P1.1	Pushbutton 1
		P1.2	Pushbutton 2
*/

/************************************************************************
*	MSP430 initialization
************************************************************************/

void initialize_IO (void)
{
#ifdef uP_platform_MSP_EXP430FR5994
	PM5CTL0 = 0xfffe;
	//			 76543210
	P1DIR = 0b00000011;
#elif uP_platform_MSP_EXP430FR5969
	PM5CTL0 = 0xfffe;
	//			 76543210
	P1DIR = 0b00000001;
	P4DIR = 0b01000000;
#elif uP_platform_MSP_EXP430FR6989
	PM5CTL0 = 0xfffe;
	//			 76543210
	P1DIR = 0b00000001;
	P9DIR = 0b10000000;
#endif
	number_of_leds = 2;
}

/************************************************************************
*	MSP430 LED Driver - ti MSP-EXP30FR5969 Explorer board
************************************************************************/

void led_port (uint8_t port_value) {
	port_value = (port_value ^ (port_value >> 2) ^ (port_value >> 4) ^ (port_value >> 6)) & 0x03;
	led_off (0);
	led_off (1);
	if ((port_value & bit0) != 0)
		led_on (0);
	if ((port_value & bit1) != 0)
		led_on (1);
}

/*	Compress a 1 of 8 LED pattern for task ID into two LEDs, even tasks
 * control LED1/red, odd ones light LED2/green
 */
void led_on (uint8_t led) {
	led = led_xlate (led);
#ifdef uP_platform_MSP_EXP430FR5994
	if ((led & bit0) == 0)
		P1OUT |= 0x01;
	else
		P1OUT |= 0x02;
#elif uP_platform_MSP_EXP430FR5969
	if ((led & bit0) == 0)
		P4OUT |= 0x40;
	else
		P1OUT |= 0x01;
#elif uP_platform_MSP_EXP430FR6989
	if ((led & bit0) == 0)
		P1OUT |= 0x01;
	else
		P9OUT |= 0x80;
#endif
}

void led_off (uint8_t led) {
	led = led_xlate (led);
#ifdef uP_platform_MSP_EXP430FR5994
	if ((led & bit0) == 0)
		P1OUT &= ~0x01;
	else
		P1OUT &= ~0x02;
#elif uP_platform_MSP_EXP430FR5969
	if ((led & bit0) == 0)
		P4OUT &= ~0x40;
	else
		P1OUT &= ~0x01;
#elif uP_platform_MSP_EXP430FR6989
	if ((led & bit0) == 0)
		P1OUT &= ~0x01;
	else
		P9OUT &= ~0x80;
#endif
}

void led_toggle (uint8_t led) {
	led = led_xlate (led);
#ifdef uP_platform_MSP_EXP430FR5994
	if ((led & bit0) == 0)
		P1OUT ^= 0x01;
	else
		P1OUT ^= 0x02;
#elif uP_platform_MSP_EXP430FR5969
	if ((led & bit0) == 0)
		P4OUT ^= 0x40;
	else
		P1OUT ^= 0x01;
#elif uP_platform_MSP_EXP430FR6989
	if ((led & bit0) == 0)
		P1OUT ^= 0x01;
	else
		P9OUT ^= 0x80;
#endif
}

#endif // uP_MSP430


/*****************************************************************
******************************************************************
**
**		PIC24
**
******************************************************************
*****************************************************************/
#ifdef uP_PIC24
#include "p24FJ128GA204.h"

void write_leds (uint8_t leds) {
	LATC = (LATC & 0xff1f) | ((leds & 0x07) << 5);
}

uint8_t read_leds (void) {
	return (((uint8_t)LATC >> 5) & 0x07);
}

/*	Change I/O assignments as needed for your hardware -
	this works with a Microchip DM240004 "Curiosity" PIC24F
	development board.  The LED functions work differently
	than for other processors in order to produce a better
	light show. */
void led_on (uint8_t led) {
	led = led_xlate (led);
	LATC |= 1 << (led + 5);
}

void led_off (uint8_t led) {
	led = led_xlate (led);
	LATC &= ~(1 << (led + 5));
}

void led_toggle (uint8_t led) {
	led = led_xlate (led);
	LATC ^= 1 << (led + 5);
}

/************************************************************************
*
*	Initialization
*
************************************************************************/

void initialize_IO (void) {
	/*	LED I/O pins to outputs */
	TRISC &= 0xff1f;
	number_of_leds = 3;
	translate_control = true;
}

#endif

/*****************************************************************
******************************************************************
**
**		SAMD10
**
******************************************************************
*****************************************************************/
#ifdef uP_Cortex_M0
#define PORTA PORT->Group[0]

static uint8_t port_b_mirror;
static uint8_t port_c_mirror;
static uint8_t port_d_mirror;

void led_on (uint8_t led) {
	if (number_of_leds == 1) {
		port_on (port_b, bit3);
	} else {
		led = led_xlate (led);
		if (led < 8)
			port_on (port_d, 1 << led);
		else if (led < 14)
			port_on (port_b, 1 << (led - 8));
		else
			port_on (port_c, 1 << (led - 14));
	}
}

void led_off (uint8_t led) {
	if (number_of_leds == 1) {
		port_off (port_b, bit3);
	} else {
		led = led_xlate (led);
		if (led < 8)
			port_off (port_d, 1 << led);
		else if (led < 14)
			port_off (port_b, 1 << (led - 8));
		else
			port_off (port_c, 1 << (led - 14));
	}
}

void led_toggle (uint8_t led) {
	if (number_of_leds == 1) {
		port_toggle (port_b, bit3);
	} else {
		led = led_xlate (led);
		if (led < 8)
			port_toggle (port_d, 1 << led);
		else if (led < 14)
			port_toggle (port_b, 1 << (led - 8));
		else
			port_toggle (port_c, 1 << (led - 14));
	}
}

void initialize_IO (void) {
	init_M0_IO (port_b, 0b00111111);
	init_M0_IO (port_c, 0b00111111);
	init_M0_IO (port_d, 0b00111111);
#ifdef uP_platform_ATSAMD10_XMINI_sheild
	/*	There are only 18 active LEDs, but this works well enough. */
	number_of_leds = 20;
#else
	number_of_leds = 1;
#endif
}

/*	In the conversion of the SAMD10-XMINI I/O to the ATMega328PB-XMINI/Arduino
	I/O the assignment comments use the following headings:
		B: bit number for access
		P: pin number
		Ard	Arduino function
		SAM	SAMD10D-XMINI module connection

	There should be a better way... */

void init_M0_IO (uint8_t port, uint8_t output_bits) {
	switch (port) {
		case port_b:
		/*	J200 (Port B) - not a very good mapping
			B	P	Ard	SAM
				8	PB0	NC
				9	PB1	NC
			0	10	PB2	PA23
			1	11	PB3	PA22
			2	12	PB4	PA24
			3	13	PB5	PA09 (On-board LED)
				14	GND	GND
				15	AREF	PA03/AREF - controlled with port C
			4	16	PC4	PA14
			5	17	PC5	PA15 */
			if ((output_bits & bit0) != 0)
				PORTA.DIRSET.reg = PORT_PA23;
			if ((output_bits & bit1) != 0)
				PORTA.DIRSET.reg = PORT_PA22;
			if ((output_bits & bit2) != 0)
				PORTA.DIRSET.reg = PORT_PA24;
			if ((output_bits & bit3) != 0)
				PORTA.DIRSET.reg = PORT_PA09;
			if ((output_bits & bit4) != 0)
				PORTA.DIRSET.reg = PORT_PA14;
			if ((output_bits & bit5) != 0)
				PORTA.DIRSET.reg = PORT_PA15;
			port_output (port_b, 0);
			break;
		case port_c:
		/* J203 (Port C)
			B	P	Ard	SAM
			0	1	A0		PA02 / ADC input 0
			1	2	A1		PA03 / ADC input 1 / AREF
			2	3	A2		PA04 / ADC input 2
			4	4	A3		PA05 / ADC input 3
			4	5	A4		PA06 / ADC input 4
			5	6	A5		PA07 / ADC input 5 */
			if ((output_bits & bit0) != 0)
				PORTA.DIRSET.reg = PORT_PA02;
			if ((output_bits & bit1) != 0)
				PORTA.DIRSET.reg = PORT_PA03;
			if ((output_bits & bit2) != 0)
				PORTA.DIRSET.reg = PORT_PA04;
			if ((output_bits & bit3) != 0)
				PORTA.DIRSET.reg = PORT_PA05;
			if ((output_bits & bit4) != 0)
				PORTA.DIRSET.reg = PORT_PA06;
			if ((output_bits & bit5) != 0)
				PORTA.DIRSET.reg = PORT_PA07;
			port_output (port_c, 0);
			break;
		case port_d:
		/*	J201 (Port D)
			B	P	Ard	SAM
			0	1	PD0	PA11
			1	2	PD1	PA10
			2	3	PD2	PA16
			3	4	PD3	PA17
			4	5	PD4	PA27
			5	6	PD5	PA25 (On-board pushbutton)
			6	7	PD6	PA30 SWCLK on-board debugger
			7	8	PD7	PA31 SWDIO on-board debugger */
			if ((output_bits & bit0) != 0)
				PORTA.DIRSET.reg = PORT_PA11;
			if ((output_bits & bit1) != 0)
				PORTA.DIRSET.reg = PORT_PA10;
			if ((output_bits & bit2) != 0)
				PORTA.DIRSET.reg = PORT_PA16;
			if ((output_bits & bit3) != 0)
				PORTA.DIRSET.reg = PORT_PA17;
			if ((output_bits & bit4) != 0)
				PORTA.DIRSET.reg = PORT_PA27;
			/*	PA25/Pin5 On board push button - normally left as input,
				line has a 100K pull-up */
			if ((output_bits & bit5) != 0)
				PORTA.DIRSET.reg = PORT_PA25;
			if ((output_bits & bit6) != 0)
				PORTA.DIRSET.reg = PORT_PA30;
			if ((output_bits & bit7) != 0)
				PORTA.DIRSET.reg = PORT_PA31;
			port_output (port_d, 0);
			break;
	}
}

void port_on (uint8_t port, uint8_t bit_pattern) {
	switch (port) {
		case port_b:
			port_b_mirror |= bit_pattern;
			port_output (port_b, port_b_mirror);
			break;
		case port_c:
			port_c_mirror |= bit_pattern;
			port_output (port_c, port_c_mirror);
			break;
		case port_d:
			port_d_mirror |= bit_pattern;
			port_output (port_d, port_d_mirror);
			break;
	}
}

void port_off (uint8_t port, uint8_t bit_pattern) {
	switch (port) {
		case port_b:
			port_b_mirror &= ~bit_pattern;
			port_output (port_b, port_b_mirror);
			break;
		case port_c:
			port_c_mirror &= ~bit_pattern;
			port_output (port_c, port_c_mirror);
			break;
		case port_d:
			port_d_mirror &= ~bit_pattern;
			port_output (port_d, port_d_mirror);
			break;
	}
}

void port_toggle (uint8_t port, uint8_t bit_pattern) {
	switch (port) {
		case port_b:
			port_b_mirror ^= bit_pattern;
			port_output (port_b, port_b_mirror);
			break;
		case port_c:
			port_c_mirror ^= bit_pattern;
			port_output (port_c, port_c_mirror);
			break;
		case port_d:
			port_d_mirror ^= bit_pattern;
			port_output (port_d, port_d_mirror);
			break;
	}
}

void port_output (uint8_t port, uint8_t bit_pattern) {
	/*	See init_IO(), above for mappings.
		This method is a real mess! */
	switch (port) {
		case port_b:
			port_b_mirror = bit_pattern;
			if ((port_b_mirror & bit0) != 0)
				PORTA.OUTSET.reg = PORT_PA23;
			else
				PORTA.OUTCLR.reg = PORT_PA23;
			if ((port_b_mirror & bit1) != 0)
				PORTA.OUTSET.reg = PORT_PA22;
			else
				PORTA.OUTCLR.reg = PORT_PA22;
			if ((port_b_mirror & bit2) != 0)
				PORTA.OUTSET.reg = PORT_PA24;
			else
				PORTA.OUTCLR.reg = PORT_PA24;
			if ((port_b_mirror & bit3) != 0)
				PORTA.OUTSET.reg = PORT_PA09;
			else
				PORTA.OUTCLR.reg = PORT_PA09;
			if ((port_b_mirror & bit4) != 0)
				PORTA.OUTSET.reg = PORT_PA14;
			else
				PORTA.OUTCLR.reg = PORT_PA14;
			if ((port_b_mirror & bit5) != 0)
				PORTA.OUTSET.reg = PORT_PA15;
			else
				PORTA.OUTCLR.reg = PORT_PA15;
			break;
		case port_c:
			port_c_mirror = bit_pattern;
			if ((port_c_mirror & bit0) != 0)
				PORTA.OUTSET.reg = PORT_PA02;
			else
				PORTA.OUTCLR.reg = PORT_PA02;
			if ((port_c_mirror & bit1) != 0)
				PORTA.OUTSET.reg = PORT_PA03;
			else
				PORTA.OUTCLR.reg = PORT_PA03;
			if ((port_c_mirror & bit2) != 0)
				PORTA.OUTSET.reg = PORT_PA04;
			else
				PORTA.OUTCLR.reg = PORT_PA04;
			if ((port_c_mirror & bit3) != 0)
				PORTA.OUTSET.reg = PORT_PA05;
			else
				PORTA.OUTCLR.reg = PORT_PA05;
			if ((port_c_mirror & bit4) != 0)
				PORTA.OUTSET.reg = PORT_PA06;
			else
				PORTA.OUTCLR.reg = PORT_PA06;
			if ((port_c_mirror & bit5) != 0)
				PORTA.OUTSET.reg = PORT_PA07;
			else
				PORTA.OUTCLR.reg = PORT_PA07;
			break;
		case port_d:
			port_d_mirror = bit_pattern;
			if ((port_d_mirror & bit0) != 0)
				PORTA.OUTSET.reg = PORT_PA11;
			else
				PORTA.OUTCLR.reg = PORT_PA11;
			if ((port_d_mirror & bit1) != 0)
				PORTA.OUTSET.reg = PORT_PA10;
			else
				PORTA.OUTCLR.reg = PORT_PA10;
			if ((port_d_mirror & bit2) != 0)
				PORTA.OUTSET.reg = PORT_PA16;
			else
				PORTA.OUTCLR.reg = PORT_PA16;
			if ((port_d_mirror & bit3) != 0)
				PORTA.OUTSET.reg = PORT_PA17;
			else
				PORTA.OUTCLR.reg = PORT_PA17;
			if ((port_d_mirror & bit4) != 0)
				PORTA.OUTSET.reg = PORT_PA27;
			else
				PORTA.OUTCLR.reg = PORT_PA27;
			/*	On board push button, normally an input */
			if ((port_d_mirror & bit5) != 0)
				PORTA.OUTSET.reg = PORT_PA25;
			else
				PORTA.OUTCLR.reg = PORT_PA25;
			if ((port_d_mirror & bit6) != 0)
				PORTA.OUTSET.reg = PORT_PA30;
			else
				PORTA.OUTCLR.reg = PORT_PA30;
			if ((port_d_mirror & bit7) != 0)
				PORTA.OUTSET.reg = PORT_PA31;
			else
				PORTA.OUTCLR.reg = PORT_PA31;
			break;
	}
}

#endif

/*	CoRTOSsuperblinky.c - Super Blinky demonstration

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	This module contains main() & the tasks for the super blinky demo.

	The program demonstrates delays, periodic signals, resources
	and messages.

	It blinks LEDs that are attached to PORTD, producing a pseudo-random
	sequence at somewhat pseudo-random intervals. */

#include "CoRTOSuP.h"

/*	uP specific include files - these will need to be modified
	depending on the variant of the processor you are using.
	You have hopefully already encountered and triumphed over
	this adversity: make changes as you see fit. */
#ifdef uP_AVR
#include <avr\io.h>
#include <avr\interrupt.h>
//#include <asf.h>
#elif uP_MSP430
#include "msp430FR6989.h"
#elif uP_PIC24
#include "p24FJ128GA204.h"
#else // uP_Cortex_M0
#include "sam.h"
#endif

#include "CoRTOScomdefs.h"
#include "CoRTOSkernel.h"
#include "CoRTOStimer.h"
#include "CoRTOSmessage.h"
#include "CoRTOSsignal.h"
#include "CoRTOStask.h"
#include "CoRTOSio.h"
#include "CoRTOSint.h"

static void task0 (void);
static void task1 (void);
static void task2 (void);
static void task3 (void);
static void task4 (void);
static void task5 (void);
static void task6 (void);
static void task7 (void);

/*	RTOS data defining tasks and the size of their stacks.

	number_of_tasks can be found in CoRTOStask.h.

	CoRTOStask.c is not used in the demonstration program -
	tasks, main() and task arrays are all in this file. */

task_address_type start_addresses [number_of_tasks] =
	{task0, task1, task2, task3, task4, task5, task6, task7};

/*	Larger stacks are needed with 32-bit machines - pushed
	values are all 4 bytes wide as compared to 1 or 2 bytes
	for 8/16 bit systems. */
#ifdef uP_32bit
uint16_t task_stack_size [number_of_tasks] =
//	8 * 0x80 = 0x400 bytes total
	{128, 128, 128, 128, 128, 128, 128, 128};
#else
uint16_t task_stack_size [number_of_tasks] =
	{80, 80, 80, 80, 80, 80, 80, 80};
#endif

static uint8_t led [3] = {0, 1, 2};

static void task0 (void)
{
	start_periodic_signal (0, 0, 43);
	while (true)
	{
		led[0] += 3;
		send_message (0, (void *)&led[0]);
		wait_for_signal (0);
	}
}

static void task1 (void)
{
	while (true)
	{
		led[1] += 5;
		send_message (0, (void *)&led[1]);
		delay (1, 47);
	}
}

static void task2 (void)
{
	while (true)
	{
		led[2] += 7;
		send_message (0, (void *)&led[2]);
		delay (2, 51);
	}
}

static void task3 (void)
{
	uint8_t * ptr;
	uint8_t led;
	while (true)
	{
		ptr = (uint8_t *)wait_for_message (0);
		led = *ptr;
		led_toggle (led);
	}
}

/*	Dummy tasks so that all test suites have 8 tasks, keeps
	from having WTF? moments when the number of tasks isn't
	set correctly in CoRTOStask.h */
static void task4 (void) {}
static void task5 (void) {}
static void task6 (void) {}
static void task7 (void) {}

/*	main() does nothing but initialize and start CoRTOS -
	this would normally be done in the function start_CoRTOS
	in the file CoRTOStask.c */

int main (void)
{
#ifdef uP_AVR
	/*	Atmel ATmega328PB-XMINI board, doesn't do anything relevant. */
//	board_init();
#elif uP_MSP430
#elif uP_PIC24
#else // uP_Cortex_M0
	/*	Atmel ATSAMD10-XMINI board */
	SystemInit();
#endif

	initialize_delay_module ();
	initialize_message_module ();
	initialize_signal_module ();
	initialize_IO ();

	/*	1mSec tick */
	set_high_speed (true);
	initialize_interrupts ();

	led_translate (true);
	timer_int_enable (true);

	start_CoRTOS ();

	while (true)
		;
	return (0);
}


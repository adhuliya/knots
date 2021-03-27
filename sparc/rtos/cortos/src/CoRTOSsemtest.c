/*	CoRTOSsemtest.c - Test module for semaphores

	2018.12.12 12:00	Release 1.10

	(c) 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	This module contains main() & a set of tasks for a test of semaphore code
		acquire_sem ()
		release_sem ()
		set_sem_count ()
		start/stop_timeout ()

	It blinks LEDs that are attached to PORTD

		Time	LED	Action
		0		0-2	Turn on
		0.11	0		Turns off
		0.23	1		Turns off
		0.41	2		Turns off
		0.41	3		Turns on
		1.20	3		Turns off
		Repeat

				5		Flashes 0.3 seconds on / 0.3 seconds off

All tasks are infinite loops.

	task0 - task 2 (1 & 2 are 'virtual' tasks )
		acquire sem 0 count
		send message to turn led on
		delay x seconds
		send message to turn led off
		acquire sem 3 count
		release sem 1
	task3
		set semaphore 0 count to 3
		send message to turn LED 3 on
		delay .79 second
		send message to turn led 3 off
		3x release sem 3 count
		3x acquire sem 1 count
	task4
		receive message
		control led

	task5
		start 0.3 second timeout
		acquire sem 2 count
		wait for 0.3 seconds for sem count that never coms
		stop timeout
		send message to turn LED 5 on
		delay by
			0.1 seconds semaphore count was acquired OK
			0.2 seconds sempahore count was not available
			0.3 seconds semaphore acquisition timed out
		send message to turn LED 5 off

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

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
#include "msp430fr6989.h"
#elif uP_PIC24
#include "p24FJ128GA204.h"
#else // uP_Cortex_M0
#include "sam.h"
#endif

#include "CoRTOScomdefs.h"
#include "CoRTOStask.h"
#include "CoRTOSkernel.h"
#include "CoRTOStimer.h"
#include "CoRTOSsignal.h"
#include "CoRTOSmessage.h"
#include "CoRTOSsem.h"
#include "CoRTOSio.h"
#include "CoRTOSint.h"

static void task0 (void);
// static void task1 (void);
// static void task2 (void);
static void task3 (void);
static void task4 (void);
static void task5 (void);
static void task6 (void);
static void task7 (void);

/*	RTOS data defining tasks and the size of their stacks.

	number_of_tasks can be found in CoRTOStask.h.

	CoRTOStask.c is not used in the demonstration program -
	tasks, main() and task arrays are all in this file. */

/*	Note that task0 code is used 3x - this works as the code uses the current_task
	variable to discriminate between its different 'instantiations'. */
task_address_type start_addresses [number_of_tasks] =
	{task0, task0, task0, task3, task4, task5, task6, task7};

/*	Larger stacks are needed with 32-bit machines - pushed
	values are all 4 bytes wide as compared to 1 or 2 bytes
	for 8/16 bit systems. */
#ifdef uP_32bit
uint16_t task_stack_size [number_of_tasks] =
	{128, 128, 128, 128, 128, 128, 128, 128};
#else
uint16_t task_stack_size [number_of_tasks] =
	{80, 80, 80, 80, 80, 80, 80, 80};
#endif

typedef enum {
	led_on_code,
	led_off_code,
	led_toggle_code
} led_action_code_t;

typedef struct {
	uint8_t led_n;
	led_action_code_t ac;
} led_struct_t;

static led_struct_t led [8][3] = {
	{{0, led_off_code}, {0, led_on_code}, {0, led_toggle_code}},
	{{1, led_off_code}, {1, led_on_code}, {1, led_toggle_code}},
	{{2, led_off_code}, {2, led_on_code}, {2, led_toggle_code}},
	{{3, led_off_code}, {3, led_on_code}, {3, led_toggle_code}},
	{{4, led_off_code}, {4, led_on_code}, {4, led_toggle_code}},
	{{5, led_off_code}, {5, led_on_code}, {5, led_toggle_code}},
	{{6, led_off_code}, {6, led_on_code}, {6, led_toggle_code}},
	{{7, led_off_code}, {7, led_on_code}, {7, led_toggle_code}}
};

static uint16_t delay_times [] = {11, 23, 41, 79, 161, 321, 641};

static void task0 (void)
{
	while (true) {
		acquire_sem (0, true);
		send_message (0, (void *)&led[current_task][1]);
		delay (current_task, delay_times[current_task]);
		send_message (0, (void *)&led[current_task][0]);
		release_sem (1);
		acquire_sem (3, true);
	}
}

/*	Placeholders for unused tasks, task0 code is used for tasks 1 & 2 */
//static void task1 (void) {}
//static void task2 (void) {}

static void task3 (void)
{
	while (true)
	{
		send_message (0, (void *)&led[current_task][1]);
		delay (current_task, delay_times[current_task]);
		send_message (0, (void *)&led[current_task][0]);
		set_sem_count (0, 3);
		release_sem (3);
		release_sem (3);
		release_sem (3);
		acquire_sem (1, true);
		acquire_sem (1, true);
		acquire_sem (1, true);
	}
}

static void task4 (void)
{
	led_struct_t * ptr;
	uint8_t led;
	while (true)
	{
		ptr = (led_struct_t *)wait_for_message (0);
		if (ptr != NULL) {
			led = ptr->led_n;
			switch (ptr->ac) {
				case led_off_code:
					led_off (led);
					break;
				case led_on_code:
					led_on (led);
					break;
				case led_toggle_code:
					led_toggle (led);
					break;
				default:
					break;
			}
		} else {
			/*	We would get here if there was an expired
				timeout on waiting for a message. */
		}
	}
}

uint8_t retval;
static void task5 (void) {
	while (true) {
		start_timeout (current_task, 30);
		retval = acquire_sem (2, true);
		stop_timeout (current_task);
		send_message (0, (void *)&led[current_task][1]);
		switch (retval) {
			case status_ok:
				delay (current_task, 10);
				break;
			case status_unavail:
				delay (current_task, 20);
				break;
			case status_timeout:
				delay (current_task, 30);
				break;
		}
		send_message (0, (void *)&led[current_task][0]);
	}
}

/*	These two placeholder tasks left over from a generic test module will work OK -
	when they execute returns CoRTOS marks them as suspended and that's the last we
	see of them. */
static void task6 (void) {}
static void task7 (void) {}

/*	main() does nothing but initialize and start CoRTOS */

int main (void)
{

#ifdef uP_AVR
	/*	Atmel ATmega328PB-XMINI board */
//	board_init();
#elif uP_MSP430
#elif uP_PIC24
#elif uP_Cortex_M0
	/*	Atmel ATSAMD10-XMINI board */
	SystemInit();
#endif

	initialize_delay_module ();
	initialize_message_module ();
	initialize_sem_module ();
	initialize_IO ();
	initialize_interrupts ();

	/*	In this demo the LEDs are 1:1 with the tasks, not a
		light show. */
	led_translate (false);

	timer_int_enable (true);

	start_CoRTOS ();

	/*	We would end up here if task0 executed a return. */
	while (true)
		;
	/*	Some compilers want to see a return value if main is
		of type int.  There is no reason main can't be a void
		function but some compilers don't like that either.
		A return from main() makes sense in a DOS/Windows/Linux...
		environment but makes no sense in an embedded system. */
	return (0);
}


/*	CoRTOSblinkyMSP.c Stand alone demo

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	MSP430FR6989, Texas Instruments Code composer studio, changes may
	be needed for other processors - see CoRTOSio.c & CoRTOSint.c for
	a template.

	A stand-alone 'blinky' demonstration of the CoRTOS Cooperative
	Real Time Operating System.

	It demonstrates the kernel and the time delay extension to the
	basic OS.

	Code has been skinnyed down for this demo file.

	(c) 2017 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

// #include <msp430.h>
#include "msp430fr6989.h"

#include "CoRTOSuP.h"
#include "CoRTOScomdefs.h"

void led_on (uint8_t led);
void led_off (uint8_t led);
void initialize_io_and_interrupts (void);
void task0 (void);
void task1 (void);
void service_timers (void);
void delay (uint8_t tin, uint16_t ticks);
void suspend (void);
void resume_task (uint8_t tn);
void relinquish (void);
int main (void);

/*	Task number of the executing task - this can be useful for
	array indexing and for calls to the OS. */

uint8_t current_task;

/**********************************************************************
*
*	msp430 I/O
*
**********************************************************************/

/*	The interrupt is triggered 10mSec period on output
	compare A using timer 1.  Its function is to decrement
	the timers of any delayed tasks via a call to service_timers(). */

#pragma vector=TIMER1_A0_VECTOR
__interrupt void timerA1_CC0 (void)
{
	/*	This vector is shared with other timer interrupt sources.  At
		present there is only the one source triggered on overflow compare. */
	service_timers ();
	__enable_interrupt ();
}

/*	Change port as needed for your hardware - this works
	with ti's MSP-EXP30FR5969 Explorer board. */
#define red_led 0x00
#define green_led 0x01

void led_on (uint8_t led) {
	if (led == red_led)
		P1OUT |= 0x01;
	else
		P9OUT |= 0x80;
}

void led_off (uint8_t led) {
	if (led == red_led)
		P1OUT &= ~0x01;
	else
		P9OUT &= ~0x80;
}

#define development_WDT 0x5A80
void initialize_io_and_interrupts (void) {

	/*	Stop the watchdog timer. */
	WDTCTL = development_WDT;

	/*	Change port as needed - this is for the the
		ti's MSP-EXP430FR6989 Explorer board. */
	PM5CTL0 = 0xfffe;
	P1DIR = 0x01;
	P9DIR = 0x80;

	/*	Set one wait state for FRAM access, the a5 is the unlock code,
		10 is the number of wait states - in the high nibble.  This
		is needed as the FRAM can only run at 8MHz and so needs the
		wait state when the CPU runs at 16MHz. */
	FRCTL0 = 0xa510; FRCTL0 = 0xa510;

	/*	Setup XT1 */
	PJSEL0 |= BIT4 | BIT5;

	/*	Unlock CS registers */
	CSCTL0 = 0xa500;

	/*	Set DCO to 16MHz */
	CSCTL1 = DCOFSEL_4|DCORSEL;

	/*	set ACLK = XT1; SMCLK= MCLK = DCO = 16MHz */
	CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;

	/*	Set all dividers */
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;
	CSCTL4 &= ~LFXTOFF;

	/*	Timer A1: SMCLK/8, MC_1 upmode, TASSEL_2 : 2 MHz clock source */
	TA1CTL = TASSEL_2 + MC_1 + ID_3;

	/*	10mSec period */
	TA1CCR0 =  20000;

	/*	CCR0 timer interrupt enabled */
	TA1CCTL0 |= CCIE;
}

/**********************************************************************
*
*	Tasks
*
**********************************************************************/

/*	These three lines tell the OS about the tasks. */

#define number_of_tasks 2
typedef void (* task_address_type) (void);
task_address_type start_addresses [number_of_tasks] = {task0, task1};

/*	Task 0 turns the LED on and then waits for 1 second, then
	it does it again.

	Task1 waits 0.5 second and then turns the led off and waits
	another 0.5 second and then repeats.

	As a result the led is on for 0.5 second and then off for 0.5
	second. */

void task0 (void) {
	while (1) {
		led_on (red_led);
		delay (0, 53);
		led_off (red_led);
		delay (0, 53);
	}
}

void task1 (void)
{
	while (1) {
		led_on (green_led);
		delay (1, 71);
		led_off (green_led);
		delay (1, 71);
	}
}

/**********************************************************************
*
*	Delay
*
**********************************************************************/

/*	This is a pared-down version of the code in CoRTOSdelay.c,
	but it is an accurate depiction of the action of the delay
	function.

	Note that delay() is independent of the kernel.  If there are
	no calls to delay() in the developed system then the whole
	of the delay code can be left out of the link with no impact
	on the rest of the system.

	This independence is true of all the CoRTOS extensions - link
	in only the features you need. */

/*	Called by the 10mSec interrupt.  If a timer is non-zero it is because
	a task has delayed itself.  When the timer reaches 0 the task is
	resumed/made active so that it will be given control by relinquish(). */

#define number_of_timers 2
static uint16_t timer [number_of_timers];
static uint8_t timer_active [number_of_timers];
static uint8_t delayed_task_number [number_of_timers];

/* service_timers() is called by a periodic interrupt service routine.
	The period determines the time value of a 'tick'. */

void service_timers (void) {
	uint8_t tin;
	for (tin = 0; tin < number_of_timers; tin++) {
		if (timer_active[tin] == true) {
			if (timer[tin] == 0) {
				resume_task (delayed_task_number[tin]);
				timer_active[tin] = false;
			}
			else
				--timer[tin];
		}
	}
}

/*	Called by a task to delay itself.  The task is taken out of action
	for ticks * 10mSec. */

void delay (uint8_t tin, uint16_t ticks) {
	/*	The task calls suspend to set it to inactive.  It gives up control
		by calling relinquish() - relinquish() will then skip this task
		when its turn to run comes up again.  The task is made active by
		the service_timers() function's call to resume_task().

		The call to suspend () is made before the timer itself is made
		active so that if the timer[] setting was not atomic it doesn't
		matter as the ISR won't be decrementing the timer until it is
		active. */

	timer_active[tin] = false;
	timer[tin] = ticks;
	delayed_task_number[tin] = current_task;
	suspend ();
	timer_active[tin] = true;
	relinquish ();
}

/**********************************************************************
*
*	Assembler macros
*
**********************************************************************/

/*	Specific for each uP.

	N.B. for the MSP CCS V7, a space is needed between " and push/pop */

// - or - " pushm.w #8, r11 " for those msp430's that support it
#define PUSHALL() asm volatile \
	(							\
		" push r4  \n\t"	\
		" push r5  \n\t"	\
		" push r6  \n\t"	\
		" push r7  \n\t"	\
		" push r8  \n\t"	\
		" push r9  \n\t"	\
		" push r10 \n\t"	\
		" push r11 \n\t"	\
	)

// - or - " popm.w #8, r11 \n\t" for those msp430's that support it
#define POPALL() asm volatile \
	(							\
		" pop r11 \n\t"	\
		" pop r10 \n\t"	\
		" pop r9  \n\t"	\
		" pop r8  \n\t"	\
		" pop r7  \n\t"	\
		" pop r6  \n\t"	\
		" pop r5  \n\t"	\
		" pop r4  \n\t"	\
	)

/**********************************************************************
*
*	Kernel
*
**********************************************************************/

static uint16_t sp_save [number_of_tasks];
static uint16_t starting_stack [number_of_tasks];
static uint8_t start_from_beginning [number_of_tasks];
static uint8_t suspended [number_of_tasks];

/*	suspend() and resume() cause relinquish() to skip tasks that are blocked,
	in this demo they are blocked by being delayed. */

void suspend (void) {
	suspended[current_task] = true;
}

void resume_task (uint8_t tn) {
	suspended[tn] = false;
}

/*	Relinquish is the heart of CoRTOS.

	It is a round-robin task scheduler.

	Only active tasks are given control.  Inactive tasks are skipped
	until they are made active again.  Tasks make themselves inactive
	when they are blocked.  The tasks are made active again when the
	block is removed by an interrupt or another task.
*/

void relinquish (void) {
	/*	Save whatever it is that the compiler expects to be saved.  Save the
		stack pointer so that we can get back to this task by reloading the
		saved value and then executing a return.  The PUSHALL/POPALL macros
		and stack pointer reference are specific to the uP. */
	PUSHALL();
	sp_save[current_task] = _get_SP_register();

	while (1) {
		do {
			/*	The if() construct is much faster than using a 
				mod % operator. */
			if (++current_task == number_of_tasks)
				current_task = 0;

		/*	Cycle through inactive tasks.  It is not uncommon for the system
			to spend most of it's time chasing its tail going through a
			list of all inactive tasks.  See the manual for suggestions
			of things to do while doing nothing. */
		} while (suspended[current_task] == true);

		if (start_from_beginning[current_task] == true) {
			/*	The start from beginning flag is set at power-up and when a
				task is reset/restarted or has returned.  Note task0 was started
				from the power-up code, all other tasks have the flag set
				at power up.  Reset the flag so the task resumes from 
				where it left off in the next go-round. */
			start_from_beginning[current_task] = false;
			/*	Since it is a virgin start, the task gets a virgin stack.
				cli/sei are needed for the AVR where the SP is set by two
				8-bit register-register transfers.  An interrupt in the middle
				would be a small disaster. */
			_set_SP_register (starting_stack[current_task]);
			/*	Give control to the task. */
			start_addresses[current_task] ();
			/*	If a task should execute a return the the uP will come to
				this spot.  The task is taken out of circulation.  The start_
				from_beginning flag is set in case the task is made active. */
			suspended[current_task] = true;
			start_from_beginning[current_task] = true;
		}
		else {
			/*	This is the normal round robin return-to-task point.  The
				tasks stack and registers are restored.

				Note that as tasks enter and exit through relinquish any
				code the compiler may add for function entry/exit is automatically
				'cancelled out.'  The GCC compiler will change this code with
				optimization level. */
			 _set_SP_register (sp_save[current_task]);
			POPALL();
			return;
		}
	}
}

int main (void) {
	/*	Initialize the CoRTOS variables, a bit skinnyed down for this
		demonstration program. */
	starting_stack[0] = _get_SP_register();
	starting_stack[1] = _get_SP_register() - 80;

	start_from_beginning[0] = false;
	start_from_beginning[1] = true;

	suspended[0] = false;
	suspended[1] = false;

	timer[0] = 0;
	timer[1] = 0;
	timer_active[0] = false;
	timer_active[1] = false;

	initialize_io_and_interrupts ();
	__enable_interrupt ();

	/*	Pass control to task0 - the one whose start address is at position
		0 in the start addresses array. */
	current_task = 0;
	start_addresses[0] ();

	/*	task0 is different from the other tasks - if it executes a return
		then control passes here and the OS stops.  In an embedded system
		there is no return from main() - there is no OS for the program to
		return to. */
	while (1)
		;
	/*	Compiler complains if there is no return value */
	return (0);
}

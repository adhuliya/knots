/*	CoRTOSblinkyPIC.c - Stand alone demo

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	Microchip PIC24F MPLAB/XC16

	A stand-alone 'blinky' demonstration of the CoRTOS Cooperative
	Real Time Operating System.

	It demonstrates the kernel and the time delay extension to the
	basic OS.

	Code has been skinned down for this demo file. */

#include "p24FJ128GA204.h"

#include "CoRTOSuP.h"
#include "CoRTOScomdefs.h"

/*	Turn off the watchdog timer, otherwise the code
	runs for 2 minutes, 11 seconds and the processor halts. */
#pragma config FWDTEN = OFF

/*	Change I/O assignments as needed for your hardware -
	this works with a Microchip DM240004 "Curiosity" PIC24F
	development board. */
#define LED1_DIR TRISCbits.TRISC5
#define LED1 LATCbits.LATC5
#define LED_ON  1
#define LED_OFF 0

void led_on (void);
void led_off (void);
void initialize_io_and_interrupts (void);
void task0 (void);
void task1 (void);
void service_timers (void);
void delay (uint16_t ticks);
void suspend (void);
void resume_task (uint8_t tn);
void relinquish (void);
int main (void);

/*	Task number of the executing task - this can be useful for
	array indexing and for calls to the OS. */

uint8_t current_task;

/**********************************************************************
*
*	PIC I/O
*
**********************************************************************/

/*	The interrupt is triggered 10mSec period on output
	compare using timer 1.  Its function is to decrement
	the timers of any delayed tasks via a call to service_timers(). */

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt (void) {
	IFS0bits.T1IF = 0;
	service_timers ();
}


void led_on (void) {
	LED1 = LED_ON;
}

void led_off (void) {
	LED1 = LED_OFF;
}

void initialize_io_and_interrupts (void) {
	/*	8MHz processor, 4 cycles/Hz => 2MHz / 8 = 250kHz */
 	T1CON = 0x0010;
	TMR1 = 0x0000;
	/*	250kHz / 2,500 = 100Hz*/
	PR1 = 2500;
	IPC0bits.T1IP = 0x01;
	IFS0bits.T1IF = 0;
	IEC0bits.T1IE = 1;
	T1CONbits.TON = 1;
	LED1_DIR = 0;
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
	while (1)
	{
		/*	"Let there be light," and wait for 1 second. */
		led_on ();
		delay (100);
	}
}

void task1 (void) {
	while (1)
	{
		/*	Allow task0's light - for 0.5 seconds. */
		delay (50);
		/*	Followed by 0.5 seconds of darkness. */
		led_off ();
		delay (50);
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

#define number_of_timers 2
static uint16_t timer [number_of_timers];
static boolean timer_active [number_of_timers] = {false, false};
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

#define PUSHALL() asm volatile \
	(							\
		"push w8  \n\t"	\
		"push w9  \n\t"	\
		"push w10 \n\t"	\
		"push w11 \n\t"	\
		"push w12 \n\t"	\
		"push w13 \n\t"	\
		"push w14 \n\t"	\
	:::)

#define POPALL() asm volatile  \
	(							\
		"pop w14 \n\t"		\
		"pop w13 \n\t"		\
		"pop w12 \n\t"		\
		"pop w11 \n\t"		\
		"pop w10 \n\t"		\
		"pop w9  \n\t"		\
		"pop w8  \n\t"		\
	:::)

/**********************************************************************
*
*	Kernel
*
**********************************************************************/

static uint16_t sp_save [number_of_tasks];
static uint16_t starting_stack [number_of_tasks];
static boolean start_from_beginning [number_of_tasks];
static boolean suspended [number_of_tasks];

/*	suspend() and resume() cause relinquish() to skip tasks that are blocked,
	in this demo they are blocked by being delayed. */

void suspend (void) {
	suspended[current_task] = false;
}

void resume_task (uint8_t tn) {
	suspended[tn] = true;
}

/*	Relinquish is the heart of CoRTOS.

	It is a round-robbin task scheduler.

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
	sp_save[current_task] = WREG15;

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
			/*	This is mostly the case for tasks when the system starts.
				task0 (the task at start_addresses[0]) however has been
				started when the system was put into motion. */
			start_from_beginning[current_task] = false;
			WREG15 = starting_stack[current_task];
			start_addresses[current_task] ();

			/*	If a task should execute a return the the uP will come to
				this spot.  The task is taken out of circulation.  The start_
				from_beginning flag is set in case the task is made active. */
			suspended[current_task] = true;
			start_from_beginning[current_task] = true;
		}
		else {
			/*	This is the normal round robbin return-to-task point.  The
				tasks stack and registers are restored.

				Note that as tasks enter and exit through relinquish any
				code the compiler may add for function entry/exit is automatically
				'cancelled out.'  The GCC compiler will change this code with
				optimization level. */
			WREG15 = sp_save[current_task];
			POPALL();
			return;
		}
	}
}

int main (void) {
	/*	Initialize the CoRTOS variables, a bit skinnyed down for this
		demonstration program. */
	starting_stack[0] = WREG15;
	starting_stack[1] = WREG15 + 100;

	start_from_beginning[0] = false;
	start_from_beginning[1] = true;

	suspended[0] = false;
	suspended[1] = false;

	timer[0] = 0;
	timer[1] = 0;
	timer_active[0] = false;
	timer_active[1] = false;

	initialize_io_and_interrupts ();

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
}
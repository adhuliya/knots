/*	CoRTOSblinkyAVR.c

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	AVR ATMega168/328, AVR Studio, GCC/WinAVR compiler.

	A stand-alone 'blinky' demonstration of the CoRTOS Cooperative
	Real Time Operating System.

	It demonstrates the kernel and the time delay extension to the
	basic OS.

	Code has been skinnyed down for this demo file. */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "CoRTOSuP.h"
#include "CoRTOScomdefs.h"

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
*	avr I/O
*
**********************************************************************/

/*	The interrupt is triggered 10mSec period on output
	compare A using timer 1.  Its function is to decrement
	the timers of any delayed tasks via a call to service_timers(). */

ISR (TIMER1_COMPA_vect) {
	sei ();
	service_timers ();

	/*	The flags are supposed to be reset in the H/W, but that seems
		to be an iffy thing accross the AVR processors.
				  76543210 */
	TIFR1 =  0b00000010;
	TIMSK1 = 0b00000010;
}

/*	Change port as needed for your hardware - this works with an
	STK500 with the LEDs plugged with a ribbon cable to PortD and
	blinks the on-board LED on the Atmel ATmega328PB Xplained Mini
	demonstration board. */

void led_on (void) {
/*	Xplained */
	PORTB |= bit5;

/*	STK500 */
	PORTD &= ~bit0;
}

void led_off (void) {
/*	Xplained */
	PORTB &= ~bit5;

/*	STK500 */
	PORTD |= bit0;
}

void initialize_io_and_interrupts (void) {

/*	Xplained  76543210 */
	PORTB = 0b11011111;
	DDRB =  0b00100000;

/*	STK500    76543210 */
	PORTD = 0b11111111;
	DDRD =  0b11111111;

/*	OCRA, 1/64 prescale on timer 1
				  76543210 */
	TCCR1B = 0b00001011;

/*	Set up the output compare register for timer 1 for
	a 10 mSec. overflow, reload and interrupt.  Xplained
	board runs at 16MHz (among other frequencies), STK500
	at 8 MHz.

	OCRA = 0x04e2 = 1,250;  8MHz clock / 64 / 1,250 = 10mS
	OCRA = 0x09c4 = 2,500; 16MHz clock / 64 / 2,500 = 10mS */

	OCR1AH = 0x09;
	OCR1AL = 0xc4;

	/*	Turn on the overflow interrupt.
				  76543210 */
	TIMSK1 = 0b00000010;
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
	second.

	If you are running this code in the *emulator* feature of AVR studio
	you may want to change the delays to 2 ticks and 1 tick to make
	the emulation run faster. */

void task0 (void) {
	while (1) {
		/*	"Let there be light," and wait for 1 second. */
		led_on ();
		delay (100);
	}
}

void task1 (void) {
	while (1) {
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

/*	The GCC compiler for AVR processors expects a whole raft of registers
	to be saved accross function calls.  The compiler, however, never
	makes use of most of the registers. The following is doing it by
	the book. */

#define PUSHALL() asm volatile \
	(								\
		"push r2  \n\t"		\
		"push r3  \n\t"		\
		"push r4  \n\t"		\
		"push r5  \n\t"		\
		"push r6  \n\t"		\
		"push r7  \n\t"		\
		"push r8  \n\t"		\
		"push r9  \n\t"		\
		"push r10 \n\t"		\
		"push r11 \n\t"		\
		"push r12 \n\t"		\
		"push r13 \n\t"		\
		"push r14 \n\t"		\
		"push r15 \n\t"		\
		"push r16 \n\t"		\
		"push r17 \n\t"		\
		"push r28 \n\t"		\
		"push r29 \n\t"		\
	)

#define POPALL() asm volatile \
	(								\
		"pop r29 \n\t"			\
		"pop r28 \n\t"			\
		"pop r17 \n\t"			\
		"pop r16 \n\t"			\
		"pop r15 \n\t"			\
		"pop r14 \n\t"			\
		"pop r13 \n\t"			\
		"pop r12 \n\t"			\
		"pop r11 \n\t"			\
		"pop r10 \n\t"			\
		"pop r9  \n\t"			\
		"pop r8  \n\t"			\
		"pop r7  \n\t"			\
		"pop r6  \n\t"			\
		"pop r5  \n\t"			\
		"pop r4  \n\t"			\
		"pop r3  \n\t"			\
		"pop r2  \n\t"			\
	)

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
	suspended[current_task] = true;
}

void resume_task (uint8_t tn) {
	suspended[tn] = false;
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
	sp_save[current_task] = SP;

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
			cli ();
			SP = starting_stack[current_task];
			sei ();
			/*	Give control to the task. */
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
			cli ();
			SP = sp_save[current_task];
			sei ();
			POPALL();
			return;
		}
	}
}

int main (void) {
	/*	Initialize the CoRTOS variables, a bit skinnyed down for this
		demonstration program. */
	starting_stack[0] = SP;
	starting_stack[1] = SP - 60;

	start_from_beginning[0] = false;
	start_from_beginning[1] = true;

	suspended[0] = false;
	suspended[1] = false;

	timer[0] = 0;
	timer[1] = 0;
	timer_active[0] = false;
	timer_active[1] = false;

	initialize_io_and_interrupts ();
	sei ();

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
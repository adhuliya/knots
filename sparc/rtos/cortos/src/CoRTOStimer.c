/*	CoRTOStimer.c

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

#include "CoRTOSuP.h"
#include "CoRTOScomdefs.h"
#include "CoRTOSkernel.h"
#include "CoRTOSsignal.h"
#include "CoRTOStask.h"
#include "CoRTOStimer.h"

#define timer_inactive 0
#define timer_type_delay 1
#define timer_type_periodic 2
#define timer_type_countdown 3
static uint8_t timer_type [number_of_timers];

static uint16_t timer [number_of_timers];
static boolean timer_paused [number_of_timers];

/*	Can be removed if periodic timers are not used. */
static uint8_t periodic_signal_number [number_of_timers];
static uint16_t periodic_period [number_of_timers];

/*	Can be removed if the delay & timeout functions aren't used. */
static uint8_t delayed_task_number [number_of_timers];

/************************************************************************
*
*	initialize
*
************************************************************************/

/*	This function needs to be called from main() if timer functions
	are used in the application. */

void initialize_delay_module (void) {
	uint8_t tin;
	for (tin = 0; tin < number_of_timers; tin++) {
		timer_type[tin] = timer_inactive;
	}
}

/************************************************************************
*
*	service timers
*
************************************************************************/

/*	Called by the timer ISR every 'tick', thus defining the value of a
	tick. */
void service_timers (void) {
	static uint8_t tin, tt;
	for (tin = 0; tin < number_of_timers; tin++) {
		tt = timer_type[tin];
		if ((tt != timer_inactive) && (timer_paused[tin] == false)) {
			if (timer[tin] == 0) {
				switch (tt) {
					/*	Comment out/delete this case code if periodic signaling isn't
						used.  Otherwise the linker will complain it can't find send_signal(). */
					case timer_type_periodic:
						send_signal (periodic_signal_number[tin]);
						timer[tin] = periodic_period[tin];
						break;
					case timer_type_delay:
						resume_task (delayed_task_number[tin]);
						/*	Fall through */
					case timer_type_countdown:
						timer_type[tin] = timer_inactive;
					default:
						break;
				}
			} else {
				--timer[tin];
			}
		}
	}
}

/************************************************************************
*
*	Delay
*
************************************************************************/

/*	Delays the calling task for so many ticks.  The task suspends itself
	and is resumed by service_timers(), above.

	The code can be removed if the delay() feature isn't used. */

void delay (uint8_t tin, uint16_t ticks) {
	timer_type[tin] = timer_inactive;
	timer[tin] = ticks;
	timer_paused[tin] = false;
	delayed_task_number[tin] = current_task;
	suspend ();
	timer_type[tin] = timer_type_delay;
	relinquish ();
}

/************************************************************************
*
*	Periodic signals
*
************************************************************************/

/*	Periodic signals are sent to the designated signal - sin.  It is up
	to the task to pick them up with wait_for_signal, in the signal module.

	This code, and the accomponying service_timers() code can be removed
	if periodic signals aren't used.

	If the periodic signal needs to stopped for a period of time then
	pause_timer()/resume_timer() should be used. */

void start_periodic_signal (uint8_t tin, uint8_t sin, uint8_t ticks) {
	timer_type[tin] = timer_inactive;
	timer[tin] = ticks;
	timer_paused[tin] = false;
	periodic_period[tin] = ticks;
	periodic_signal_number[tin] = sin;
	timer_type[tin] = timer_type_periodic;
}

void stop_periodic_signal (uint8_t tin) {
	timer_type[tin] = timer_inactive;
}

/************************************************************************
*
*	Countdown timers
*
************************************************************************/

/*	The timer counts down and then stops.  Check timer can be called
	to see how much time, in ticks, is left.

	If these functions are not used then they can be edited out to free
	up code memory space. */

void start_countdown_timer (uint8_t tin, uint16_t ticks) {
	timer_type[tin] = timer_inactive;
	timer[tin] = ticks;
	timer_paused[tin] = false;
	timer_type[tin] = timer_type_countdown;
}

/************************************************************************
*
*	Timeouts
*
************************************************************************/

/*	Timeouts are used in conjuction with waiting for messages, signals
	and resources (MSR).  The timeout is started ahd then the wait call is made.

	It is very important to call stop_timeout() after successfully acquiring
	an MSR, otherwise a spurious resume() call may be made by service_timers().

	If the timer comes back from the wait call without the MSR
	then it was brought back to life by the timeout expiration.

	A return value of 0 from check_timer() also indicates the task timed
	out.

	An example:

		start_timeout (timer_x, 100);
		resource_status = acquire_resource (resource_x, true);
		stop_timout (timer_x);
		switch (resource_status)
		{
			case status_timeout:
				...time out action...
				break;
			...
		}
*/

void start_timeout (uint8_t tin, uint16_t ticks) {
	timer_type[tin] = timer_inactive;
	timer[tin] = ticks;
	timer_paused[tin] = false;
	delayed_task_number[tin] = current_task;
	timer_type[tin] = timer_type_delay;
}

uint16_t stop_timeout (uint8_t tin) {
	timer_type[tin] = timer_inactive;
	return (timer[tin]);
}

/************************************************************************
*
*	Misc. check/pause/resume
*
************************************************************************/

uint16_t check_timer (uint8_t tin) {
	uint16_t local_time [2];
	/*	Do two reads to insure that the timer value didn't get stomped on
		by service_timers() during the read.  Not needed in 16 bit systems
		that can read an uint16_t as an atomic operation. */
	do {
		local_time[0] = timer[tin];
		local_time[1] = timer[tin];
	} while (local_time[0] != local_time[1]);
	return (local_time[0]);
}

void pause_timer (uint8_t tin) {
	timer_paused[tin] = true;
}

void resume_timer (uint8_t tin) {
	timer_paused[tin] = false;
}

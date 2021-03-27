/*	CoRTOSsignal.c - ISR->task & task->task signaling

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

#include "CoRTOSuP.h"
#include "CoRTOScomdefs.h"
#include "CoRTOSkernel.h"
#include "CoRTOStask.h"
#include "CoRTOSsignal.h"

/************************************************************************
*
*	Local variables
*
************************************************************************/

/*	The number of signals is defined in CoRTOStask.h - this is the file that
	defines the application to CoRTOS. */

/*	This tail-chasing scheme lets ISR's and tasks both use the
	signal counters without risk of collision or the need for turning
	off interrupts.  Interrupts increment sig_add; tasks increment sig_sub.
	The signal count is the difference between add and sub.  If equal then
	no signals are present.  add/sub are both circular. */
static volatile uint8_t sig_add [number_of_signals];
static volatile uint8_t sig_sub [number_of_signals];

/*	The task number of a task waiting upon a signal, set to 0xff if there
	is no task waiting.  If the sender sees a task is waiting then it
	will set that task to active. */
static uint8_t sig_waiting_task [number_of_signals];

/************************************************************************
*
*	Global functions
*
************************************************************************/

/*	Called by an ISR (or, alternatively, another task) to send a signal
	to a task.  The task would receive the signal upon calling
	wait_for_signal ().

	If the task is not picking up its signals then a return of status_full
	will be made when a signal counter reaches 0xff signals. */

status_t send_signal (uint8_t sin)
{
	if ((sig_add[sin] + 1) == sig_sub[sin])
		return (status_full);

	/*	CAUTION CAUTION CAUTION CAUTION CAUTION CAUTION CAUTION CAUTION

		In the >>very rare case<< that signals are sent to the >>same
		counter<< by ISRs that run at different priorities (ie one can
		interrupt the other) or by both a task and an interrupt then
		an disable/enable needs to bracket this increment instruction.
		There is the posibility of signals getting lost if the higher
		priority interrupt stomps on the lower priority interrupt
		while the signal counter is being incremented.

		This requirement is >>not needed<< if:

		o	The system >>doesn't<< have nested interrupts that use the same
			signal counter - this is normally the case;

		- or -

		o	The processor can perform the increment atomicaly - as with
			the x86 and MSP430. Check the disassembly listing if in doubt
			on atomicity. */

	// disable ();
	sig_add[sin]++;
	//	enable ();

	if (sig_waiting_task[sin] != 0xff)
	{
		resume_task (sig_waiting_task[sin]);
		sig_waiting_task[sin] = 0xff;
	}
	return (status_ok);
}

/*	wait_for_signal () first indicates to the sender that it is waiting
	for a signal.  It then checks for the presence of signals, and
	if there are none then it relinquishes().  The calling task's
	suspend flag is cleared with a resume() from send_signal();
	in the case there were signals available there would have
	been no resume() call to a waiting task made by the signal sender.
	If the task	had relinquished control and been resumed by the signal
	sender (or a timeout) the extra resume() call will have no effect.

	If no signals are available after the task continues then the task
	was resumed by a timeout, in this case the return value is 0 signals.

	If signals are available then the count is decremented and the number
	of signals present at resumption is returned.  The normal case
	is 1 signal. */

uint8_t wait_for_signal (uint8_t sin)
{
	uint8_t sig_count;

	/*	We suspend early on.  We have to guard agains the possibility
		the interrupt comes in resuming the task before it has suspended
		itself.  An extra resume from the interrupt has no effect on a
		non-suspended task.  */
	suspend ();
	sig_waiting_task[sin] = current_task;

	if (sig_sub[sin] == sig_add[sin])
		relinquish ();

	sig_waiting_task[sin] = 0xff;
	/*	Cancel the suspend if it wasn't used because signals were already
		available. */
	resume_task (current_task);

	sig_count = sig_add[sin] - sig_sub[sin];
	/*	It is possible the signal count is 0 if the task was resumed
		by a timeout.  If not a time-out (or just a serendipitous
		interrupt) then decrement the available signals. */
	if (sig_count != 0)
		sig_sub[sin]++;
	return (sig_count);
}

void clear_signals (uint8_t sin)
{
	sig_sub[sin] = sig_add[sin];
}

uint8_t check_signals (uint8_t sin)
{
	return (sig_add[sin] - sig_sub[sin]);
}

void initialize_signal_module (void)
{
	uint8_t sin;

	for (sin = 0; sin < number_of_signals; sin++)
	{
		sig_waiting_task[sin] = 0xff;
		sig_add[sin] = 0;
		sig_sub[sin] = 0;
	}
}

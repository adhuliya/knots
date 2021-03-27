/*	CoRTOSsem.c - Semaphores

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	Provides a semaphore facility for the CoRTOS real time OS.

	Both binary and counting semaphores are supported.
		o	Binary semaphores for control of a shared resource have
			their count set to 1 after the resource has been initialized.
		o	Counting semaphores have their count set to > 1 after the
			resource has been initialized.
		o	Signaling semaphores have a count of 0 (the default value)
			and a semaphore count is released to send a signal and acquired to
			receive a signal.

	Semaphores counts CAN NOT be released from interrupts.  Use signals instead. */

#include "CoRTOSuP.h"
#include "CoRTOScomdefs.h"
#include "CoRTOSkernel.h"
#include "CoRTOStask.h"
#include "CoRTOSsem.h"

/************************************************************************
*	General purpose queuing
************************************************************************/

/*	This code would normally go in a seperate queuing module.  Queuing
	is only used by the semaphore code - and so it is merged into
	this module. */

/*	A que consists of only a head and tail index.  These indeces hold the
	indeces in the forward and backward arrays.  It is the forware &
	backward arrays that make up a double linked que. */
typedef struct {
	uint8_t head;
	uint8_t tail;
} queue_type;
typedef queue_type * queue_pointer_t;

/*	The forward and backward links serve for all the queues in the system -
	with the obvious restriction that a task can only be in one queue at a
	time.  They are indexed by task number and each task has its own entry
	in the arrays. */
static uint8_t forward [number_of_tasks];
static uint8_t backward [number_of_tasks];

static void add_to_queue (uint8_t tn, queue_pointer_t qp);
static void remove_from_queue (uint8_t tn, queue_pointer_t qp);
static void initialize_queues (queue_pointer_t qp, uint8_t number_of_queues);

void add_to_queue (uint8_t tn, queue_pointer_t qp) {

/*	Adds item tn to the tail of queue qp. */

	if (qp->head == 0xff) {
		/*	Empty queue */
		qp->head = tn;
		backward[tn] = 0xff;
	} else {
		/*	Add to tail of queue */
		forward[qp->tail] = tn;
		backward[tn] = qp->tail;
	}
	qp->tail = tn;
	forward[tn] = 0xff;
}

void remove_from_queue (uint8_t tn, queue_pointer_t qp) {

/*	Removes item tn from any location in queue qp. */

	if (forward[tn] == 0xff) {
		/*	No following item. */
		if (backward[tn] == 0xff) {
			/*	No backward item either, so this is the only
				item on the queue */
			qp->head = 0xff;
			qp->tail = 0xff;
		} else {
			/*	There is an item before this one so this is
				the last item on the queue */
			qp->tail = backward[tn];
			forward[backward[tn]] = 0xff;
		}
	} else {
		/*	There are items following this one. */
		if (backward[tn] == 0xff) {
			/*	But there is nothing before it so this is the
				first item on tne queue */
			qp->head = forward[tn];
			backward[forward[tn]] = 0xff;
		} else {
			/*	If all else fails then this must be a middle
				item on the queue. */
			forward[backward[tn]] = forward[tn];
			backward[forward[tn]] = backward[tn];
		}
	}
}

static void initialize_queues (queue_pointer_t qp, uint8_t number_of_queues) {
	uint8_t n;
	/*	Initializes all the queues in an array of queues starting with qp.
		0xff is the indication that a queue is empty. */
	for (n = 0; n < number_of_queues; n++) {
		qp->head = 0xff;
		qp++;
	}
}

/************************************************************************
*	Semaphore code
************************************************************************/

static uint8_t sem_count [number_of_sems];
static queue_type sem_queue [number_of_sems];
static boolean acquired [number_of_tasks];

status_t acquire_sem (uint8_t semn, boolean wait) {

	/*	Called to acquire a count from semaphore semn.  If no count is available
		then the caller may either wait for a count or return early.

		Return values are:

			status_ok		task has acquired a count from the semaphore
			status_unavail	no count is available and the task doesn't want to wait
			status_timeout	A timeout was started before acquire_sem()
								was called and it has expired, the task did not acquire
								a count from the semaphore
	*/

	if (sem_count[semn] > 0) {
		/*	A count was available so we take it. */
		sem_count[semn]--;
		return (status_ok);
	}

	acquired[current_task] = false;

	/*	No count, and we don't want to wait for one. */
	if (wait == false)
		return (status_unavail);

	/*	Add this task to the list of tasks queuing for a count. */
	add_to_queue (current_task, &sem_queue[semn]);

	/*	Now wait for a count */
	suspend ();
	relinquish ();

	/*	We have a count, maybe. */

	if (acquired[current_task] == false) {
		/*	The assumption is that if we didn't get the count then
			the reason for our resumption is a timeout.  However,
			We are still in the queue of tasks waiting for a count
			so we have to remove ourselves from the queue. */
		remove_from_queue (current_task, &sem_queue[semn]);
		return (status_timeout);
	}

	/*	A semaphore count was released and that is the reason we
		woke up. */
	return (status_ok);
}

void release_sem (uint8_t semn) {

/*	After a task is done using a semaphore count it releases it to either
	the free state or it advances the queue and gives the count
	over to a new owner.

	DO NOT call this function from an interrupt. */

	uint8_t tn;

	tn = sem_queue[semn].head;

	/*	Nobody waiting, just increment the count and we are done. */
	if (tn == 0xff) {
		sem_count[semn]++;
		return;
	}

	/*	Task waiting, pull its task number from the queue and set
		the task back to active.  There is no need to decrement the
		count as we haven't incremented it.

		WARNING: Note that we don't increase the count and then let the
		waiting task decrease it.  The reason for this is the danger of
		a task waiting in the rotation that then requests & acquires the
		count ahead of the intended recipient, this would leave two tasks
		'owning' the same count. */
	remove_from_queue (tn, &sem_queue[semn]);
	resume_task (tn);
	acquired[tn] = true;
}

void set_sem_count (uint8_t semn, uint8_t count) {
	uint8_t tn;

	/*	Setting the count to 0 is a special case, there is
		no need to check for waiting tasks. */
	if (count == 0) {
		sem_count[semn] = 0;
		return;
	}

	while ((count != 0) && ((tn = sem_queue[semn].head) != 0xff)) {
		/*	A bit elaborate but it is possible to have multiple queuing
			tasks and the count set to >1.  See the warning at the end
			of release sem. */
		count--;
		remove_from_queue (tn, &sem_queue[semn]);
		acquired[tn] = true;
		resume_task (tn);
	}
	sem_count[semn] = count;
}

uint8_t query_sem_count (uint8_t semn) {
	return (sem_count[semn]);
}

void initialize_sem_module (void) {
	initialize_queues (sem_queue, number_of_sems);
}




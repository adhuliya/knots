/*	CoRTOSmessage.c

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	Provides a facility for passing messages (well, pointers to
	messages) from task->task.

	This module is not designed for ISR->task messaging.  Use
	the signal module for this.  Alternatively this module could
	be re-written along the lines of the signal module (using
	a msg_add/msg_sub to keep track of the # of messages) if a lot
	of ISR->task messaging is required. */

#include "CoRTOSuP.h"
#include "CoRTOScomdefs.h"
#include "CoRTOSkernel.h"
#include "CoRTOStask.h"
#include "CoRTOSmessage.h"

/*	Queues may be used by any task.  If a lot of intertask messaging
	is done it may be convenient to have the number of message queues
	equal to the number of tasks.  Each task then has it's own queue
	and the task number and queue number are the same.  It is also
	possible for a task to draw from more than one message queue. */

/*	Rather than queuing the data this scheme queues pointers to the
	data.  In some occasions it may be preferable to queue the message
	itself rather than a pointer. */
static void * messages [number_of_msg_queues][msg_queue_size];

/*	The message ques are circular with the remove index chasing the
	add index */
static uint8_t msg_add_index [number_of_msg_queues];
static uint8_t msg_remove_index [number_of_msg_queues];

/*	Keeping track of the count makes life easier, the expenditure
	in RAM is paid for by a reduction in program size. */
static uint8_t msg_counter [number_of_msg_queues];

/*	The task numbers of waiting tasks, a value of 0xff indicates
	no task is waiting. */
static uint8_t msg_waiting_task_number [number_of_msg_queues];

/*	Adds a pointer to a message into a que specified by
	'mqn'.  Returns status_ok if all went well, returns
	status_full if the que is full of messages - indicating
	a design problem as this should never happen in
	a properly designed system. */
status_t send_message (uint8_t mqn, void * msg_pointer)
{
	/*	An attempt to speed/reduce code. */
	uint8_t add_index;

	/*	No room at the queue. */
	if (msg_counter[mqn] == msg_queue_size)
		return (status_full);

	add_index = msg_add_index[mqn];
	messages[mqn][add_index] = msg_pointer;

	/*	if() is faster/smaller than a % operator. */
	if (++add_index == msg_queue_size)
		add_index = 0;
	msg_add_index[mqn] = add_index;
	msg_counter[mqn]++;

	if (msg_waiting_task_number[mqn] != 0xff)
	{
		resume_task (msg_waiting_task_number[mqn]);
		msg_waiting_task_number[mqn] = 0xff;
	}

	return (status_ok);
}

/*	The calling task is returned a pointer to a message.
	The task will suspend itself to wait for
	the message.  If a wait with timeout is desired it
	can be made by starting a timeout and then calling
	wait_for_message() - a NULL pointer will be returned
	if the timeout expired.  Be sure to stop the timeout. */

void * wait_for_message (uint8_t mqn)
{
	/*	Index to where the message is at:  We increment
		msg_remove_index, losing its value in mod arithmetic,
		so we keep a local copy. */
	uint8_t remove_index;

	/*	The task waits if there are no messages. */
	if (msg_counter[mqn] == 0)
	{
		suspend ();
		msg_waiting_task_number[mqn] = current_task;
		relinquish ();
		/*	See if it is a timeout that made the task active again. */
		if (msg_counter[mqn] == 0)
			return (NULL);
	}

	/* Pull the message from the queue. */
	remove_index = msg_remove_index[mqn];
	if (++msg_remove_index[mqn] == msg_queue_size)
		msg_remove_index[mqn] = 0;
	msg_counter[mqn]--;
	return (messages[mqn][remove_index]);
}

/*	If check_messages() indicates message(s) are available then the
	messages can be retrieved by wait_for_message(). */
uint8_t check_messages (uint8_t mqn)
{
	return (msg_counter[mqn]);
}

void initialize_message_module (void)
{
	uint8_t mqn;

	for (mqn = 0; mqn < number_of_msg_queues; mqn++)
	{
		msg_add_index[mqn] = 0;
		msg_remove_index[mqn] = 0;
		msg_counter[mqn] = 0;
		msg_waiting_task_number[mqn] = 0xff;
	}
}


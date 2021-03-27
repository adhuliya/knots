/*	CoRTOStask.c - Defines the task arrays, and possibly the tasks.

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

/*	This is a place holder dummy module with do nothing tasks.
	If used as a templae then CoRTOStask.h should be modified
	so the two files agree. */

#include "CoRTOSuP.h"
#include "CoRTOScomdefs.h"
#include "CoRTOSkernel.h"
#include "CoRTOStask.h"

void task0 (void);
void task1 (void);
void task2 (void);
void task3 (void);

#ifdef uP_32bit
uint16_t task_stack_size [number_of_tasks] =
	{200, 200, 200, 200};
#else
uint16_t task_stack_size [number_of_tasks] =
	{80, 80, 80, 80};
#endif

void task0 (void)
{
	while (true)
		relinquish ();
}

void task1 (void)
{
	while (true)
		relinquish ();
}

void task2 (void)
{
	while (true)
		relinquish ();
}

void task3 (void)
{
	while (true)
		relinquish ();
}

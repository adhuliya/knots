/*	CoRTOStask.h - Data that tells CoRTOS about the user's
	system - how many tasks, signals, etc.

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

/*	Tasks are void functions taking no parameters.  Addresses may
	be 16 or 32 bits, the compiler picks the right size. */
typedef void (* task_address_type) (void);

/*	These may be defined in CoRTOStask.c, in the module containing
	main() or anyplace else convenient.  The data is only used by
	the CoRTOS kernel. */
extern task_address_type start_addresses [];
extern uint16_t task_stack_size [];

/*	The size of everything.  The numbers here are compatible with
	CoRTOSsuperblinky???.c - change them to the values used in your system. */

#define number_of_tasks 8

#define number_of_signals 8

#define number_of_msg_queues 8
#define msg_queue_size 8

#define number_of_timers 8

#define number_of_sems 8


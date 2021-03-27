/*	CoRTOSkernel.c - Kernel for CoRTOS

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

/*	uP specific include files - these will need to be modified
	depending on the variant of the processor you are using.
	You have hopefully already encountered and triumphed over
	this adversity: make changes as you see fit. */
#include "CoRTOSuP.h"
#ifdef uP_AVR
#include <avr\io.h>
#include <avr\interrupt.h>
#elif uP_MSP430
#include "msp430fr6989.h"
#elif uP_PIC24
#include "p24FJ128GA204.h"
#elif uP_Cortex_M0
#include "sam.h"
#endif

#include "CoRTOScomdefs.h"
#include "CoRTOStask.h"
#include "CoRTOSkernel.h"

/**********************************************************************
*
*	Public variables
*
**********************************************************************/

/*	current_task is a global because it can be very useful when either
	making OS calls - the call then refers to the calling task.  It
	can also be used when tasks access arrays of variables where each
	task has its own copy of the variable(s) in the array. */
uint8_t current_task;

/**********************************************************************
*
*	The local OS Kernel variables
*
**********************************************************************/

/*	The system saves the stack pointer for each task when it relinquishes
	control, and then restores it when the task gets control again.
	The starting stack is the top of the stack for each task -
	used when a task is started from its entry point. */
static stack_address_t sp_save [number_of_tasks];
static stack_address_t starting_stack [number_of_tasks];

/*	Indicates a task is to start from its entry point, normal for all
	tasks when they first get control.  The flag is set again if a task
	executes a return.  Also see the reset/restart functions. */
static boolean start_from_beginning [number_of_tasks];

/*	Reset if a task executes a return.  Would need to be reset by an
	external agency for the task to execute again.  Manipulated
	by the suspend/resume functions. */
static boolean suspended [number_of_tasks];

/************************************************************************
*
*	relinquish () - the whole of CoRTOS in one function
*
************************************************************************/

void relinquish (void) {

	/*	Save whatever it is that the compiler expects to be saved - the clobber
		list includes all relevant registers, the compiler then picks the ones
		that need pushing - this can change with optimization level.  Save the
		stack pointer so that we can get back to this task by reloading the
		saved value and then executing a return. */
#ifdef uP_AVR
	asm volatile ("NOP":::"r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r13","r14","r15","r16","r17","r28","r29");
	sp_save[current_task] = SP;
#elif uP_MSP430
	/*	TI's CCS compiler doesn't take clobber lists. */
	__asm (" push r4 \n push r5 \n push r6 \n push r7 \n push r8 \n push r9 \n push r10 \n push r11 \n");
	sp_save[current_task] =  _get_SP_register ();
#elif uP_PIC24
	asm volatile ("NOP":::"w8","w9","w10","w11","w12","w13");
    /* Compiler doesn't like w14 in a clobber list. */
	asm volatile ("push w14":::);
	sp_save[current_task] = WREG15;
#elif uP_Cortex_M0
//	asm volatile ("NOP":::"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r14");
	asm volatile ("NOP":::"r0","r1","r2","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","r14");
	sp_save[current_task] = __get_MSP();
#endif

	while (1) {
		do {
			/*	Circle through the tasks, the if() construct is much
				faster than using a mod % operator. */
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
#ifdef uP_AVR
			cli ();
			SP = starting_stack[current_task];
			sei ();
#elif uP_MSP430
			_set_SP_register (starting_stack[current_task]);
#elif uP_PIC24
			WREG15 = starting_stack[current_task];
#elif uP_Cortex_M0
			__set_MSP (starting_stack[current_task]);
#endif
			/*	Give control to the task. */
			start_addresses[current_task] ();
			/*	If a task should execute a return the the uP will come to
				this spot.  The task is taken out of circulation.  The start_
				from_beginning flag is set in case the task is made active. */
			suspended[current_task] = true;
			start_from_beginning[current_task] = true;
		}
		else {
			/*	Load the stack pointer for the new current task, current_task
				was incremented above.  Enable/disable only needed for 8 bit
				machines like the AVR.

				Note that as tasks enter and exit through relinquish any
				code the compiler may add for function entry/exit is automatically
				'cancelled out.'  The GCC compiler will change this code with
				optimization level. */
#ifdef uP_AVR
			cli ();
			SP = sp_save[current_task];
			sei ();
#elif uP_MSP430
			_set_SP_register (sp_save[current_task]);
			__asm (" pop r11 \n pop r10 \n pop r9 \n pop r8 \n pop r7 \n pop r6 \n pop r5 \n pop r4 \n");
#elif uP_PIC24
			WREG15 = sp_save[current_task];
			asm volatile ("pop w14":::);
#elif uP_Cortex_M0
			__set_MSP (sp_save[current_task]);
#endif
			/*	Go back to where this task called relinquish (). */
			return;
		}
	}
}

/************************************************************************
*
*	suspend/resume/restart ...
*
************************************************************************/

/*	A suspended task will be skipped over by relinquish(). */
void suspend (void) {
	suspended[current_task] = true;
}

/*	A resumed task will again be given control by relinquish(). */
void resume_task (uint8_t tn) {
	suspended[tn] = false;
}

/*	CAUTION:

	Be very careful when calling these two functions - be sure the
	task is not the owner of, or qued to, a resource, or has signals
	or messages pending.  These issues need to be dealt with
	seperately. */

/*	A restarted task will be given control by relinquish() starting
	from its entry point. */
void restart_task (uint8_t tn) {
	start_from_beginning[tn] = true;
	suspended[tn] = false;
}

/*	A reset task will be skipped over by relinquish(), if it is
	made active again by a call to resume_task() then it will
	begin from its entry point. */
void reset_task (uint8_t tn) {
	start_from_beginning[tn] = true;
	suspended[tn] = true;
}

/************************************************************************
*
*	start_CoRTOS
*
************************************************************************/

/*	This function is called from main() to start the OS.  It initializes
	the variables used by relinquish() for controling task execution.

	Control isn't given to the OS but to the first task, which then
	gives control to the OS on its first call to relinquish().

	This 'backwards into the future' method of starting a real time OS
	is rather common.  The tasks and the OS are co-routines that start
	each other in something resembling a dance. */

void start_CoRTOS (void) {
	uint8_t tn;
	stack_address_t spv;

	/*	The stack for the tasks is carved from stack allocated by the
		compiler for the whole program.  You need to be sure that this
		is adequate.  The GCC compiler seems to allocate stack from
		the top of RAM with the heap at the bottom of free RAM.  For
		most processors there is plenty of RAM available for the stacks.

		See the manual about a wrapper for the ISR's so that the ISRs will
		have their own stacks - this reduces the size of the stack
		required for each task.  As supplied CoRTOS requires each
		task's stack have enough room for pushing registers for the
		ISRs. */
#ifdef uP_AVR
	spv = SP;
#elif uP_MSP430
	spv =  _get_SP_register ();
#elif uP_PIC24
	spv = WREG15;
#elif uP_Cortex_M0
	spv = __get_MSP();
#endif

	for (tn = 0; tn < number_of_tasks; tn++) {
		starting_stack[tn] = spv;
#ifdef uP_PIC24
		spv += task_stack_size[tn];
#else
		spv -= task_stack_size[tn];
#endif
		start_from_beginning[tn] = true;
		suspended[tn] = false;
	}

	/*	The start_from_beginning flag is cleared as we start task0
		from its entry point.  Relinquish() will start task0
		again from the point where it surrenders control on calling
		relinquish() */
	start_from_beginning[0] = false;
	current_task = 0;
	start_addresses[0] ();

	/*	If the first task, with the task number 0, executes a return
		then control will pass to this point and CoRTOS will cease
		execution.

		Control will then pass to the code that called start_CoRTOS() */
}


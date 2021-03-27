/* CoRTOSkernel.h - CoRTOS Cooperative Real Time Operating System

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

extern uint8_t current_task;

void relinquish (void);
void suspend (void);
void resume_task (uint8_t tn);
void restart_task (uint8_t tn);
void reset_task (uint8_t tn);
void start_CoRTOS (void);

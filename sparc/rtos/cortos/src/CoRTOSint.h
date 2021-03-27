/*	CoRTOSint - Interrupts for test modules

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

void set_high_speed (boolean x);
void timer_int_disable (void);
void timer_int_enable (boolean force);

void initialize_interrupts (void);

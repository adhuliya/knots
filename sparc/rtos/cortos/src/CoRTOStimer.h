/* CoRTOStimer.h - delay/periodic signaling/timeout/countdown

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

void initialize_delay_module (void);
void service_timers (void);
void delay (uint8_t tin, uint16_t ticks);
void start_periodic_signal (uint8_t ptn, uint8_t sin, uint8_t ticks);
void stop_periodic_signal (uint8_t ptn);
void start_countdown_timer (uint8_t tin, uint16_t ticks);
void start_timeout (uint8_t tin, uint16_t ticks);
uint16_t stop_timeout (uint8_t tin);
uint16_t check_timer (uint8_t tin);
void pause_timer (uint8_t tin);
void resume_timer (uint8_t tin);



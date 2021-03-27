/* CoRTOSsignal.h - ISR->task signaling

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

status_t send_signal (uint8_t sn);
uint8_t wait_for_signal (uint8_t sn);
uint8_t check_signals (uint8_t sn);
void clear_signals (uint8_t sn);
void initialize_signal_module (void);


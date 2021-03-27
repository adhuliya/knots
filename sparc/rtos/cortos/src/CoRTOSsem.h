/* CoRTOSsem.h - Semaphores

	2018.12.12 12:00	Release 1.10

	(c) 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

status_t acquire_sem (uint8_t semn, boolean wait);
void release_sem (uint8_t semn);
void set_sem_count (uint8_t semn, uint8_t count);
uint8_t query_sem_count (uint8_t semn);
void initialize_sem_module (void);

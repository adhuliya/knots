/* CoRTOSmessage.h - task->task messaging

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

status_t send_message (uint8_t mqn, void * msg_pointer);
void * wait_for_message (uint8_t mqn);
uint8_t check_messages (uint8_t mqn);
void initialize_message_module (void);


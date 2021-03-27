/*	CoRTOSio.h - CoRTOS testing i/o module - led drive

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */


void initialize_IO (void);

void led_on (uint8_t led);
void led_off (uint8_t led);
void led_toggle (uint8_t led);
void led_translate (boolean control);

#ifdef uP_Cortex_M0
/*	Arduino I/O mapping (sorta) */
#define port_b (uint8_t)1
#define port_c (uint8_t)2
#define port_d (uint8_t)3
void init_M0_IO (uint8_t port, uint8_t output_bits);
void port_on (uint8_t port, uint8_t bit_pattern);
void port_off (uint8_t port, uint8_t bit_pattern);
void port_toggle (uint8_t port, uint8_t bit_pattern);
void port_output (uint8_t port, uint8_t bit_pattern);
#endif

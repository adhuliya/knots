/*	CoRTOSuP.h - Define the uP in use

	2018.12.12 12:00	Release 1.10

	(c) 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html
*/

/*	Select the microprocessor family.  Only one of these should be
	uncommented. */
//#define uP_AVR 1
#define uP_MSP430 1
//#define uP_PIC24 1
//#define uP_Cortex_M0 1

/*	These are only used in the CoRTOSio.c module - which in turn
	is only used for the test modules.  The
	purpose here is to map virtual leds to those present on an
	evaluation board. */
#ifdef uP_AVR
//#define uP_platform_SDK_500 1
#define uP_platform_ATMEGA328P_XMINI_sheild 1
//#define uP_platform_ATMEGA328P_XMINI 1
//#define uP_platform_ATMEGA1284P_XPLD 1
#endif

#ifdef uP_MSP430
#define variant_MSP430FR5994 1
#define uP_platform_MSP_EXP430FR5994 1
//#define variant_MSP430FR5969 1
//#define uP_platform_MSP_EXP430FR5969 1
//#define variant_MSP430FR6989 1
//#define uP_platform_MSP_EXP430FR6989 1
#endif

#ifdef uP_Cortex_M0
#define uP_32bit 1
//#define uP_platform_ATSAMD10_XMINI 1
#define uP_platform_ATSAMD10_XMINI_sheild 1
#endif

/*	CoRTOScomdefs.h - Common definitions

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html */

/*	Typedefs sometimes collide - allow the ones defined in the GCC/vendor
	headers to override. */
#ifdef uP_AVR
typedef unsigned char uint8_t;
// typedef char int8_t; /* AVR include file collides and the type is not used in CoRTOS */
typedef unsigned int uint16_t;
typedef int int16_t;
#elif uP_MSP430
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned int uint16_t;
typedef int int16_t;
#elif uP_PIC24
typedef unsigned char uint8_t;
typedef char int8_t;
typedef unsigned int uint16_t;
typedef int int16_t;
#elif uP_Cortex_M0
/*	Sometimes the <sam.h> file is included, causes conflicts */
#ifndef _UINT8_T_DECLARED
typedef unsigned char uint8_t;
#endif
// typedef char int8_t;
#ifndef _UINT16_T_DECLARED
typedef unsigned int uint16_t;
#endif
// typedef int int16_t;
// typedef long int32_t;
// typedef unsigned long uint32_t
#endif

#ifdef uP_32bit
typedef unsigned long stack_address_t;
#else
typedef unsigned int stack_address_t;
#endif

typedef unsigned char boolean;
#define true 1
#define false 0
//#define true (uint8_t)1
//#define false (uint8_t)0

#define NULL ((void *)0)

typedef unsigned char status_t;
#define status_ok (uint8_t)0x00
#define status_busy (uint8_t)0x01
#define status_full (uint8_t)0x02
#define status_timeout (uint8_t)0x04
#define status_unavail (uint8_t)0x08
#define status_error (uint8_t)0x80

#define bit0 (uint8_t)0x01
#define bit1 (uint8_t)0x02
#define bit2 (uint8_t)0x04
#define bit3 (uint8_t)0x08
#define bit4 (uint8_t)0x10
#define bit5 (uint8_t)0x20
#define bit6 (uint8_t)0x40
#define bit7 (uint8_t)0x80

#define bit8 (uint16_t)0x0100
#define bit9 (uint16_t)0x0200
#define bit10 (uint16_t)0x0400
#define bit11 (uint16_t)0x0800
#define bit12 (uint16_t)0x1000
#define bit13 (uint16_t)0x2000
#define bit14 (uint16_t)0x4000
#define bit15 (uint16_t)0x8000

#ifdef uP_32bit
#define bit16 (uint32_t)0x00010000
#define bit17 (uint32_t)0x00020000
#define bit18 (uint32_t)0x00040000
#define bit19 (uint32_t)0x00080000
#define bit20 (uint32_t)0x00100000
#define bit21 (uint32_t)0x00200000
#define bit22 (uint32_t)0x00400000
#define bit23 (uint32_t)0x00800000

#define bit24 (uint32_t)0x01000000
#define bit25 (uint32_t)0x02000000
#define bit26 (uint32_t)0x04000000
#define bit27 (uint32_t)0x08000000
#define bit28 (uint32_t)0x10000000
#define bit29 (uint32_t)0x20000000
#define bit30 (uint32_t)0x40000000
#define bit31 (uint32_t)0x80000000
#endif

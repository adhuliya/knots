/*	CoRTOSint.c - Interrupt & timer for the Super Blinky et. al. demonstration

	2018.12.12 12:00	Release 1.10

	(c) 2017, 2018 Nicholas O. Lindan,
	Released under GPL V3 https://www.gnu.org/licenses/gpl.html

	Contains the timer interrupt code.

	This file is ungainly as it contains code for all the supported
	processors - feel free to delete the sections for uPs that aren't
	needed. */

#include "CoRTOSuP.h"

#ifdef uP_Cortex_M0
/* Needs to go before CoRTOScomdefs.h to resolve typedef collisions. */
#include "sam.h"
#endif

#include "CORTOScomdefs.h"
#include "CoRTOSint.h"
#include "CoRTOStimer.h"

/*	Interrupt enable/disable nesting for the timer interrupt. */
static uint8_t intdis_nest_timer;
static boolean high_speed;

/*	Run software with a 1mSec tick, speeds up some tests. */
void set_high_speed (boolean x) {
	if (x == true)
		high_speed = true;
	else
		high_speed = false;
}

/*****************************************************************
******************************************************************
**
**		AVR
**
******************************************************************
*****************************************************************/
#ifdef uP_AVR
#include <avr/io.h>
#include <avr/interrupt.h>

/************************************************************************
*
*	Timer compare interrupt
*
************************************************************************/

ISR (TIMER1_COMPA_vect) {
	sei ();
	service_timers ();

	/*	Reset the hardware for the next timer compare interrupt.
		The manual says the hardware does this on executing the
		vector, but this doesn't always seem to be the case. */
	TIFR1 = 0b00000010;
	TIMSK1 = 0b00000010;
}

/************************************************************************
*
*	interrupt disable/enable routines
*
************************************************************************/

/*	Not used in CoRTOS, but timer needs to be enabled via main()
	when CoRTOS is started.

	The AVR can't do atomic bit set/resets so interrupts have to be
	disabled while the timer interrupt control is changed.  Note the
	interrupt routines above also manipulate the TIMSK1 register so
	there would otherwise be the possibility of the main line code
	and the timer interrupt trying to access the register at the same
	time.

	sreg_save is used to restore the state of the global interrupt
	enable.  If these functions are called with interrupts disabled
	the the interrupts will stay disabled, ditto for interrupts
	enabled. */

void timer_int_disable (void)
{
	uint8_t sreg_save = SREG;
	intdis_nest_timer++;
	cli ();
	TIMSK1 &= ~bit1;
	SREG = sreg_save;
}

void timer_int_enable (boolean force)
{
	uint8_t sreg_save = SREG;
	if (force == true)
		intdis_nest_timer = 0;
	if (intdis_nest_timer != 0)
	{
		intdis_nest_timer--;
	}
	else
	{
		cli ();
		TIMSK1 |= bit1;
		SREG = sreg_save;
	}
}

/************************************************************************
*
*	Initialization
*
************************************************************************/

void initialize_interrupts (void)
{

	/*	Timer & interrupt */
			  /* 76543210 */
	TCCR1A = 0b00000000;

/*	TC1 Control Register B

	Timer is clocked at 1MHz, 1x system clock
	Reloaded from OCR1A

	7	0	ICNC1		1 - Cancel noise on ICP1 pin
	6	0	ICES1		1 - Rising edge on ICP1 pin
	5	0
	4	0	WGM13		01 - OCR1A is top value
	3	1	WGM12		11 - ICR1A is top value
	2	0	CS12		000->101 0, 1, 8, 64, 256, 1024 sys clock
	1	0	CS11		110 T0 pin falling
	0	1	CS10  	111 T0 pin rising

	Divide by 64 - @8MHz gives 8 uSec.

				  76543210 */
	TCCR1B = 0b00001011;

	TCCR1C = 0b00000000;

/*	Set up timer 1 for 10 mSec. overflow & interrupt

	8MHz internal clock	=>      0.125 uS
	prescale / 64 			=>      8.0   uS */
	if (high_speed == false) {
		/*	divide by 1,250 (0x04e2) in OCRA=> 10,000.0 uS */
		OCR1AH = 0x04;
		OCR1AL = 0xe2;
	} else {
		/*	divide by 125 (0x007d) in OCRA=> 1,000.0 uS */
		OCR1AH = 0x00;
		OCR1AL = 0x7d;
	}

	TIMSK1 = 0b00000000;

	TIFR1 = 0b00000000;
}

/*****************************************************************
******************************************************************
**
**		MSP430
**
******************************************************************
*****************************************************************/
#elif uP_MSP430

#ifdef variant_MSP430FR5994
#include "msp430FR5994.h"
#elif variant_MSP430FR5969
#include "msp430FR5969.h"
#elif variant_MSP430FR6989
#include "msp430FR6989.h"
#else
#include <msp430.h>
#endif

#define development_WDT 0x5A80

/************************************************************************
*
*	Timer compare interrupt
*
************************************************************************/

/*	The interrupt is triggered 10mSec period on output
	compare A using timer 1.  Its function is to decrement
	the timers of any delayed tasks via a call to service_timers(). */

#pragma vector=TIMER1_A0_VECTOR
__interrupt void timerA1_CC0 (void) {
	/*	This vector is shared with other timer interrupt sources.  At
		present there is only the one source triggered on overflow compare. */
	service_timers ();
	__enable_interrupt ();
}

/************************************************************************
*
*	interrupt disable/enable routines
*
************************************************************************/

void timer_int_disable (void)
{
	intdis_nest_timer++;
	TA1CCTL0 &= ~CCIE;
}

void timer_int_enable (boolean force)
{
	if (force == true)
		intdis_nest_timer = 0;
	if (intdis_nest_timer != 0)
		intdis_nest_timer--;
	else
		TA1CCTL0 |= CCIE;
}

/************************************************************************
*
*	Initialization
*
************************************************************************/

void initialize_interrupts (void)
{
	/*	Stop the watchdog timer. */
	WDTCTL = development_WDT;

	/*	Set one wait state for FRAM access, the a5 is the unlock code,
		10 is the number of wait states - in the high nibble.  This
		is needed as the FRAM can only run at 8MHz and so needs the
		wait state when the CPU runs at 16MHz. */
	FRCTL0 = 0xa510; FRCTL0 = 0xa510;

	/*	Setup XT1 */
	PJSEL0 |= BIT4 | BIT5;

	/*	Unlock CS registers */
	CSCTL0 = 0xa500;

	/*	Set DCO to 16MHz */
	CSCTL1 = DCOFSEL_4|DCORSEL;

	/*	set ACLK = XT1; SMCLK= MCLK = DCO = 16MHz */
	CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;

	/*	Set all dividers */
	CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;
	CSCTL4 &= ~LFXTOFF;

	/*	Timer A1: SMCLK/8, MC_1 upmode, TASSEL_2 : 2 MHz clock source */
	TA1CTL = TASSEL_2 + MC_1 + ID_3;

	if (high_speed == false)
		/*	10mSec period */
		TA1CCR0 =  20000;
	else
		/*	1mSec period */
		TA1CCR0 =  2000;

	__enable_interrupt ();
}

/*****************************************************************
******************************************************************
**
**		PIC24
**
******************************************************************
*****************************************************************/
#elif uP_PIC24
#include "p24FJ128GA204.h"

/************************************************************************
*
*	Timer compare interrupt
*
************************************************************************/

/*	The interrupt is triggered 10mSec period on output
	compare using timer 1.  Its function is to decrement
	the timers of any delayed tasks via a call to service_timers(). */

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt (void) {
	IFS0bits.T1IF = 0;
	service_timers ();
}

/************************************************************************
*
*	interrupt disable/enable routines
*
************************************************************************/

/*	Not used in CoRTOS, but timer needs to be enabled via main()
	when CoRTOS is started. */

void timer_int_disable (void)
{
	intdis_nest_timer++;
	IEC0bits.T1IE = 0;
}

void timer_int_enable (boolean force)
{
	if (force == true)
		intdis_nest_timer = 0;
	if (intdis_nest_timer != 0)
		intdis_nest_timer--;
	else
		IEC0bits.T1IE = 1;
}

/************************************************************************
*
*	Initialization
*
************************************************************************/

void initialize_interrupts (void)
{
    /*  8MHz processor, 4 cycles/Hz => 2MHz / 8 = 250kHz */
 	T1CON = 0x0010;
	TMR1 = 0x0000;
	if (high_speed == false)
		/*  250kHz / 2,500 = 100Hz*/
		PR1 = 2500;
	else
		/* = 1kHz */
		PR1 = 250;

	IPC0bits.T1IP = 0x01;
	IFS0bits.T1IF = 0;
   IEC0bits.T1IE = 1;
	T1CONbits.TON = 1;
}

/*****************************************************************
******************************************************************
**
**		SAMD10
**
******************************************************************
*****************************************************************/
#elif uP_Cortex_M0
#define PORTA PORT->Group[0]

static boolean M0_timer_soft_enable;

static volatile int x;

/* Trap "lost in the weeds" interrupts, add/delete as needed for
	different processors. */
void PM_Handler (void) {while (1);}
void SYSCTRL_Handler (void) {while (1);}
void WDT_Handler (void) {while (1);}
void RTC_Handler (void) {while (1);}
void EIC_Handler (void) {while (1);}
void NVMCTRL_Handler (void) {while (1);}
void DMAC_Handler (void) {while (1);}
void USB_Handler (void) {while (1);}
void EVSYS_Handler (void) {while (1);}
void SERCOM0_Handler (void) {while (1);}
void SERCOM1_Handler (void) {while (1);}
void SERCOM2_Handler (void) {while (1);}
void TCC0_Handler (void) {while (1);}
void TC1_Handler (void) {while (1);}
//void TC2_Handler (void) {while (1);}
//void ADC_Handler (void) {while (1);}
void AC_Handler (void) {while (1);}
void DAC_Handler (void) {while (1);}
void PTC_Handler (void) {while (1);}
void NMI_Handler (void) {while (1);}
void HardFault_Handler (void) {while (1);}
void SVC_Handler (void) {while (1);}
void PendSV_Handler (void) {while (1);}
//void SysTick_Handler (void) {while (1);}

void SysTick_Handler (void) {
	if (M0_timer_soft_enable == true)
		service_timers ();
}

void timer_int_disable (void) {
	intdis_nest_timer++;
	/* Rather than fiddle with the ARM interrupt system we
		just tell the timer ISR to do nothing. */
	M0_timer_soft_enable = false;
}

void timer_int_enable (boolean force) {
	if (force == true)
		intdis_nest_timer = 0;
	if (intdis_nest_timer != 0)
		intdis_nest_timer--;
	else
		M0_timer_soft_enable = true;
}

void initialize_interrupts (void) {
	/* Configure SysTick to generate an interrupt every 10mS.
		AMAZING - something that is actually simple to do on
		the M0/SAMD10 */
	if (high_speed == false)
		SysTick_Config (SystemCoreClock / 100);
	else
		SysTick_Config (SystemCoreClock / 1000);
}

#endif

/*
 * timers.c
 *
 * Created: 9/24/2017 1:27:37 AM
 *  Author: Kurt
 */ 

 #include <asf.h>
 #include <stdbool.h>
 #include "timers.h"

 void timers_init(void) {

	// T0 is used for stepping
	// Enable interrupts on timer 0

	NVIC_EnableIRQ(TC0_IRQn);

	// Enable peripheral clock for TC0
	// Peripheral ID (PID) for TC0 is 23
	REG_PMC_PCER0 |= PMC_PCER0_PID23;

	// Links timer clock to Master clock / 32 = 3.125 MHz
	// 3.125 MHz = 62500 ticks @ 50 BPM (without handling overflows)
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK4;

	// Sets the counter overflow interrupt
	REG_TC0_IER0 |= TC_IER_COVFS;

	// For the interrupt
	REG_PIOA_PER |= PIO_PER_P11; //enable PIO controller on PA11
	REG_PIOA_OER |= PIO_PER_P11; //enable output on pin PA11
	REG_PMC_PCER0 |= PMC_PCER0_PID11; //Enable PMC control for PA11

	// TC0 control register enables timer and triggers it to start
	REG_TC0_CCR0 |= TC_CCR_CLKEN | TC_CCR_SWTRG;
 }

 void TC0_Handler() {
	 // Handling overflow
	 if((REG_TC0_SR0 & TC_SR_COVFS) != 0) {
		 if((REG_PIOA_PDSR & PIO_ODSR_P11) >= 1) {
			 REG_PIOA_CODR |= PIO_CODR_P11;
		 }
		 else {
			 REG_PIOA_SODR |= PIO_SODR_P11;
		 }
	 }
 }
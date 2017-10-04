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

	overflow_count = 0;

	// T0 is used for stepping
	// Enable interrupts on timer 0

	NVIC_EnableIRQ(TC0_IRQn);

	// Enable peripheral clock for TC0
	// Peripheral ID (PID) for TC0 is 23
	REG_PMC_PCER0 |= PMC_PCER0_PID23;

	// Links timer clock to Master clock / 32 = 3.125 MHz
	// 3.125 MHz = 62500 ticks @ 50 BPM (without handling overflows)

	// Sets the timer to overflow when it matches RC value, and sets speed of clock
	// TIMER_CLOCK1 = MCK/2
	// TIMER_CLOCK2 = MCK/8
	// TIMER_CLOCK3 = MCK/32
	// TIMER_CLOCK4 = MCK/128
	// TIMER_CLOCK5 = SCLK
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK2 | TC_CMR_CPCTRG;
	// Set interrupt on compare to RC value
	REG_TC0_IER0 |= TC_IER_CPCS;

// 	// 60 BPM = 1 Hz. SCK = 32 KHz. 16,000 counts per half second, 2 interrupts per cycle
// 	REG_TC0_RC0 = 16000;

	// 60 BPM = 1 Hz. MCK/8 = 12.5 MHz. 6.25 mil counts per half second, 2 interrupts per cycle
	// Anticipating 5000 overflows (5000*1250 is 6.25 mil)
	REG_TC0_RC0 = 1250;

	// For the interrupt
	REG_PIOA_PER |= PIO_PER_P20; //enable PIO controller on PA11
	REG_PIOA_OER |= PIO_PER_P20; //enable output on pin PA11
	REG_PMC_PCER0 |= PMC_PCER0_PID11; //Enable PMC control for PA11

	// TC0 control register enables timer and triggers it to start
	REG_TC0_CCR0 |= TC_CCR_CLKEN | TC_CCR_SWTRG;
 }

 void update_timers(int bpm) {
// 	// (SCK/2) / (bpm/60); SCK*60/2 = 960000
// 	// Offset is needed, possible not with the crystals working
// 	REG_TC0_RC0 = (uint16_t)(960000/bpm - 420);
	if(bpm > 1) {
		REG_TC0_RC0 = (uint16_t)(75000/bpm);
	}
 }

 void TC0_Handler() {
	 // Handling timer = RC

	 // Test code, normally trigger next step, output clock
	 if((REG_TC0_SR0 & TC_SR_CPCS) >= 0) {
		overflow_count += 1;
	 }

	 if(overflow_count >= 5000) {
		if((REG_PIOA_PDSR & PIO_ODSR_P20) >= 1) {
			REG_PIOA_CODR |= PIO_CODR_P20;
		}
		else {
			REG_PIOA_SODR |= PIO_SODR_P20;
		}
		overflow_count = 0;
	 }

 }
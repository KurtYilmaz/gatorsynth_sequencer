/*
 * sequencer.c
 *
 * Created: 9/22/2017 12:15:25 AM
 *  Author: Kurt
 */ 

 #include <asf.h>
 #include <board.h>
 #include <conf_board.h>
 #include <stdbool.h>

 #include "timers.h"
 #include "sequencer.h"

 uint8_t A_seq;
 uint8_t B_seq;


 void bpm_direction(uint32_t A, uint32_t B){

	//read Encoder input A
	bool A_in = REG_PIOA_PDSR & A;
	//read Encoder input B
	bool B_in = REG_PIOA_PDSR & B;
	
	A_seq = A_seq << 1;
	A_seq |= A_in;
	
	B_seq = B_seq << 1;
	B_seq |= B_in;
	
	A_seq &= 0b00001111;
	B_seq &= 0b00001111;


	//return true if turned right
	if ((A_seq == 0b00001001) && (B_seq == 0b00000011)){
		REG_PIOB_SODR |= PIO_PER_P3; //set output high on PB3
		bpm_inc();

	}

	else if ((A_seq == 0b00000011) && (B_seq == 0b00001001)){
		REG_PIOB_CODR |= PIO_PER_P3; //set output low on PB3
		bpm_dec();
	}


}

 void bpm_inc(){
	bpm++;
 }

 void bpm_dec(){
	 bpm--;
 }


 void init_sequencer_controls(){

	bpm = 120;

	//enable clock for PIOA
	REG_PMC_PCER0 |= PMC_PCER0_PID11;

	/**************			CONFIGURE CONTROL ENCODERS			**************/

	//Set up PA0 as BPM INPUT A
	REG_PIOA_PER |= PIO_PER_P0; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P0; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P0; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P0;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P0; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P0;	//start debounce filter

	//Set up PA1 as BPM INPUT B
	REG_PIOA_PER |= PIO_PER_P1; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P1; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P1; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P1;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P1; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P1;	//start debounce filter



	/**************			CONFIGURE ENCODER INTERRUPTS			**************/

	uint32_t flag_clear = REG_PIOA_ISR;	//clear left over interrupt flags

	//Enable interrupts for Encoder 1
	REG_PIOA_IER |= PIO_IER_P0;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P0;
	REG_PIOA_IER |= PIO_IER_P1;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P1;

	NVIC_EnableIRQ(PIOA_IRQn);			//enable PORT A interrupts


 }

 void PIOA_Handler(){

	uint32_t status = REG_PIOA_ISR;	//read PIOC interrupt status & clear interrupt flags

	//check if Encoder 1 was rotated
	if ( (status & PIO_ISR_P0) || (status & PIO_ISR_P1) ){
		bpm_direction(PIO_ODSR_P0, PIO_ODSR_P1);
		update_timers(bpm);
	}

 }
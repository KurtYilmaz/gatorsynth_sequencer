/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>
#include <stdbool.h>
#include "notes.h"
#include "timers.h"

uint8_t A_seq;
uint8_t B_seq;

 void encoder_direction(uint32_t A, uint32_t B, uint8_t step){

	//read Encoder input A
	bool A_in = REG_PIOC_PDSR & A;
	//read Encoder input B
	bool B_in = REG_PIOC_PDSR & B;
	
	A_seq = A_seq << 1;
	A_seq |= A_in;
	
	B_seq = B_seq << 1;
	B_seq |= B_in;
	
	A_seq &= 0b00001111;
	B_seq &= 0b00001111;


	//return true if turned right
	if ((A_seq == 0b00001001) && (B_seq == 0b00000011)){
		REG_PIOB_SODR |= PIO_PER_P3; //set output high on PB3
		notes_inc(step);
	}

	else if ((A_seq == 0b00000011) && (B_seq == 0b00001001)){
		REG_PIOB_CODR |= PIO_PER_P3; //set output low on PB3
		notes_dec(step);
	}
}


void Encoder_init(){
	A_seq = 0;
	B_seq = 0;

	//enable clock for PIOC
	REG_PMC_PCER0 |= PMC_PCER0_PID13;


	/**************			CONFIGURE 16 STEP ENCODERS			**************/

	//Set up PC0 as ENCODER 1 INPUT A
	REG_PIOC_PER |= PIO_PER_P0; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P0; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P0; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P0;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P0; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P0;	//start debounce filter

	//Set up PC1 as ENCODER 1 INPUT B
	REG_PIOC_PER |= PIO_PER_P1; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P1; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P1; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P1;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P1; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P1;	//start debounce filter


	
	//Set up PC2 as ENCODER 2 INPUT A
	REG_PIOC_PER |= PIO_PER_P2; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P2; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P2; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P2;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P2; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P2;	//start debounce filter

	//Set up PC3 as ENCODER 2 INPUT B
	REG_PIOC_PER |= PIO_PER_P3; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P3; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P3; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P3;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P3; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P3;	//start debounce filter



	//Set up PC4 as ENCODER 3 INPUT A
	REG_PIOC_PER |= PIO_PER_P4; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P4; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P4; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P4;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P4; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P4;	//start debounce filter

	//Set up PC5 as ENCODER 3 INPUT B
	REG_PIOC_PER |= PIO_PER_P5; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P5; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P5; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P5;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P5; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P5;	//start debounce filter



	//Set up PC6 as ENCODER 4 INPUT A
	REG_PIOC_PER |= PIO_PER_P6; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P6; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P6; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P6;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P6; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P6;	//start debounce filter

	//Set up PC7 as ENCODER 4 INPUT B
	REG_PIOC_PER |= PIO_PER_P7; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P7; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P7; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P7;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P7; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P7;	//start debounce filter



	//Set up PC8 as ENCODER 5 INPUT A
	REG_PIOC_PER |= PIO_PER_P8; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P8; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P8; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P8;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P8; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P8;	//start debounce filter

	//Set up PC9 as ENCODER 5 INPUT B
	REG_PIOC_PER |= PIO_PER_P9; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P9; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P9; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P9;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P9; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P9;	//start debounce filter



	//Set up PC10 as ENCODER 6 INPUT A
	REG_PIOC_PER |= PIO_PER_P10; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P10; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P10; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P10;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P10; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P10;	//start debounce filter

	//Set up PC11 as ENCODER 6 INPUT B
	REG_PIOC_PER |= PIO_PER_P11; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P11; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P11; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P11;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P11; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P11;	//start debounce filter



	//Set up PC12 as ENCODER 7 INPUT A
	REG_PIOC_PER |= PIO_PER_P3; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P3; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P3; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P3;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P3; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P3;	//start debounce filter

	//Set up PC13 as ENCODER 7 INPUT B
	REG_PIOC_PER |= PIO_PER_P13; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P13; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P13; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P13;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P13; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P13;	//start debounce filter



	//Set up PC14 as ENCODER 8 INPUT A
	REG_PIOC_PER |= PIO_PER_P14; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P14; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P14; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P14;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P14; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P14;	//start debounce filter

	//Set up PC15 as ENCODER 8 INPUT B
	REG_PIOC_PER |= PIO_PER_P15; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P15; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P15; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P15;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P15; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P15;	//start debounce filter



	//Set up PC16 as ENCODER 9 INPUT A
	REG_PIOC_PER |= PIO_PER_P16; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P16; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P16; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P16;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P16; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P16;	//start debounce filter

	//Set up PC17 as ENCODER 9 INPUT B
	REG_PIOC_PER |= PIO_PER_P17; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P17; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P17; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P17;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P17; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P17;	//start debounce filter



	
	//Set up PC18 as ENCODER 10 INPUT A
	REG_PIOC_PER |= PIO_PER_P18; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P18; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P18; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P18;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P18; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P18;	//start debounce filter

	//Set up PC19 as ENCODER 10 INPUT B
	REG_PIOC_PER |= PIO_PER_P19; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P19; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P19; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P19;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P19; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P19;	//start debounce filter



	//Set up PC20 as ENCODER 11 INPUT A
	REG_PIOC_PER |= PIO_PER_P20; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P20; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P20; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P20;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P20; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P20;	//start debounce filter

	//Set up PC21 as ENCODER 11 INPUT B
	REG_PIOC_PER |= PIO_PER_P21; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P21; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P21; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P21;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P21; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P21;	//start debounce filter



	//Set up PC22 as ENCODER 12 INPUT A
	REG_PIOC_PER |= PIO_PER_P22; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P22; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P22; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P22;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P22; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P22;	//start debounce filter

	//Set up PC23 as ENCODER 12 INPUT B
	REG_PIOC_PER |= PIO_PER_P23; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P23; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P23; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P23;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P23; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P23;	//start debounce filter



	//Set up PC24 as ENCODER 13 INPUT A
	REG_PIOC_PER |= PIO_PER_P24; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P24; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P24; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P24;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P24; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P24;	//start debounce filter

	//Set up PC25 as ENCODER 13 INPUT B
	REG_PIOC_PER |= PIO_PER_P25; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P25; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P25; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P25;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P25; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P25;	//start debounce filter



	//Set up PC26 as ENCODER 14 INPUT A
	REG_PIOC_PER |= PIO_PER_P26; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P26; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P26; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P26;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P26; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P26;	//start debounce filter

	//Set up PC27 as ENCODER 14 INPUT B
	REG_PIOC_PER |= PIO_PER_P27; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P27; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P27; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P27;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P27; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P27;	//start debounce filter



	//Set up PC28 as ENCODER 15 INPUT A
	REG_PIOC_PER |= PIO_PER_P28; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P28; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P28; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P28;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P28; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P28;	//start debounce filter

	//Set up PC29 as ENCODER 15 INPUT B
	REG_PIOC_PER |= PIO_PER_P29; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P29; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P29; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P29;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P29; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P29;	//start debounce filter



	//Set up PC30 as ENCODER 16 INPUT A
	REG_PIOC_PER |= PIO_PER_P30; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P30; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P30; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P30;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P30; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P30;	//start debounce filter

	//Set up PC31 as ENCODER 16 INPUT B
	REG_PIOC_PER |= PIO_PER_P31; //enable PIO controller
	REG_PIOC_ODR |= PIO_ODR_P31; //disable output
	REG_PIOC_PPDDR |= PIO_PPDDR_P31; //disable pull-down resistor
	REG_PIOC_PUER |= PIO_PUER_P31;	//enable pull-up resistor
	REG_PIOC_IFSCER |= PIO_IFSCER_P31; //turn on slow clock debounce
	REG_PIOC_IFER |= PIO_IFER_P31;	//start debounce filter
	


	/**************			CONFIGURE ENCODER INTERRUPTS			**************/

	uint32_t flag_clear = REG_PIOC_ISR;	//clear left over interrupt flags

	//Enable interrupts for Encoder 1
	REG_PIOC_IER |= PIO_IER_P0;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P0;
	REG_PIOC_IER |= PIO_IER_P1;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P1;

	//Enable interrupts for Encoder 2
	REG_PIOC_IER |= PIO_IER_P2;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P2;
	REG_PIOC_IER |= PIO_IER_P3;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P3;

	//Enable interrupts for Encoder 3
	REG_PIOC_IER |= PIO_IER_P4;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P4;
	REG_PIOC_IER |= PIO_IER_P5;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P5;

	//Enable interrupts for Encoder 4
	REG_PIOC_IER |= PIO_IER_P6;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P6;
	REG_PIOC_IER |= PIO_IER_P7;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P7;

	//Enable interrupts for Encoder 5
	REG_PIOC_IER |= PIO_IER_P8;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P8;
	REG_PIOC_IER |= PIO_IER_P9;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P9;

	//Enable interrupts for Encoder 6
	REG_PIOC_IER |= PIO_IER_P10;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P10;
	REG_PIOC_IER |= PIO_IER_P11;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P11;

	//Enable interrupts for Encoder 7
	REG_PIOC_IER |= PIO_IER_P3;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P3;
	REG_PIOC_IER |= PIO_IER_P13;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P13;

	//Enable interrupts for Encoder 8
	REG_PIOC_IER |= PIO_IER_P14;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P14;
	REG_PIOC_IER |= PIO_IER_P15;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P15;

	//Enable interrupts for Encoder 9
	REG_PIOC_IER |= PIO_IER_P16;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P16;
	REG_PIOC_IER |= PIO_IER_P17;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P17;

	//Enable interrupts for Encoder 10
	REG_PIOC_IER |= PIO_IER_P18;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P18;
	REG_PIOC_IER |= PIO_IER_P19;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P19;

	//Enable interrupts for Encoder 11
	REG_PIOC_IER |= PIO_IER_P20;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P20;
	REG_PIOC_IER |= PIO_IER_P21;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P21;

	//Enable interrupts for Encoder 12
	REG_PIOC_IER |= PIO_IER_P22;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P22;
	REG_PIOC_IER |= PIO_IER_P23;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P23;

	//Enable interrupts for Encoder 13
	REG_PIOC_IER |= PIO_IER_P24;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P24;
	REG_PIOC_IER |= PIO_IER_P25;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P25;

	//Enable interrupts for Encoder 14
	REG_PIOC_IER |= PIO_IER_P26;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P26;
	REG_PIOC_IER |= PIO_IER_P27;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P27;

	//Enable interrupts for Encoder 15
	REG_PIOC_IER |= PIO_IER_P28;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P28;
	REG_PIOC_IER |= PIO_IER_P29;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P29;

	//Enable interrupts for Encoder 16
	REG_PIOC_IER |= PIO_IER_P30;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P30;
	REG_PIOC_IER |= PIO_IER_P31;			//enable input rising edge interrupt
	REG_PIOC_REHLSR |= PIO_REHLSR_P31;

	NVIC_EnableIRQ(PIOC_IRQn);			//enable PORT C interrupts


}



void PIOC_Handler(){

	uint32_t status = REG_PIOC_ISR;	//read PIOC interrupt status & clear interrupt flags

	//check if Encoder 1 was rotated
	if ( (status & PIO_ISR_P0) || (status & PIO_ISR_P1) ){	
		encoder_direction(PIO_ODSR_P0, PIO_ODSR_P1, 0);
	}

	//check if Encoder 2 was rotated
	else if ( (status & PIO_ISR_P2) || (status & PIO_ISR_P3) ){
		encoder_direction(PIO_ODSR_P2, PIO_ODSR_P3, 1);
	}

	//check if Encoder 3 was rotated
	else if ( (status & PIO_ISR_P4) || (status & PIO_ISR_P5) ){
		encoder_direction(PIO_ODSR_P4, PIO_ODSR_P5, 2);
	}

	//check if Encoder 4 was rotated
	else if ( (status & PIO_ISR_P6) || (status & PIO_ISR_P7) ){
		encoder_direction(PIO_ODSR_P6, PIO_ODSR_P7, 3);
	}

	//check if Encoder 5 was rotated
	else if ( (status & PIO_ISR_P8) || (status & PIO_ISR_P9) ){
		encoder_direction(PIO_ODSR_P8, PIO_ODSR_P9, 4);
	}

	//check if Encoder 6 was rotated
	else if ( (status & PIO_ISR_P10) || (status & PIO_ISR_P11) ){
		encoder_direction(PIO_ODSR_P10, PIO_ODSR_P11, 5);
	}

	//check if Encoder 7 was rotated
	else if ( (status & PIO_ISR_P12) || (status & PIO_ISR_P13) ){
		encoder_direction(PIO_ODSR_P12, PIO_ODSR_P13, 6);
	}

	//check if Encoder 8 was rotated
	else if ( (status & PIO_ISR_P14) || (status & PIO_ISR_P15) ){
		encoder_direction(PIO_ODSR_P14, PIO_ODSR_P15, 7);
	}

	//check if Encoder 9 was rotated
	else if ( (status & PIO_ISR_P16) || (status & PIO_ISR_P17) ){
		encoder_direction(PIO_ODSR_P16, PIO_ODSR_P17, 8);
	}

	//check if Encoder 10 was rotated
	else if ( (status & PIO_ISR_P18) || (status & PIO_ISR_P19) ){
		encoder_direction(PIO_ODSR_P18, PIO_ODSR_P19, 9);
	}

	//check if Encoder 11 was rotated
	else if ( (status & PIO_ISR_P20) || (status & PIO_ISR_P21) ){
		encoder_direction(PIO_ODSR_P20, PIO_ODSR_P21, 10);
	}

	//check if Encoder 12 was rotated
	else if ( (status & PIO_ISR_P22) || (status & PIO_ISR_P23) ){
		encoder_direction(PIO_ODSR_P22, PIO_ODSR_P23, 11);
	}

	//check if Encoder 13 was rotated
	else if ( (status & PIO_ISR_P24) || (status & PIO_ISR_P25) ){
		encoder_direction(PIO_ODSR_P24, PIO_ODSR_P25, 12);
	}
	
	//check if Encoder 14 was rotated
	else if ( (status & PIO_ISR_P26) || (status & PIO_ISR_P27) ){
		encoder_direction(PIO_ODSR_P26, PIO_ODSR_P27, 13);
	}

	//check if Encoder 15 was rotated
	else if ( (status & PIO_ISR_P28) || (status & PIO_ISR_P29) ){
		encoder_direction(PIO_ODSR_P28, PIO_ODSR_P29, 14);
	}

	//check if Encoder 16 was rotated
	else if ( (status & PIO_ISR_P30) || (status & PIO_ISR_P31) ){
		encoder_direction(PIO_ODSR_P30, PIO_ODSR_P31, 15);
	}
}

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

void LED_init(){
	 //enable clock for PIOA
	 REG_PMC_PCER0 |= PMC_PCER0_PID11;

	 //Set up PA11 as Center LED OUTPUT
	 REG_PIOA_PER |= PIO_PER_P17; //enable PIO controller on PA17
	 REG_PIOA_OER |= PIO_PER_P17; //enable output on pin PA17
	 REG_PIOA_CODR |= PIO_PER_P17; //set output low on PA17 as default

	  //Set up PA15 as Left LED OUTPUT
	  REG_PIOA_PER |= PIO_PER_P15; //enable PIO controller on PA15
	  REG_PIOA_OER |= PIO_PER_P15; //enable output on pin PA15
	  REG_PIOA_CODR |= PIO_PER_P15; //set output low on PA15 as default

	  //Set up PA16 as Right LED OUTPUT
	  REG_PIOA_PER |= PIO_PER_P16; //enable PIO controller on PA16
	  REG_PIOA_OER |= PIO_PER_P16; //enable output on pin PA16
	  REG_PIOA_CODR |= PIO_PER_P16; //set output low on PA16 as default
}

void Encoder_init(){
	 //Set up PA12 as BUTTON INPUT
	 REG_PIOA_PER |= PIO_PER_P12; //enable PIO controller on PA12
	 REG_PIOA_ODR |= PIO_ODR_P12; //disable output on pin PA12
	 REG_PIOA_PPDDR |= PIO_PPDDR_P12; //disable pull-down resistor on PA12
	 REG_PIOA_PUER |= PIO_PUER_P12;	//enable pull-up resistor on PA12
	 REG_PIOA_IFSCER |= PIO_IFSCER_P12; //turn on slow clock debounce
	 REG_PIOA_IFER |= PIO_IFER_P12;	//start debounce filter

	 //Set up PA13 as ENCODER INPUT A
	 REG_PIOA_PER |= PIO_PER_P5; //enable PIO controller on PA13
	 REG_PIOA_ODR |= PIO_ODR_P5; //disable output on pin PA13
	 REG_PIOA_PPDDR |= PIO_PPDDR_P5; //disable pull-down resistor on PA13
	 REG_PIOA_PUER |= PIO_PUER_P5;	//enable pull-up resistor on PA13
	 REG_PIOA_IFSCER |= PIO_IFSCER_P5; //turn on slow clock debounce
	 REG_PIOA_IFER |= PIO_IFER_P5;	//start debounce filter

	 //Set up PA12 as ENCODER INPUT B
	 REG_PIOA_PER |= PIO_PER_P6; //enable PIO controller on PA14
	 REG_PIOA_ODR |= PIO_ODR_P6; //disable output on pin PA14
	 REG_PIOA_PPDDR |= PIO_PPDDR_P6; //disable pull-down resistor on PA14
	 REG_PIOA_PUER |= PIO_PUER_P6;	//enable pull-up resistor on PA14
	 REG_PIOA_IFSCER |= PIO_IFSCER_P6; //turn on slow clock debounce
	 REG_PIOA_IFER |= PIO_IFER_P6;	//start debounce filter
	 

	 uint32_t flag_clear = REG_PIOA_ISR;	//clear left over interrupt flags
	 REG_PIOA_IER |= PIO_IER_P12;			//enable input level change interrupt on P12
	 REG_PIOA_IER |= PIO_IER_P5;			//enable input rising edge interrupt on P5
	 REG_PIOA_REHLSR |= PIO_REHLSR_P5;
	 REG_PIOA_IER |= PIO_IER_P6;			//enable input rising edge interrupt on P6
	 REG_PIOA_REHLSR |= PIO_REHLSR_P6;
	 NVIC_EnableIRQ(PIOA_IRQn);				//enable PORT A interrupts
}

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	 LED_init();
	 Encoder_init();


}

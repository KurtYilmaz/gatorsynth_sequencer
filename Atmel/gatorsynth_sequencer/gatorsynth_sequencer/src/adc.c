/*
 * adc.c
 *
 * Created: 10/24/2017 7:02:11 PM
 *  Author: Kyle
 */ 

 #include <asf.h>
 #include <stdbool.h>
 #include <stdlib.h>

 #include "timers.h"

 //define register to read CH2 conversion from
#define REG_ADC_CDR2     (*(__I  uint32_t*)0x40038058U) /**< \brief (ADC) Channel Data Register */ 

 void ADC_init(){

	note_length = 5000;

	//enable peripheral clock for ADC
	REG_PMC_PCER0 |= PMC_PCER0_PID29;

	//enable interrupts for ADC
	NVIC_EnableIRQ(ADC_IRQn);

	//enable Channel 2 of ADC (PORTA 19)
	REG_ADC_CHER |= ADC_CHER_CH2;

	//configure ADC clock to 5MHz
	REG_ADC_MR |= ADC_MR_PRESCAL(9);

	//enable interrupt for end of ADC conversion on CH2
	REG_ADC_IER |= ADC_IER_EOC2;

	//start initial conversion
	REG_ADC_CR |= ADC_CR_START;

 }

  void convert_NoteLength(uint32_t DAC_data){

	  //get note length as a proportion of the overflow count of the timer
	  float note_float = 10000*(((float)DAC_data)/1023);
	  note_length = (uint16_t) note_float;

	  //in case of over flow from offset
	  if (note_length > 9000){
		note_length = 9000;
	  }
	  else if (note_length < 1000){
		note_length = 1000;
	  }

  }

 void ADC_Handler(){

	//read the interrupt flag and clear it
	uint32_t status = REG_ADC_ISR;

	//store the data
	uint32_t data;

	//check for CH2 interrupt
	if ((status & ADC_IMR_EOC2) > 0){
		data = REG_ADC_CDR2;	//read ADC data off CH2
	}

	convert_NoteLength(data);

	//start a new conversion
	//REG_ADC_CR |= ADC_CR_START;

 }

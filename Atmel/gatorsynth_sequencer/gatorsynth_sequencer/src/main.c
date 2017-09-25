#include <asf.h>
#include "timers.h"
#include <stdbool.h>


uint8_t A_seq = 0;
uint8_t B_seq = 0;

uint8_t position = 1;
uint8_t bpm = 120;

int main (void)
{
	sysclk_init();				//initialize system clock
	board_init();				//board init (currently empty)
	timers_init();				//initiate timer for Flashing LED on PA11
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer

	while (1)
	{

		if (position == 0){
			REG_PIOA_CODR |= PIO_PER_P15; //turn Left LED off
			REG_PIOA_SODR |= PIO_PER_P16; //turn Center LED on
			REG_PIOA_CODR |= PIO_PER_P17; //turn Right LED off
		}
		else if (position == 1){
			REG_PIOA_SODR |= PIO_PER_P15; //turn Left LED on
			REG_PIOA_CODR |= PIO_PER_P16; //turn Center LED off
			REG_PIOA_CODR |= PIO_PER_P17; //turn Right LED off
		}
		else if (position == 2){
			REG_PIOA_CODR |= PIO_PER_P15; //turn Left LED off
			REG_PIOA_CODR |= PIO_PER_P16; //turn Center LED off
			REG_PIOA_SODR |= PIO_PER_P17; //turn Right LED on
		}
	}
}

//turn LED ON/OFF when interrupt triggered on PA12
void PIOA_Handler(void){

	uint32_t status = REG_PIOA_ISR;	//read PIOA interrupt status & clear interrupt flags

	if ((status & PIO_ISR_P12)){	//check if Encoder Button was pressed

		position = 1;	//reset positon to center
	    bpm = 120;
	}

	else {	//  handle Encoder signal inputs

		//read Encoder input A
		bool A_in = REG_PIOA_PDSR & PIO_ODSR_P13;
		//read Encoder input B
		bool B_in = REG_PIOA_PDSR & PIO_ODSR_P14;

		A_seq = A_seq << 1;
		A_seq |= A_in;

		B_seq = B_seq << 1;
		B_seq |= B_in;

		A_seq &= 0b00001111;
		B_seq &= 0b00001111;

		if ((A_seq == 0b00001001) && (B_seq == 0b00000011)){

			if (position < 2)	//Check if not at Right-most LED
			position++;		//Move position right
			if(bpm < 999) {
				bpm+=1;
			}
		}
		else if ((A_seq == 0b00000011) && (B_seq == 0b00001001)){

			if (position > 0)	//Check if not at Left-most LED
			position--;		//Move position left
			if(bpm > 20) {
				bpm-=1;
			}
		}
	}

	update_timers(bpm);

}

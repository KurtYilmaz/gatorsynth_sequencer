#include <asf.h>
#include "timers.h"
#include <stdbool.h>


uint8_t A_seq = 0;
uint8_t B_seq = 0;
bool Right = false;
bool Left = false;

uint8_t count_left = 0;
uint8_t count_right = 0;

int main (void)
{
	 sysclk_init();				//initialize system clock
	 board_init();				//board init (currently empty)
	 timers_init();				//initiate timer for LED on PA11
	 WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer

	while (1)
	{
		//endless loop
		if ((Right == true) && (Left == true)){
			REG_PIOA_SODR |= PIO_PER_P15;	//turn Left LED ON
			REG_PIOA_SODR |= PIO_PER_P16;	//turn Right LED ON
		}
		if ((Right == false) && (Left == false)){
			REG_PIOA_CODR |= PIO_PER_P15;	//turn Left LED ON
			REG_PIOA_CODR |= PIO_PER_P16;	//turn Right LED ON
		}
		else if (Left == true){
			REG_PIOA_SODR |= PIO_PER_P15;	//turn Left LED ON
			REG_PIOA_CODR |= PIO_PER_P16;	//turn Right LED Off
		}
		else if (Right == true){
			REG_PIOA_CODR |= PIO_PER_P15;	//turn Left LED Off
			REG_PIOA_SODR |= PIO_PER_P16;	//turn Right LED ON
		}
	}
}

//turn LED ON/OFF when interrupt triggered on PA12
void PIOA_Handler(void){

	uint32_t status = REG_PIOA_ISR;	//read PIOA interrupt status & clear interrupt flags

	if ((status & PIO_ISR_P12)){	//check if Encoder Button was pressed
		//check if PA11 is HIGH or LOW
				if ( (REG_PIOA_PDSR & PIO_ODSR_P12) >= 1){	//if PA12 is HIGH
					Right = false;
					Left = false;
				}
				else{
					Right = true;
					Left = true;
				}
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
			Left = false;
			Right = true;
			count_right++;
		}

		else if ((A_seq == 0b00000011) && (B_seq == 0b00001001)){
			Left = true;
			Right = false;
			count_left++;
		}
// 
// 		if ((A_in == true) && (B_in == false)){
// 			Left = false;
// 			Right = true;
// 			count_right++;
// 		}
// 
// 		else if ((A_in == false) && (B_in == true)){
// 			Left = true;
// 			Right = false;
// 			count_left++;
// 		}

	}

}

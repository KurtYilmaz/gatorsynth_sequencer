#include <asf.h>
#include "timers.h"
#include "leds.h"
#include "spi.h"
#include <stdbool.h>
#include <stdlib.h>


uint8_t A_seq = 0;
uint8_t B_seq = 0;

uint16_t bpm = 60;
uint8_t brightness = 0x07;

int main (void)
{
	sysclk_init();				//initialize system clock
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer
	board_init();				//board init (currently empty)
	SPI_init();
	leds_update_display();
	timers_init();				//initiate timer for Flashing LED on PA20
	update_timers(bpm);

	while (1)
	{
		int x = 0;
	}
}

//turn LED ON/OFF when interrupt triggered on PA12
// void PIOA_Handler(void){
// 
// 	uint32_t status = REG_PIOA_ISR;	//read PIOA interrupt status & clear interrupt flags
// 
// 	if ((status & PIO_ISR_P12)){	//check if Encoder Button was pressed
// 
// 		position = 1;	//reset positon to center
// 	    bpm = 120;
// 	}
// 
// 	else {	//  handle Encoder signal inputs
// 
// 		//read Encoder input A
// 		bool A_in = REG_PIOA_PDSR & PIO_ODSR_P5;
// 		//read Encoder input B
// 		bool B_in = REG_PIOA_PDSR & PIO_ODSR_P6;
// 
// 		A_seq = A_seq << 1;
// 		A_seq |= A_in;
// 
// 		B_seq = B_seq << 1;
// 		B_seq |= B_in;
// 
// 		A_seq &= 0b00001111;
// 		B_seq &= 0b00001111;
// 
// 		if ((A_seq == 0b00001001) && (B_seq == 0b00000011)){
// 
// 			if (position < 2)	//Check if not at Right-most LED
// 			position++;		//Move position right
// 			if(bpm < 999) {
// 				bpm+=1;
// 			}
// 
// 			if (brightness != 0x80){
// 				brightness = brightness << 1;
// 			}
// 			//Set Write Command, Function, and BC Bits
// 			SPI_byteSend(0x94);
// 			SPI_byteSend(0x5F);
// 			SPI_byteSend(0xFF);
// 			SPI_byteSend(0x80);
// 
// 			//set PWM GrayScale Bits (BITS 191-0)
// 			for (int i = 0; i < 24; i++){
// 				SPI_byteSend(brightness);
// 			}
// 
// 			//Set Write Command, Function, and BC Bits
// 			SPI_byteSend(0x94);
// 			SPI_byteSend(0x5F);
// 			SPI_byteSend(0xFF);
// 			SPI_byteSend(0xFF);
// 
// 			//set PWM GrayScale Bits (BITS 191-0)
// 			for (int i = 0; i < 24; i++){
// 				SPI_byteSend(brightness);
// 			}
// 	
// 			delay_cycles(5*8);
// 		}
// 
// 
// 		else if ((A_seq == 0b00000011) && (B_seq == 0b00001001)){
// 
// 			if (position > 0)	//Check if not at Left-most LED
// 			position--;		//Move position left
// 			if(bpm > 20) {
// 				bpm-=1;
// 			}
// 
// 			if (brightness != 0x01){
// 				brightness = brightness >> 1;
// 			}
// 
// 			//Set Write Command, Function, and BC Bits
// 			SPI_byteSend(0x94);
// 			SPI_byteSend(0x5F);
// 			SPI_byteSend(0xFF);
// 			SPI_byteSend(0x80);
// 
// 			//set PWM GrayScale Bits (BITS 191-0)
// 			for (int i = 0; i < 24; i++){
// 				SPI_byteSend(brightness);
// 			}
// 
// 			//Set Write Command, Function, and BC Bits
// 			SPI_byteSend(0x94);
// 			SPI_byteSend(0x5F);
// 			SPI_byteSend(0xFF);
// 			SPI_byteSend(0xFF);
// 
// 			//set PWM GrayScale Bits (BITS 191-0)
// 			for (int i = 0; i < 24; i++){
// 				SPI_byteSend(brightness);
// 			}
// 	
// 			delay_cycles(5*8);
// 		}
// 	}
// 
// 	update_timers(bpm);
// 
// }

void PIOC_Handler(void){


}
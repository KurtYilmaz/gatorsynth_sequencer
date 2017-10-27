/*
 * leds.c
 *
 * Created: 10/8/2017 5:26:13 PM
 *  Author: Kyle
 */ 

#include <asf.h>
#include <stdbool.h>
#include "spi.h"
#include "timers.h"



int leds_status[16] = {0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0};

uint16_t leds_data_1[12] = {0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000};
uint16_t leds_data_2[12] = {0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000};
uint16_t leds_data_3[12] = {0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000};
uint16_t leds_data_4[12] = {0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000,
							0x0000, 0x0000, 0x0000};	

uint8_t offset;
uint8_t toffset;



void leds_update_cursor(uint8_t curr_step);
void leds_update_note(uint8_t led_pos);
void leds_update_display();
void led_toggle(uint8_t top_row, uint8_t bottom_row);
int leds_status_get(uint8_t curr_step);

int leds_status_get(uint8_t curr_step){
	return leds_status[curr_step];
}

void led_toggle(uint8_t top_row, uint8_t bottom_row){

	switch(bottom_row) {
		case 254 :
			leds_status[15] = abs(leds_status[15] - 1);
			break;
		case 253 :
			leds_status[14] = abs(leds_status[14] - 1);
			break;
		case 251 :
			leds_status[13] = abs(leds_status[13] - 1);
			break;
		case 247 :
			leds_status[12] = abs(leds_status[12] - 1);
			break;
		case 239 :
			leds_status[11] = abs(leds_status[11] - 1);
			break;
		case 223 :
			leds_status[10] = abs(leds_status[10] - 1);
			break;
		case 191 :
			leds_status[9] = abs(leds_status[9] - 1);
			break;
		case 127 :
			leds_status[8] = abs(leds_status[8] - 1);
			break;
		default :
			break;
	}

	switch(top_row) {
		case 126 :
			leds_status[7] = abs(leds_status[7] - 1);
			break;
		case 125 :
			leds_status[6] = abs(leds_status[6] - 1);
			break;
		case 123 :
			leds_status[5] = abs(leds_status[5] - 1);
			break;
		case 119 :
			leds_status[4] = abs(leds_status[4] - 1);
			break;
		case 111 :
			leds_status[3] = abs(leds_status[3] - 1);
			break;
		case 95 :
			leds_status[2] = abs(leds_status[2] - 1);
			break;
		case 63 :
			leds_status[1] = abs(leds_status[1] - 1);
			break;
		case 2 :
			leds_status[0] = abs(leds_status[0] - 1);
			break;
		default : 
			break;
	}
	
	SPI_led_init();
	leds_update_cursor(curr_step);
}

void leds_update_cursor(uint8_t curr_step){

/* Initialize the Notes that are Enabled as Blue */
	for (int i = 0; i < 16; i++){
			if ( (i >= 0) && (i < 4) ){
				toffset = (i)*3;
				if(leds_status[i] == 1){
					leds_data_1[toffset] = 0x0000;
					leds_data_1[toffset+1] = 0x0000;
					leds_data_1[toffset+2] = 0xFFFF;
				}
				else{
					leds_data_1[toffset] = 0x0000;
					leds_data_1[toffset+1] = 0x0000;
					leds_data_1[toffset+2] = 0x0000;
				}
			}
			else if ( (i >= 4) && (i < 8) ){
				toffset = (i % 4)*3;
				if(leds_status[i] == 1){
					leds_data_2[toffset] = 0x0000;
					leds_data_2[toffset+1] = 0x0000;
					leds_data_2[toffset+2] = 0xFFFF;
				}
				else{
					leds_data_2[toffset] = 0x0000;
					leds_data_2[toffset+1] = 0x0000;
					leds_data_2[toffset+2] = 0x0000;
				}
			}
			else if ( (i >= 8) && (i < 12) ){
				toffset = (i % 8)*3;
				if(leds_status[i] == 1){
					leds_data_3[toffset] = 0x0000;
					leds_data_3[toffset+1] = 0x0000;
					leds_data_3[toffset+2] = 0xFFFF;
				}
				else{
					leds_data_3[toffset] = 0x0000;
					leds_data_3[toffset+1] = 0x0000;
					leds_data_3[toffset+2] = 0x0000;
				}
			}
			else {
				toffset = (i % 12)*3;
				if(leds_status[i] == 1){
					leds_data_4[toffset] = 0x0000;
					leds_data_4[toffset+1] = 0x0000;
					leds_data_4[toffset+2] = 0xFFFF;
				}
				else{
					leds_data_4[toffset] = 0x0000;
					leds_data_4[toffset+1] = 0x0000;
					leds_data_4[toffset+2] = 0x0000;
				}
			}
	}


/* Update Cursor to correct position */
	if ( (curr_step >= 0) && (curr_step < 4) ){
		offset = (curr_step)*3;
		leds_data_1[offset] = 0xFFFF;
		leds_data_1[offset+1] = 0x0FFF;
		leds_data_1[offset+2] = 0x0000;
	}
	else if ( (curr_step >= 4) && (curr_step < 8) ){
		offset = (curr_step % 4)*3;
		leds_data_2[offset] = 0xFFFF;
		leds_data_2[offset+1] = 0x0FFF;
		leds_data_2[offset+2] = 0x0000;
	}
	else if ( (curr_step >= 8) && (curr_step < 12) ){
		offset = (curr_step % 8)*3;
		leds_data_3[offset] = 0xFFFF;
		leds_data_3[offset+1] = 0x0FFF;
		leds_data_3[offset+2] = 0x0000;
	}
	else if ( (curr_step >= 12) && (curr_step < 16) ){
		offset = (curr_step % 12)*3;
		leds_data_4[offset] = 0xFFFF;
		leds_data_4[offset+1] = 0x0FFF;
		leds_data_4[offset+2] = 0x0000;
	}


	leds_update_display();
}

void leds_update_note(uint8_t led_pos){

	leds_update_display();
}

 void leds_update_display(){

	cpu_irq_disable();

	//Set Write Command, Function, and BC Bits
	SPI_byteSend(0x94);
	SPI_byteSend(0x5F);
	SPI_byteSend(0xFF);
	SPI_byteSend(0xFF);
	
	//set PWM GrayScale Bits (BITS 191-0)
// 	for (int i = 11; i > -1; i--){
// 		SPI_byteSend( (uint8_t) (leds_data_1[i] >> 8) );
// 		SPI_byteSend( (uint8_t) (leds_data_1[i]) );
// 	}

	SPI_byteSend( (uint8_t) (leds_data_1[2] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[2]) );
	SPI_byteSend( (uint8_t) (leds_data_1[1] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[1]) );
	SPI_byteSend( (uint8_t) (leds_data_1[0] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[0]) );

	SPI_byteSend( (uint8_t) (leds_data_3[2] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[2]) );
	SPI_byteSend( (uint8_t) (leds_data_3[1] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[1]) );
	SPI_byteSend( (uint8_t) (leds_data_3[0] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[0]) );

	SPI_byteSend( (uint8_t) (leds_data_3[5] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[5]) );
	SPI_byteSend( (uint8_t) (leds_data_3[4] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[4]) );
	SPI_byteSend( (uint8_t) (leds_data_3[3] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[3]) );

	SPI_byteSend( (uint8_t) (leds_data_1[5] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[5]) );
	SPI_byteSend( (uint8_t) (leds_data_1[4] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[4]) );
	SPI_byteSend( (uint8_t) (leds_data_1[3] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[3]) );

	//Set Write Command, Function, and BC Bits
	SPI_byteSend(0x94);
	SPI_byteSend(0x5F);
	SPI_byteSend(0xFF);
	SPI_byteSend(0xFF);
	
	//set PWM GrayScale Bits (BITS 191-0)
// 	for (int i = 11; i > -1; i--){
// 		SPI_byteSend( (uint8_t) (leds_data_2[i] >> 8) );
// 		SPI_byteSend( (uint8_t) (leds_data_2[i]) );
// 	}

	SPI_byteSend( (uint8_t) (leds_data_1[8] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[8]) );
	SPI_byteSend( (uint8_t) (leds_data_1[7] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[7]) );
	SPI_byteSend( (uint8_t) (leds_data_1[6] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[6]) );

	SPI_byteSend( (uint8_t) (leds_data_3[8] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[8]) );
	SPI_byteSend( (uint8_t) (leds_data_3[7] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[7]) );
	SPI_byteSend( (uint8_t) (leds_data_3[6] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[6]) );

	SPI_byteSend( (uint8_t) (leds_data_3[11] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[11]) );
	SPI_byteSend( (uint8_t) (leds_data_3[10] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[10]) );
	SPI_byteSend( (uint8_t) (leds_data_3[9] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_3[9]) );

	SPI_byteSend( (uint8_t) (leds_data_1[11] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[11]) );
	SPI_byteSend( (uint8_t) (leds_data_1[10] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[10]) );
	SPI_byteSend( (uint8_t) (leds_data_1[9] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_1[9]) );

	//Set Write Command, Function, and BC Bits
	SPI_byteSend(0x94);
	SPI_byteSend(0x5F);
	SPI_byteSend(0xFF);
	SPI_byteSend(0xFF);

	//set PWM GrayScale Bits (BITS 191-0)
// 	for (int i = 11; i > -1; i--){
// 		SPI_byteSend( (uint8_t) (leds_data_3[i] >> 8) );
// 		SPI_byteSend( (uint8_t) (leds_data_3[i]) );
// 	}

	SPI_byteSend( (uint8_t) (leds_data_2[2] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[2]) );
	SPI_byteSend( (uint8_t) (leds_data_2[1] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[1]) );
	SPI_byteSend( (uint8_t) (leds_data_2[0] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[0]) );

	SPI_byteSend( (uint8_t) (leds_data_4[2] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[2]) );
	SPI_byteSend( (uint8_t) (leds_data_4[1] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[1]) );
	SPI_byteSend( (uint8_t) (leds_data_4[0] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[0]) );

	SPI_byteSend( (uint8_t) (leds_data_4[5] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[5]) );
	SPI_byteSend( (uint8_t) (leds_data_4[4] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[4]) );
	SPI_byteSend( (uint8_t) (leds_data_4[3] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[3]) );

	SPI_byteSend( (uint8_t) (leds_data_2[5] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[5]) );
	SPI_byteSend( (uint8_t) (leds_data_2[4] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[4]) );
	SPI_byteSend( (uint8_t) (leds_data_2[3] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[3]) );

	//Set Write Command, Function, and BC Bits
	SPI_byteSend(0x94);
	SPI_byteSend(0x5F);
	SPI_byteSend(0xFF);
	SPI_byteSend(0xFF);
	
	//set PWM GrayScale Bits (BITS 191-0)
// 	for (int i = 11; i > -1; i--){
// 		SPI_byteSend( (uint8_t) (leds_data_4[i] >> 8) );
// 		SPI_byteSend( (uint8_t) (leds_data_4[i]) );
// 	}

	SPI_byteSend( (uint8_t) (leds_data_2[8] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[8]) );
	SPI_byteSend( (uint8_t) (leds_data_2[7] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[7]) );
	SPI_byteSend( (uint8_t) (leds_data_2[6] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[6]) );

	SPI_byteSend( (uint8_t) (leds_data_4[8] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[8]) );
	SPI_byteSend( (uint8_t) (leds_data_4[7] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[7]) );
	SPI_byteSend( (uint8_t) (leds_data_4[6] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[6]) );

	SPI_byteSend( (uint8_t) (leds_data_4[11] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[11]) );
	SPI_byteSend( (uint8_t) (leds_data_4[10] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[10]) );
	SPI_byteSend( (uint8_t) (leds_data_4[9] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_4[9]) );

	SPI_byteSend( (uint8_t) (leds_data_2[11] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[11]) );
	SPI_byteSend( (uint8_t) (leds_data_2[10] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[10]) );
	SPI_byteSend( (uint8_t) (leds_data_2[9] >> 8) );
	SPI_byteSend( (uint8_t) (leds_data_2[9]) );


	delay_ms(2.74);
	cpu_irq_enable();

 }
/*
 * leds.c
 *
 * Created: 10/8/2017 5:26:13 PM
 *  Author: Kyle
 */ 

#include <asf.h>
#include <stdbool.h>
#include "spi.h"

uint16_t leds_prev_data[3] = {0x0000, 0x0000, 0x0fff};
 
 uint8_t leds_status[16] = {0, 0, 0, 0, 0, 0, 0, 0,
							0, 0, 0, 0, 0, 0, 0, 0};

 uint16_t leds_data_1[12] = {0x0000, 0x0000, 0x3fff,
							 0x0000, 0x0000, 0x0000,
							 0x0000, 0x0000, 0x3fff,
							 0x0000, 0x0000, 0x0000};
 uint16_t leds_data_2[12] = {0x0000, 0x0000, 0x3fff,
							 0x0000, 0x0000, 0x0000,
							 0x0000, 0x0000, 0x3fff,
							 0x0000, 0x0000, 0x0000};
 uint16_t leds_data_3[12] = {0x0000, 0x0000, 0x0000,
							 0x0000, 0x0000, 0x3fff,
							 0x0000, 0x0000, 0x3fff,
							 0x0000, 0x0000, 0x3fff};
 uint16_t leds_data_4[12] = {0x0000, 0x0000, 0x3fff,
							 0x0000, 0x0000, 0x0000,
							 0x0000, 0x0000, 0x0000,
							 0x0000, 0x0000, 0x3fff};


void leds_update_cursor(uint8_t curr_led);
void leds_update_note(uint8_t led_pos);
void leds_update_display();
void leds_save_prev(uint8_t curr_led);



void leds_update_cursor(uint8_t curr_led){

	switch(curr_led){
		case 0 : 
			leds_data_4[9] = leds_prev_data[0];
			leds_data_4[10] = leds_prev_data[1];
			leds_data_4[11] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_1[0];
			leds_prev_data[1] = leds_data_1[1];
			leds_prev_data[2] = leds_data_1[2];

			leds_data_1[0] = 0x1FFF;
			leds_data_1[1] = 0x03FF;
			leds_data_1[2] = 0x0000;
			break;
		case 1 :
			leds_data_1[0] = leds_prev_data[0];
			leds_data_1[1] = leds_prev_data[1];
			leds_data_1[2] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_1[3];
			leds_prev_data[1] = leds_data_1[4];
			leds_prev_data[2] = leds_data_1[5];

			leds_data_1[3] = 0x1FFF;
			leds_data_1[4] = 0x03FF;
			leds_data_1[5] = 0x0000;
			break;
		case 2 :
			leds_data_1[3] = leds_prev_data[0];
			leds_data_1[4] = leds_prev_data[1];
			leds_data_1[5] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_1[6];
			leds_prev_data[1] = leds_data_1[7];
			leds_prev_data[2] = leds_data_1[8];

			leds_data_1[6] = 0x1FFF;
			leds_data_1[7] = 0x03FF;
			leds_data_1[8] = 0x0000;
			break;
		case 3 :
			leds_data_1[6] = leds_prev_data[0];
			leds_data_1[7] = leds_prev_data[1];
			leds_data_1[8] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_1[9];
			leds_prev_data[1] = leds_data_1[10];
			leds_prev_data[2] = leds_data_1[11];

			leds_data_1[9] = 0x1FFF;
			leds_data_1[10] = 0x03FF;
			leds_data_1[11] = 0x0000;
			break;
		case 4 :
			leds_data_1[9] = leds_prev_data[0];
			leds_data_1[10] = leds_prev_data[1];
			leds_data_1[11] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_2[0];
			leds_prev_data[1] = leds_data_2[1];
			leds_prev_data[2] = leds_data_2[2];

			leds_data_2[0] = 0x1FFF;
			leds_data_2[1] = 0x03FF;
			leds_data_2[2] = 0x0000;
			break;
		case 5 :
			leds_data_2[0] = leds_prev_data[0];
			leds_data_2[1] = leds_prev_data[1];
			leds_data_2[2] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_2[3];
			leds_prev_data[1] = leds_data_2[4];
			leds_prev_data[2] = leds_data_2[5];

			leds_data_2[3] = 0x1FFF;
			leds_data_2[4] = 0x03FF;
			leds_data_2[5] = 0x0000;
			break;
		case 6 :
			leds_data_2[3] = leds_prev_data[0];
			leds_data_2[4] = leds_prev_data[1];
			leds_data_2[5] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_2[6];
			leds_prev_data[1] = leds_data_2[7];
			leds_prev_data[2] = leds_data_2[8];

			leds_data_2[6] = 0x1FFF;
			leds_data_2[7] = 0x03FF;
			leds_data_2[8] = 0x0000;
			break;
		case 7 :
			leds_data_2[6] = leds_prev_data[0];
			leds_data_2[7] = leds_prev_data[1];
			leds_data_2[8] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_2[9];
			leds_prev_data[1] = leds_data_2[10];
			leds_prev_data[2] = leds_data_2[11];

			leds_data_2[9] = 0x1FFF;
			leds_data_2[10] = 0x03FF;
			leds_data_2[11] = 0x0000;
			break;
		case 8 :
			leds_data_2[9] = leds_prev_data[0];
			leds_data_2[10] = leds_prev_data[1];
			leds_data_2[11] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_3[0];
			leds_prev_data[1] = leds_data_3[1];
			leds_prev_data[2] = leds_data_3[2];

			leds_data_3[0] = 0x1FFF;
			leds_data_3[1] = 0x03FF;
			leds_data_3[2] = 0x0000;
			break;
		case 9 :
			leds_data_3[0] = leds_prev_data[0];
			leds_data_3[1] = leds_prev_data[1];
			leds_data_3[2] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_3[3];
			leds_prev_data[1] = leds_data_3[4];
			leds_prev_data[2] = leds_data_3[5];

			leds_data_3[3] = 0x1FFF;
			leds_data_3[4] = 0x03FF;
			leds_data_3[5] = 0x0000;
			break;
		case 10 :
			leds_data_3[3] = leds_prev_data[0];
			leds_data_3[4] = leds_prev_data[1];
			leds_data_3[5] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_3[6];
			leds_prev_data[1] = leds_data_3[7];
			leds_prev_data[2] = leds_data_3[8];

			leds_data_3[6] = 0x1FFF;
			leds_data_3[7] = 0x03FF;
			leds_data_3[8] = 0x0000;
			break;
		case 11 :
			leds_data_3[6] = leds_prev_data[0];
			leds_data_3[7] = leds_prev_data[1];
			leds_data_3[8] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_3[9];
			leds_prev_data[1] = leds_data_3[10];
			leds_prev_data[2] = leds_data_3[11];

			leds_data_3[9] = 0x1FFF;
			leds_data_3[10] = 0x03FF;
			leds_data_3[11] = 0x0000;
			break;
		case 12 :
			leds_data_3[9] = leds_prev_data[0];
			leds_data_3[10] = leds_prev_data[1];
			leds_data_3[11] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_4[0];
			leds_prev_data[1] = leds_data_4[1];
			leds_prev_data[2] = leds_data_4[2];

			leds_data_4[0] = 0x1FFF;
			leds_data_4[1] = 0x03FF;
			leds_data_4[2] = 0x0000;
			break;
		case 13 :
			leds_data_4[0] = leds_prev_data[0];
			leds_data_4[1] = leds_prev_data[1];
			leds_data_4[2] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_4[3];
			leds_prev_data[1] = leds_data_4[4];
			leds_prev_data[2] = leds_data_4[5];

			leds_data_4[3] = 0x1FFF;
			leds_data_4[4] = 0x03FF;
			leds_data_4[5] = 0x0000;
			break;
		case 14 :
			leds_data_4[3] = leds_prev_data[0];
			leds_data_4[4] = leds_prev_data[1];
			leds_data_4[5] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_4[6];
			leds_prev_data[1] = leds_data_4[7];
			leds_prev_data[2] = leds_data_4[8];

			leds_data_4[6] = 0x1FFF;
			leds_data_4[7] = 0x03FF;
			leds_data_4[8] = 0x0000;
			break;
		case 15 :
			leds_data_4[6] = leds_prev_data[0];
			leds_data_4[7] = leds_prev_data[1];
			leds_data_4[8] = leds_prev_data[2];

			leds_prev_data[0] = leds_data_4[9];
			leds_prev_data[1] = leds_data_4[10];
			leds_prev_data[2] = leds_data_4[11];

			leds_data_4[9] = 0x1FFF;
			leds_data_4[10] = 0x03FF;
			leds_data_4[11] = 0x0000;
			break;
	}

	leds_update_display();
}

void leds_update_note(uint8_t led_pos){

	leds_update_display();
}

 void leds_update_display(){
 
	//Set Write Command, Function, and BC Bits
	SPI_byteSend(0x94);
	SPI_byteSend(0x5F);
	SPI_byteSend(0xFF);
	SPI_byteSend(0xFF);
	
	//set PWM GrayScale Bits (BITS 191-0)
	for (int i = 11; i > -1; i--){
		SPI_byteSend( (uint8_t) (leds_data_4[i] >> 8) );
		SPI_byteSend( (uint8_t) (leds_data_4[i]) );
	}

	//Set Write Command, Function, and BC Bits
	SPI_byteSend(0x94);
	SPI_byteSend(0x5F);
	SPI_byteSend(0xFF);
	SPI_byteSend(0xFF);
	
	//set PWM GrayScale Bits (BITS 191-0)
	for (int i = 11; i > -1; i--){
		SPI_byteSend( (uint8_t) (leds_data_3[i] >> 8) );
		SPI_byteSend( (uint8_t) (leds_data_3[i]) );
	}

	//Set Write Command, Function, and BC Bits
	SPI_byteSend(0x94);
	SPI_byteSend(0x5F);
	SPI_byteSend(0xFF);
	SPI_byteSend(0xFF);

	//set PWM GrayScale Bits (BITS 191-0)
	for (int i = 11; i > -1; i--){
		SPI_byteSend( (uint8_t) (leds_data_2[i] >> 8) );
		SPI_byteSend( (uint8_t) (leds_data_2[i]) );
	}

	//Set Write Command, Function, and BC Bits
	SPI_byteSend(0x94);
	SPI_byteSend(0x5F);
	SPI_byteSend(0xFF);
	SPI_byteSend(0xFF);
	
	//set PWM GrayScale Bits (BITS 191-0)
	for (int i = 11; i > -1; i--){
		SPI_byteSend( (uint8_t) (leds_data_1[i] >> 8) );
		SPI_byteSend( (uint8_t) (leds_data_1[i]) );
	}

	delay_ms(2.74);

 };
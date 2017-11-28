/*
 * dac.c
 *
 * Created: 10/12/2017 6:49:09 PM
 *  Author: Kyle
 */ 
 
#include <asf.h>
#include <stdlib.h>
#include "spi.h"
#include "sequencer.h"


#define VREF 10
#define max 1023

void DAC_write_cv(float voltage, uint8_t channel){

	cpu_irq_disable();

	float float_voltage = (max*(voltage))/VREF;
	uint16_t dac_voltage = (uint16_t) float_voltage;

	uint8_t low_byte;
	uint8_t high_byte;

	if (channel == CHANNEL_1){
		low_byte = (uint8_t) (dac_voltage << 2);
		high_byte = ((uint8_t) (dac_voltage >> 6)) | (0x90);
		REG_PIOB_CODR |=  PIO_PER_P13;
	}
	else if (channel == CHANNEL_2){
		low_byte = (uint8_t) (dac_voltage << 2);
		high_byte = ((uint8_t) (dac_voltage >> 6)) | (0xA0);
		REG_PIOB_CODR |=  PIO_PER_P13;
	}
	else if (channel == CHANNEL_3){
		low_byte = (uint8_t) (dac_voltage << 2);
		high_byte = ((uint8_t) (dac_voltage >> 6)) | (0x90);
		REG_PIOB_CODR |=  PIO_PER_P14;
	}
	else{
		low_byte = (uint8_t) (dac_voltage << 2);
		high_byte = ((uint8_t) (dac_voltage >> 6)) | (0xA0);
		REG_PIOB_CODR |=  PIO_PER_P14;
	}
	
	SPI_byteSend(high_byte);
	SPI_byteSend(low_byte);
	delay_us(3);

	if (channel == CHANNEL_1){
		REG_PIOB_SODR |=  PIO_PER_P13;
	}
	else if (channel == CHANNEL_2){
		REG_PIOB_SODR |=  PIO_PER_P13;
	}
	else if (channel == CHANNEL_3){
		REG_PIOB_SODR |=  PIO_PER_P14;
	}
	else{
		REG_PIOB_SODR |=  PIO_PER_P14;
	}

	cpu_irq_enable();
	

}

void DAC_write_gate_on(uint8_t channel){

	if (channel == CHANNEL_1){
		REG_PIOB_CODR |=  PIO_PER_P0;
	}
	else if (channel == CHANNEL_2){
		REG_PIOB_CODR |=  PIO_PER_P1;
	}
	else if (channel == CHANNEL_3){
		REG_PIOB_CODR |=  PIO_PER_P2;
	}
	else{
		REG_PIOB_CODR |=  PIO_PER_P3;
	}

// 	cpu_irq_disable();
// 
// 	float float_voltage = (max*(0))/VREF;
// 	uint16_t dac_voltage = (uint16_t) float_voltage;
// 
// 	uint8_t low_byte = (uint8_t) (dac_voltage << 2);
// 	uint8_t high_byte = ((uint8_t) (dac_voltage >> 6)) | (0xA0);
// 
// 	SPI_dac_init();
// 	REG_PIOB_CODR |=  PIO_PER_P13;
// 	SPI_byteSend(high_byte);
// 	SPI_byteSend(low_byte);
// 	delay_us(3);
// 	REG_PIOB_SODR |=  PIO_PER_P13;
// 
// 	cpu_irq_enable();
}

void DAC_write_gate_off(uint8_t channel){

	if (channel == CHANNEL_1){
		REG_PIOB_SODR |=  PIO_PER_P0;
	}
	else if (channel == CHANNEL_2){
		REG_PIOB_SODR |=  PIO_PER_P1;
	}
	else if (channel == CHANNEL_3){
		REG_PIOB_SODR |=  PIO_PER_P2;
	}
	else{
		REG_PIOB_SODR |=  PIO_PER_P3;
	}

// 	cpu_irq_disable();
// 
// 	float float_voltage = (max*(VREF))/VREF;
// 	uint16_t dac_voltage = (uint16_t) float_voltage;
// 
// 	uint8_t low_byte = (uint8_t) (dac_voltage << 2);
// 	uint8_t high_byte = ((uint8_t) (dac_voltage >> 6)) | (0xA0);
// 
// 	SPI_dac_init();
// 	REG_PIOB_CODR |=  PIO_PER_P13;
// 	SPI_byteSend(high_byte);
// 	SPI_byteSend(low_byte);
// 	delay_us(3);
// 	REG_PIOB_SODR |=  PIO_PER_P13;
// 
// 	cpu_irq_enable();

}


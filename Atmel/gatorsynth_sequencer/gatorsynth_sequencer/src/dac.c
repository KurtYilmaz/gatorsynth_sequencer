/*
 * dac.c
 *
 * Created: 10/12/2017 6:49:09 PM
 *  Author: Kyle
 */ 
 
#include <asf.h>
#include <stdlib.h>
#include "spi.h"


#define VREF 3.3
#define max 1023

void DAC_write_cv(float voltage){

	//cpu_irq_disable();

	float float_voltage = (max*(voltage))/VREF;
	uint16_t dac_voltage = (uint16_t) float_voltage;

	uint8_t low_byte = (uint8_t) (dac_voltage << 2);
	uint8_t high_byte = ((uint8_t) (dac_voltage >> 6)) | (0x90);

	
	SPI_dac_init();
	REG_PIOB_CODR |=  PIO_PER_P13;
	SPI_byteSend(high_byte);
	SPI_byteSend(low_byte);
	delay_us(3);
	REG_PIOB_SODR |=  PIO_PER_P13;

	//cpu_irq_enable();
	

}

void DAC_write_gate_on(){

	//cpu_irq_disable();

	float float_voltage = (max*(VREF))/VREF;
	uint16_t dac_voltage = (uint16_t) float_voltage;

	uint8_t low_byte = (uint8_t) (dac_voltage << 2);
	uint8_t high_byte = ((uint8_t) (dac_voltage >> 6)) | (0xA0);

	SPI_dac_init();
	REG_PIOB_CODR |=  PIO_PER_P13;
	SPI_byteSend(high_byte);
	SPI_byteSend(low_byte);
	delay_us(3);
	REG_PIOB_SODR |=  PIO_PER_P13;

	//cpu_irq_enable();
}

void DAC_write_gate_off(){

	//cpu_irq_disable();

	float float_voltage = (max*(0))/VREF;
	uint16_t dac_voltage = (uint16_t) float_voltage;

	uint8_t low_byte = (uint8_t) (dac_voltage << 2);
	uint8_t high_byte = ((uint8_t) (dac_voltage >> 6)) | (0xA0);

	SPI_dac_init();
	REG_PIOB_CODR |=  PIO_PER_P13;
	SPI_byteSend(high_byte);
	SPI_byteSend(low_byte);
	delay_us(3);
	REG_PIOB_SODR |=  PIO_PER_P13;

	//cpu_irq_enable();

}


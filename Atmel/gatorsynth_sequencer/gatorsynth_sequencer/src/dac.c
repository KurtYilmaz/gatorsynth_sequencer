/*
 * dac.c
 *
 * Created: 10/12/2017 6:49:09 PM
 *  Author: Kyle
 */ 
 
#include <asf.h>
#include <stdlib.h>
#include "spi.h"


#define VREF 5
#define max 1023

void DAC_write_cv(float voltage){

	float float_voltage = (max*(voltage))/VREF;
	uint16_t dac_voltage = (uint16_t) float_voltage;

	uint8_t low_byte = (uint8_t) (dac_voltage << 2);
	uint8_t high_byte = ((uint8_t) (dac_voltage >> 6)) | (0xF0);

	REG_PIOB_CODR |= PIO_CODR_P14;
	SPI_dac_init();
	SPI_byteSend(high_byte);
	SPI_byteSend(low_byte);
	

}

void DAC_write_gate_on(){


	uint8_t dac_voltage = (uint8_t) max;

	SPI_dac_init();
	SPI_byteSend(0b11111110);
	SPI_byteSend( dac_voltage );
	SPI_dac_load();

	SPI_dac_init();
	SPI_byteSend(0b11111111);
	SPI_byteSend( dac_voltage );
	SPI_dac_load();


}

void DAC_write_gate_off(){


	uint8_t dac_voltage = (uint8_t) 0;

	SPI_dac_init();
	SPI_byteSend(0b11111110);
	SPI_byteSend( dac_voltage );
	SPI_dac_load();

	SPI_dac_init();
	SPI_byteSend(0b11111111);
	SPI_byteSend( dac_voltage );
	SPI_dac_load();


}


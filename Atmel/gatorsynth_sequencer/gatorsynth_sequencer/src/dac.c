/*
 * dac.c
 *
 * Created: 10/12/2017 6:49:09 PM
 *  Author: Kyle
 */ 
 
#include <asf.h>
#include <stdlib.h>
#include "spi.h"


void DAC_write(uint8_t voltage){

	SPI_dac_init();
	SPI_byteSend(0b11111100);
	SPI_byteSend(voltage);
	SPI_dac_load();

}

#include <asf.h>
#include <stdbool.h>
#include <stdlib.h>
#include "encoders.h"
#include "timers.h"
#include "leds.h"
#include "spi.h"
#include "dac.h"
#include "notes.h"
#include "i2c.h"


uint16_t bpm = 120;
uint8_t brightness = 0x07;
uint8_t dataL;
uint8_t dataH;

int main (void)
{
	sysclk_init();				//initialize system clock
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer

	board_init();				//board init (currently empty)

	SPI_led_init();
	leds_update_display();

	timers_init();				//initiate timer for Flashing LED on PA20
	update_timers(bpm);

	REG_PIOB_PER |= PIO_PER_P3; //enable PIO controller on PB14
	REG_PIOB_OER |= PIO_PER_P3; //enable output on pin PB14
	REG_PIOB_SODR |= PIO_PER_P3; //set output high on PB14 as default
	Encoder_init();				//initialize encoders

	i2c_init();
	init_IO_int();
// 
// 	//configure register to enable interrupt
// 	i2c_start(MAX7314_slaveAddress, write);
// 	i2c_write(MAX7314_configRegister);
// 	i2c_writeStop(0b00001000);

	//configure ports as Inputs
// 	i2c_start(MAX7314_slaveAddress, write);
// 	i2c_write(MAX7314_portConfigRegisterLow);
// 	i2c_write(0xFF);	//configure low port as IN
// 	i2c_writeStop(0xFF);//configure high port as IN (register addr auto increments)


	while (1)
	{
		//wait for button interrupt to read data
		//configure register to enable interrupt
	i2c_start(MAX7314_slaveAddress, 0);
	
	i2c_write(MAX7314_configRegister);

	i2c_writeStop(0b00001000);
	
	}
}

 void PIOB_Handler(){

	 uint32_t status = REG_PIOB_ISR;	//read PIOB interrupt status & clear interrupt flags
 
	 //check if Io expander interrupt was driven
	 if (status & PIO_ISR_P10){
		
// 		i2c_start(MAX7314_slaveAddress, read);
// 		i2c_write(MAX7314_inputPortLow);
// 		dataL = i2c_readACK();
// 		dataH = i2c_readNACK();
	 }

 }
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
#include "sequencer.h"
#include "adc.h"
#include "displays.h"
#include <twi.h>

uint8_t brightness = 0x07;
uint8_t count = 0;


uint8_t port_data[2] = {0};
uint8_t temp_data[2] = {0};

#define BOARD_ID_TWI    ID_TWI0
#define BOARD_BASE_TWI  TWI0

void config_MAX7314(void);
void read_MAX7314(uint8_t *port_data);

int main (void)
{
	sysclk_init();				//initialize system clock
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer

	board_init();				//board init (currently empty)
	init_sequencer_controls();

	SPI_led_init();
	leds_update_display();
	
	timers_init();				//initiate timer for Flashing LED on PA20
	update_timers(bpm);
	
	ADC_init();
	Encoder_init();				//initialize encoders

	i2c_init();
	//notes_inc(5);
	

	init_IO_int();
	config_MAX7314();
	read_MAX7314(port_data);
	all_displays_init();
	//note_display(5);
	//bpm_display(bpm);
	page_display(display_page);

	while (1)
	{
	//read_MAX7314(port_data);
	//config_MAX7314();
	//delay_us(10);
	//note_display(5);
	}
}

 void PIOB_Handler(){

	 uint32_t status = REG_PIOB_ISR;	//read PIOB interrupt status & clear interrupt flags
 
	 //check if Io expander interrupt was driven
	 if (status & PIO_ISR_P10){
		read_MAX7314(temp_data);

		if  ( !((temp_data[0] == 127) && (temp_data[1] == 255)) ){
			port_data[0] = temp_data[0];
			port_data[1] = temp_data[1];

			count++;
			if (count >= 2){
				led_toggle(port_data[0], port_data[1]);
				count = 0;
			}
		}
		
	 }

	 else{
		read_MAX7314(temp_data);
		read_MAX7314(temp_data);
		uint8_t test = 0;
	 }

 }

 void config_MAX7314(){
	twi_packet_t packet_tx;
	uint8_t config_data[] = {MAX7314_configRegister, 0x08};

	/* Configure the Chip Config Register */
	packet_tx.chip        = 0b0100000;
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) config_data;
	packet_tx.length      = 2;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);


	uint8_t port_data_write[] = {MAX7314_portConfigRegisterLow, 0xFF, 0xFF};

	/* Configure the Chip Ports as Inputs */
	packet_tx.chip        = 0b0100000;
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) port_data_write;
	packet_tx.length      = 3;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);
 }

 void read_MAX7314(uint8_t *data){
	/* Data Packets for tx/rx */
	twi_packet_t packet_rx, packet_tx;
	uint8_t port_addr[] = {MAX7314_inputPortLow};

	
	/* Write the command byte address to be the Low byte of the Input Port */
	packet_tx.chip        = 0b0100000;
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) port_addr;
	packet_tx.length      = 1;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);


	/* Read Data from the Low and High Input Ports */
	packet_rx.chip        = 0b0100000;
	packet_rx.addr_length = 0;
	packet_rx.buffer      = data;
	packet_rx.length      = 2;
	twi_master_read(BOARD_BASE_TWI, &packet_rx);


 }


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
#include "flash_mem.h"
#include <twi.h>

uint8_t brightness = 0x07;
uint8_t button_count = 0;
uint8_t encoder_count = 0;


uint8_t button_port_data[2] = {0};
uint8_t encoder_port_data[2] = {0};
uint8_t temp_data[2] = {0};

#define BOARD_ID_TWI    ID_TWI0
#define BOARD_BASE_TWI  TWI0

void config_MAX7314(void);
void read_button_MAX7314(uint8_t *port_data);
void read_encoder_MAX7314(uint8_t *port_data);


int main (void)
{
	sysclk_init();				//initialize system clock
	WDT->WDT_MR = WDT_MR_WDDIS; //disable watchdog timer

	board_init();				//board init (currently empty)
	
	led_init_colors();
	SPI_led_init();
	i2c_init();
	init_IO_int();
	timers_init();
	ADC_init();
	Encoder_init();				//initialize encoders
	all_displays_init();
	init_sequencer_controls();

	leds_update_display();
	update_timers(bpm);
	config_MAX7314();
	read_button_MAX7314(button_port_data);

	//notes_default();
 	
	note_display(48);
 	

 	bpm_display(bpm);
 	res_display(res_to_int(resolution));
 	page_display(curr_page);
 	pattern_display(curr_pattern);
 	output_display_1(curr_pattern_ch[0], curr_pattern_ch[1]);
 	output_display_2(curr_pattern_ch[2], curr_pattern_ch[3]);

	pattern_mem_read(0x00490000);

	while (1)
	{

	}
}

 void PIOB_Handler(){

	 uint32_t status = REG_PIOB_ISR;	//read PIOB interrupt status & clear interrupt flags
 
	 //check if Io expander interrupt was driven
	 if (status & PIO_ISR_P10){
		read_button_MAX7314(temp_data);

		if  ( !((temp_data[0] == 255) && (temp_data[1] == 255)) ){
			button_port_data[0] = temp_data[0];
			button_port_data[1] = temp_data[1];

			button_count++;
			if (button_count >= 2){
				led_toggle(button_port_data[0], button_port_data[1]);
				button_count = 0;
			}
		}
		
	 }

	 else if (status & PIO_ISR_P11) {
		read_encoder_MAX7314(temp_data);
		
		if  ( !((temp_data[0] == 255) && (temp_data[1] == 255)) ){
			encoder_port_data[0] = temp_data[0];
			encoder_port_data[1] = temp_data[1];

			encoder_count++;
			if (encoder_count >= 2){
				aux_toggle(encoder_port_data[0], encoder_port_data[1]);
				encoder_count = 0;
			}
		}
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


	uint8_t port_data_write_encoders[] = {MAX7314_portConfigRegisterLow, 0xFF, 0xFF};

	/* Configure the Chip Ports as Inputs */
	packet_tx.chip        = 0b0100000;
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) port_data_write_encoders;
	packet_tx.length      = 3;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);

	/* Configure the Chip Config Register */
	packet_tx.chip        = 0b0100100;
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) config_data;
	packet_tx.length      = 2;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);


	uint8_t port_data_write_buttons[] = {MAX7314_portConfigRegisterLow, 0xFF, 0xFF};

	/* Configure the Chip Ports as Inputs */
	packet_tx.chip        = 0b0100100;
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) port_data_write_buttons;
	packet_tx.length      = 3;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);
 }

 void read_encoder_MAX7314(uint8_t *data){
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

void read_button_MAX7314(uint8_t *data){
	/* Data Packets for tx/rx */
	twi_packet_t packet_rx, packet_tx;
	uint8_t port_addr[] = {MAX7314_inputPortLow};

	  
	/* Write the command byte address to be the Low byte of the Input Port */
	packet_tx.chip        = 0b0100100;
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) port_addr;
	packet_tx.length      = 1;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);


	/* Read Data from the Low and High Input Ports */
	packet_rx.chip        = 0b0100100;
	packet_rx.addr_length = 0;
	packet_rx.buffer      = data;
	packet_rx.length      = 2;
	twi_master_read(BOARD_BASE_TWI, &packet_rx);


}

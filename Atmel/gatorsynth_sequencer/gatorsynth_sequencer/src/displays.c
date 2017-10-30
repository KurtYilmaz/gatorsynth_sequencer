/*
 * displays.c
 *
 * Created: 10/29/2017 9:22:17 PM
 *  Author: Kyle
 */ 
 #include <asf.h>
 #include "i2c.h"
 #include <twi.h>

 #define SSD1306_LCDWIDTH      128
 #define SSD1306_LCDHEIGHT      64
 #define SSD1306_SETCONTRAST   0x81
 #define SSD1306_DISPLAYALLON_RESUME 0xA4
 #define SSD1306_DISPLAYALLON 0xA5
 #define SSD1306_NORMALDISPLAY 0xA6
 #define SSD1306_INVERTDISPLAY 0xA7
 #define SSD1306_DISPLAYOFF 0xAE
 #define SSD1306_DISPLAYON 0xAF
 #define SSD1306_SETDISPLAYOFFSET 0xD3
 #define SSD1306_SETCOMPINS 0xDA
 #define SSD1306_SETVCOMDETECT 0xDB
 #define SSD1306_SETDISPLAYCLOCKDIV 0xD5
 #define SSD1306_SETPRECHARGE 0xD9
 #define SSD1306_SETMULTIPLEX 0xA8
 #define SSD1306_SETLOWCOLUMN 0x00
 #define SSD1306_SETHIGHCOLUMN 0x10
 #define SSD1306_SETSTARTLINE 0x40
 #define SSD1306_MEMORYMODE 0x20
 #define SSD1306_COLUMNADDR 0x21
 #define SSD1306_PAGEADDR   0x22
 #define SSD1306_COMSCANINC 0xC0
 #define SSD1306_COMSCANDEC 0xC8
 #define SSD1306_SEGREMAP 0xA0
 #define SSD1306_CHARGEPUMP 0x8D
 #define SSD1306_EXTERNALVCC 0x1
 #define SSD1306_SWITCHCAPVCC 0x2

 #define control 0x00

 #define BOARD_ID_TWI    ID_TWI0
 #define BOARD_BASE_TWI  TWI0


 //Used to sent command to the display during operation
 void display_command(uint8_t control_data){
	 twi_packet_t packet_tx;
	 uint8_t command_data[] = {control, control_data};

	 packet_tx.chip        = 0b0111100;		// 0x78 is slave address for display
	 packet_tx.addr_length = 0;
	 packet_tx.buffer      = (uint8_t *) command_data;
	 packet_tx.length      = 2;
	 twi_master_write(BOARD_BASE_TWI, &packet_tx);

 }

 //used to send data to the display during operation
 void display_data(uint8_t data){
	twi_packet_t packet_tx;
	uint8_t command_data[] = {0x40, data};

	packet_tx.chip        = 0b0111100;		// 0x78 is slave address for display
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) command_data;
	packet_tx.length      = 2;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);
 }

 void display_reset(){
	//configure register used for display reset if not already done
	REG_PIOA_PER |= PIO_PER_P31; //enable PIO controller on PA31
	REG_PIOA_OER |= PIO_PER_P31; //enable output on pin PA31

	REG_PIOA_SODR |= PIO_PER_P31; //set high
	delay_ms(1);
	REG_PIOA_CODR |= PIO_PER_P31; //set low
	delay_ms(10);
	REG_PIOA_SODR |= PIO_PER_P31; //set high and hold for normaloperation
 }

 void display_init(){

	delay_ms(40);

	//reset display to begin
	display_reset();	

	//init settings for OLED
	display_command(SSD1306_DISPLAYOFF);

	display_command(SSD1306_SETDISPLAYCLOCKDIV);
	display_command(0x80);

	display_command(SSD1306_SETMULTIPLEX);
	display_command(0x3F);

	//set no display offset
	display_command(SSD1306_SETDISPLAYOFFSET);
	display_command(0x00);

	//start at line 0
	display_command(SSD1306_SETSTARTLINE);

	display_command(SSD1306_CHARGEPUMP);
	display_command(0x14);	//internal VCC from charge pump

	//set segment remap
	display_command(0xA1);

	//set com scan direction
	display_command(SSD1306_COMSCANDEC);

	display_command(SSD1306_SETCOMPINS);
	display_command(0x12);

	display_command(SSD1306_SETCONTRAST);
	display_command(0xCF);

	display_command(SSD1306_SETPRECHARGE);
	display_command(0xF1);

	display_command(SSD1306_SETVCOMDETECT);
	display_command(0x40);

	display_command(SSD1306_NORMALDISPLAY);
	display_command(SSD1306_DISPLAYALLON);

	display_command(SSD1306_DISPLAYON);

 }

//  void display_test(){
// 
// 	display_command(SSD1306_COLUMNADDR);
// 	display_command(0x00);
// 	display_command(SSD1306_LCDWIDTH-1);
// 
// 	display_command(SSD1306_PAGEADDR);
// 	display_command(0x00);
// 	display_command((SSD1306_LCDHEIGHT/8)-1);
// 
// 	twi_packet_t packet_tx;
// 	uint8_t command_data = PROGMEM;
// 
// 	packet_tx.chip        = 0b0111100;		// 0x78 is slave address for display
// 	packet_tx.addr_length = 0;
// 	packet_tx.buffer      = (uint8_t *) command_data;
// 	packet_tx.length      = 1025;
// 	twi_master_write(BOARD_BASE_TWI, &packet_tx);
//  }


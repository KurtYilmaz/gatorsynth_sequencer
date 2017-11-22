/*
 * displays.c
 *
 * Created: 10/29/2017 9:22:17 PM
 *  Author: Kyle
 */ 
 #include <asf.h>
 #include "i2c.h"
 #include "fonts.h"
 #include <twi.h>
 #include <stdlib.h>

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
 #define SSD1306_ALTCOM 0x12
 #define SSD1306_LEFTRIGHTREMAP_ALTCOM 0x32
 #define SSD1306_SETVCOMDETECT 0xDB
 #define SSD1306_SETDISPLAYCLOCKDIV 0xD5
 #define SSD1306_SETPRECHARGE 0xD9
 #define SSD1306_SETMULTIPLEX 0xA8
 #define SSD1306_SETLOWCOLUMN 0x00
 #define SSD1306_SETHIGHCOLUMN 0x10
 #define SSD1306_SETSTARTLINE 0x40
 #define SSD1306_MEMORYMODE 0x20
 #define SSD1306_VERTADDR 0x01
 #define SSD1306_PAGEADDR   0x02
 #define SSD1306_COMSCANINC 0xC0
 #define SSD1306_COMSCANDEC 0xC8
 #define SSD1306_SEGREMAP 0xA0
 #define SSD1306_CHARGEPUMP 0x8D
 #define SSD1306_EXTERNALVCC 0x1
 #define SSD1306_SWITCHCAPVCC 0x2
 #define SSD1306_SCROLLRIGHT 0x26
 #define SSD1306_DISPLAY32COLS 0x5F
 #define SSD1306_EDITPAGEADDR 0x22


 #define control_command 0x00
 #define control_data 0x40
 #define control_cont_command 0x80
 #define control_cont_data 0xC0

 #define BOARD_ID_TWI    ID_TWI0
 #define BOARD_BASE_TWI  TWI0

#define disp_sel_0 PIO_PER_P28
#define disp_sel_1 PIO_PER_P29
#define disp_sel_2 PIO_PER_P30 
#define disp_reset PIO_PER_P31


bool inverted[7] = {0,0,0,0,0,0,0};
uint16_t disp_ptr_location[7] = {0,0,0,0,0,0,0};
uint8_t curr_display = 7;

 void display_select(uint8_t d_id) {
	if(curr_display != d_id) {
		switch (d_id) {
			case 0:
				REG_PIOA_CODR |= disp_sel_0;
				REG_PIOA_CODR |= disp_sel_1;
				REG_PIOA_CODR |= disp_sel_2;
				curr_display = 0;
				break;
			case 1:
				REG_PIOA_SODR |= disp_sel_0;
				REG_PIOA_CODR |= disp_sel_1;
				REG_PIOA_CODR |= disp_sel_2;
				curr_display = 1;
				break;
			case 2:
				REG_PIOA_CODR |= disp_sel_0;
				REG_PIOA_SODR |= disp_sel_1;
				REG_PIOA_CODR |= disp_sel_2;
				curr_display = 2;
				break;
			case 3:
				REG_PIOA_SODR |= disp_sel_0;
				REG_PIOA_SODR |= disp_sel_1;
				REG_PIOA_CODR |= disp_sel_2;
				curr_display = 3;
				break;
			case 4:
				REG_PIOA_CODR |= disp_sel_0;
				REG_PIOA_CODR |= disp_sel_1;
				REG_PIOA_SODR |= disp_sel_2;
				curr_display = 4;
				break;
			case 5:
				REG_PIOA_SODR |= disp_sel_0;
				REG_PIOA_CODR |= disp_sel_1;
				REG_PIOA_SODR |= disp_sel_2;
				curr_display = 5;
				break;
			case 6:
				REG_PIOA_CODR |= disp_sel_0;
				REG_PIOA_SODR |= disp_sel_1;
				REG_PIOA_SODR |= disp_sel_2;
				curr_display = 6;
				break;
			default:
				REG_PIOA_SODR |= disp_sel_0;
				REG_PIOA_SODR |= disp_sel_1;
				REG_PIOA_SODR |= disp_sel_2;
				curr_display = 7;
				break;
		}
	}
 }

 //Used to send command to the display during operation
 void display_command(uint8_t data, uint8_t d_id){
	 display_select(d_id);

	 twi_packet_t packet_tx;
	 uint8_t command_buffer[] = {control_command, data};

	 packet_tx.chip        = 0x3C;		// 0x3C is slave address for display
	 packet_tx.addr_length = 0;
	 packet_tx.buffer      = (uint8_t *) command_buffer;
	 packet_tx.length      = 2;
	 twi_master_write(BOARD_BASE_TWI, &packet_tx);

 }

 //used to send data to the display during operation
 void display_data(uint8_t data, uint8_t d_id){
	display_select(d_id);
	
	twi_packet_t packet_tx;
	uint8_t data_buffer[] = {control_data, data};
	packet_tx.chip        = 0x3C;		// 0x3C is slave address for display
	packet_tx.addr_length = 0;
	packet_tx.buffer      = (uint8_t *) data_buffer;
	packet_tx.length      = 2;
	twi_master_write(BOARD_BASE_TWI, &packet_tx);
	disp_ptr_location[d_id] += 8;
	if(disp_ptr_location[d_id] >= 4096) {
		disp_ptr_location[d_id] = 0;
	}
 }

 void display_reset(uint8_t d_id){
	display_select(d_id);
	REG_PIOA_SODR |= disp_reset; //set high
	delay_ms(1);
	REG_PIOA_CODR |= disp_reset; //set low
	delay_ms(10);
	REG_PIOA_SODR |= disp_reset; //set high and hold for normal operation
 }

 void display_init(uint8_t d_id) {
	// Reset display to begin
	display_reset(d_id);

	// Init settings for OLED
	display_command(SSD1306_DISPLAYOFF, d_id);

	display_command(SSD1306_SETDISPLAYCLOCKDIV, d_id);
	display_command(0x80, d_id);

	// Set no display offset
	display_command(SSD1306_SETDISPLAYOFFSET, d_id);
	display_command(0x00, d_id);

	// Start at line 0
	display_command(SSD1306_SETSTARTLINE, d_id);

	display_command(SSD1306_CHARGEPUMP, d_id);
	display_command(0x14, d_id);	//internal VCC from charge pump

	// Set segment remap
	display_command(0xA0, d_id);

	display_command(SSD1306_SETCOMPINS, d_id);
	display_command(0x02, d_id);

	display_command(SSD1306_SETCONTRAST, d_id);
	display_command(0xCF, d_id);

	display_command(SSD1306_SETPRECHARGE, d_id);
	display_command(0xF1, d_id);

	display_command(SSD1306_SETVCOMDETECT, d_id);
	display_command(0x40, d_id);

	display_command(SSD1306_NORMALDISPLAY, d_id);
	display_command(SSD1306_DISPLAYON, d_id);
	display_command(SSD1306_MEMORYMODE, d_id);
	display_command(SSD1306_VERTADDR, d_id);

	// Adjusting for 32 height display
	display_command(SSD1306_EDITPAGEADDR, d_id);
	display_command(0, d_id);
	display_command(3, d_id);

	display_command(SSD1306_SETMULTIPLEX, d_id);
	display_command(31, d_id);
 }

 void all_displays_init(void) {

	// Configure registers used for display mux lines
	REG_PIOA_PER |= disp_sel_0; //enable PIO controller on PA28
	REG_PIOA_OER |= disp_sel_0; //enable output on pin PA28
	REG_PIOA_PER |= disp_sel_1; //enable PIO controller on PA29
	REG_PIOA_OER |= disp_sel_1; //enable output on pin PA29
	REG_PIOA_PER |= disp_sel_2; //enable PIO controller on PA30
	REG_PIOA_OER |= disp_sel_2; //enable output on pin PA30

	// Configure register used for display reset
	REG_PIOA_PER |= disp_reset; //enable PIO controller on PA31
	REG_PIOA_OER |= disp_reset; //enable output on pin PA31

// 	display_init(0);
//   display_init(1);
 	display_init(2);
// 	display_init(3);
// 	display_init(4);
// 	display_init(5);
// 	display_init(6);
 }

 void toggle_inversion(uint8_t d_id) {
	if(inverted == 0) {
		display_command(SSD1306_INVERTDISPLAY, d_id);
		inverted[d_id] = 1;
	}
	else {
		display_command(SSD1306_NORMALDISPLAY, d_id);
		inverted[d_id] = 0;
	}
 }

 void finish_display(uint8_t d_id) {
	while(disp_ptr_location[d_id] > 0 && disp_ptr_location[d_id] <= 4096) {
		display_data(0, d_id);
	}
 }

 void clear_display(uint8_t d_id) {
	finish_display(d_id);
	finish_display(d_id);
 }

  // Displays 1 byte of space and 3 bytes of character at a time
 void display_char(char input, uint8_t font_size, uint8_t d_id) {
	  // Lets us customize our space width, input parameter can be added if needed
	if(input == ' ') {
		int i;
		for(i = 8; i > 0; i--) {
			display_data(0, d_id);
		}
	  }
	  // Uses font to display characters
	else {
		uint16_t font_index = 0;
		uint8_t byte_1;
		uint8_t byte_2;
		uint8_t byte_3;
		if(font_size == 28) {
			uint16_t width = getWidth_28();
			while (font_index < width) {
				//Sharps and flats are elevated, rest of characters are not
				if(input != '#' && input != 'b') {
					display_data(0, d_id);
				}
				byte_1 = getByte_28(input, font_index);
				byte_2 = getByte_28(input, font_index + width);
				byte_3 = getByte_28(input, font_index + 2*width);
				display_data(byte_1, d_id);
				display_data(byte_2, d_id);
				display_data(byte_3, d_id);
				//Sharps and flats are elevated, rest of characters are not
				if(input == '#' || input == 'b') {
					display_data(0, d_id);
				}
				font_index++;
			}
		}

		else if(font_size == 22) {
			uint16_t width = getWidth_22();
			while (font_index < width) {
				//Sharps and flats are elevated, rest of characters are not
				if(input != '#' && input != 'b') {
					display_data(0, d_id);
				}
				byte_1 = getByte_22(input, font_index);
				byte_2 = getByte_22(input, font_index + width);
				byte_3 = getByte_22(input, font_index + 2*width);
				display_data(byte_1, d_id);
				display_data(byte_2, d_id);
				display_data(byte_3, d_id);
				//Sharps and flats are elevated, rest of characters are not
				if(input == '#' || input == 'b') {
					display_data(0, d_id);
				}
				font_index++;
			}
		}

		// Defaults to 18 to reduce errors.
		else {
			uint16_t width = getWidth_18();
			while (font_index < width) {
				//Sharps and flats are elevated, rest of characters are not
				if(input != '#' && input != 'b') {
					display_data(0, d_id);
				}
				display_data(0, d_id);
				byte_1 = getByte_18(input, font_index);
				byte_2 = getByte_18(input, font_index + width);
				display_data(byte_1, d_id);
				display_data(byte_2, d_id);
				//Sharps and flats are elevated, rest of characters are not
				if(input == '#' || input == 'b') {
					display_data(0, d_id);
				}
				font_index++;
			}
		}
	}
 }

 void display_number(uint32_t input, uint8_t font_size, uint8_t d_id) {
	int buffersize = 0;
    char buffer[8];

	if(input==0) {
		display_char('0', font_size, d_id);
		display_char(' ', font_size, d_id);
		return;
	}

	//Determining needed size of buffer
    if (input > 999999) {           
        buffersize = 7;
    }
    else if (input > 99999) {
        buffersize = 6;
    }
    else if (input > 9999) {
        buffersize = 5;
    }
    else if (input > 999) {
        buffersize = 4;
    }
    else if(input > 99) {
        buffersize = 3;
    }
    else if(input > 9) {
        buffersize = 2;
    }
    else {
        buffersize = 1;
    }

    // Grabs each digit at a time from integer and stores in array
	// Does this to reverse the order it's output in
    int i = buffersize - 1;
    uint32_t temp;
    while(input > 0) {
        temp = input;
        buffer[i] = (char)(input%10 + '0');
        input = temp;
        input = input/10;
        i--;
    }
	while(i > 0) {
		buffer[i] = '1';
	}

    i = 0;
    while(i < buffersize) {
		display_char(buffer[i], font_size, d_id);
		display_char(' ', font_size, d_id);
		i++;
	}
 }

// Display 0
void note_display(uint16_t note) {
	while(disp_ptr_location[0] < 1280) {
		display_data(0, 0);
	}
	
	display_char('A', 28, 0);
	display_char(' ', 28, 0);
	display_char('b', 18, 0);
	display_char(' ', 28, 0);
	display_char(' ', 28, 0);
	display_char('3', 18, 0);
	finish_display(0);
}

// Display 1
void bpm_display(uint16_t bpm) {
	display_char('B', 28, 1);
	display_char(' ', 28, 1);
	display_char('P', 28, 1);
	display_char(' ', 28, 1);
	display_char('M', 28, 1);
	display_char(' ', 28, 1);
	display_char(':', 28, 1);
	display_char(' ', 28, 1);
	display_number(bpm, 28, 1);
	finish_display(1);
}

// Display 2
void res_display(uint8_t res) {
	display_char('R', 22, 2);
	display_char(' ', 28, 2);
	display_char('E', 22, 2);
	display_char(' ', 28, 2);
	display_char('S', 22, 2);
	display_char(' ', 28, 2);
	display_char(':', 22, 2);
	display_char(' ', 28, 2);
	display_char('1', 22, 2);
	display_char(' ', 28, 2);
	display_char('/', 22, 2); 
	display_char(' ', 28, 2);
	if(res == 6) {
		display_number(4, 22, 2);
		display_char('t', 22, 2);
	}
	else if(res == 12) {
		display_number(8, 22, 2);
		display_char('t', 22, 2);
	}
	else if(res == 24) {
		display_number(16, 22, 2);
		display_char('t', 22, 2);
	}
	else {
		display_number(res, 22, 2);
	}
	finish_display(2);  
}

// Display 3
void page_display(uint8_t page) {
	display_char('P', 28, 3);
	display_char('A', 28, 3);
	display_char('G', 28, 3);
	display_char('E', 28, 3);
	display_char(':', 28, 3);
	display_number(page, 28, 3);
	finish_display(3);
}

// Display 4
void pattern_display(uint8_t pattern) {
	display_char('P', 18, 4);
	display_char('T', 18, 4);
	display_char('R', 18, 4);
	display_char('N', 18, 4);
	display_char(':', 18, 4);
	display_number(pattern, 18, 4);
	finish_display(4);
}

// Display 5
void output_display_1(uint8_t out1, uint8_t out2) {
	display_char('0', 22, 5);
	display_char(' ', 22, 5);
	display_char('1', 18, 5);
	display_char(':', 18, 5);
	display_number(out1, 18, 5);

	while(disp_ptr_location[5] < 1920) {
		display_data(0, 5);
	}

	display_char('0', 22, 5);
	display_char(' ', 22, 5);
	display_char('2', 18, 5);
	display_char(':', 18, 5);
	display_number(out2, 18, 5);
	
	finish_display(5);
}

// Display 6
void output_display_2(uint8_t out3, uint8_t out4) {
	display_char('0', 22, 6);
	display_char(' ', 22, 6);
	display_char('3', 18, 6);
	display_char(':', 18, 6);
	display_number(out3, 18, 6);

	while(disp_ptr_location[6] < 1920) {
		display_data(0, 6);
	}

	display_char('0', 22, 6);
	display_char(' ', 22, 6);
	display_char('4', 18, 6);
	display_char(':', 18, 6);
	display_number(out4, 18, 6);
	
	finish_display(6);
}
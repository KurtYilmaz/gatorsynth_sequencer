/*
 * displays.h
 *
 * Created: 10/29/2017 9:22:33 PM
 *  Author: Kyle
 */ 


#ifndef DISPLAYS_H_
#define DISPLAYS_H_

#include <stdbool.h>

void display_select(uint8_t d_id);
void display_command(uint8_t control_data, uint8_t d_id);
void display_data(uint8_t data, uint8_t d_id);
void display_reset();
void display_init(uint8_t d_id);
void all_displays_init(void);
void toggle_inversion(uint8_t d_id);
void clr_pattern_display(uint8_t pattern, bool yes);
//void note_display(uint16_t note);

void finish_display(uint8_t d_id);
void clear_display(uint8_t d_id);
void display_char(char input, uint8_t font_size, uint8_t d_id);
void display_char_inverted(char input, uint8_t font_size, uint8_t d_id);
void display_number(uint16_t input, uint8_t font_size, uint8_t d_id);

// Display 0
void note_display(uint16_t note);

// Display 1
void bpm_display(uint16_t bpm);

// Display 2
void res_display(uint8_t res);

// Display 3
void page_display(uint8_t page);
void loop_display(uint8_t page_loop);

// Display 4
void pattern_display(uint8_t pattern);

// Display 5
void output_display_1(uint8_t out1, uint8_t out2);

// Display 6
void output_display_2(uint8_t out3, uint8_t out4);

#endif /* DISPLAYS_H_ */
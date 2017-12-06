/*
 * sequencer.h
 *
 * Created: 9/22/2017 12:15:53 AM
 *  Author: Kurt
 */ 


#ifndef SEQUENCER_H_
#define SEQUENCER_H_
#include <stdbool.h>

#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2
#define CHANNEL_4 3

 uint8_t A_seq;
 uint8_t B_seq;

bool clr_yes;
bool cursor_follow;
bool page_disable;
uint8_t save;
uint8_t pause;
uint8_t pause_count;
uint16_t bpm;
uint8_t bpm_adjust;
uint8_t page_or_loop;
uint8_t pattern_clr;
uint8_t patterns_out[4];
// uint8_t button_feature[8];
// uint8_t aux_feature[8];


uint8_t res_to_int(uint8_t res);
void res_inc(void);
void res_dec(void);
void bpm_inc(void);
void bpm_dec(void);
void bpm_toggle(void);
void display_page_inc(void);
void display_page_dec(void);
void pattern_inc(void);
void pattern_dec(void);
void pattern_up(uint8_t channel);
void pattern_down(uint8_t channel);
void page_loop_inc(void);
void page_loop_dec(void);
void cursor_follow_toggle(void);
void pattern_octave_up(void);
void pattern_octave_down(void);
void synch_pages(void);

void aux_toggle(uint8_t button_row, uint8_t aux_encoders);

void control_direction(uint32_t A, uint32_t B, uint8_t aux_control);
void init_sequencer_controls(void);


#endif /* SEQUENCER_H_ */
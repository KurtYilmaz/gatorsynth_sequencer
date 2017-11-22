/*
 * sequencer.h
 *
 * Created: 9/22/2017 12:15:53 AM
 *  Author: Kurt
 */ 


#ifndef SEQUENCER_H_
#define SEQUENCER_H_


uint16_t bpm;
uint8_t patterns_out[4];


#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2
#define CHANNEL_4 3

uint8_t res_to_int(uint8_t res);
void res_inc(void);
void res_dec(void);
void bpm_inc(void);
void bpm_dec(void);
void display_page_inc(void);
void display_page_dec(void);
void pattern_inc(void);
void pattern_dec(void);
void pattern_up(uint8_t channel);
void pattern_down(uint8_t channel);
void page_loop_inc(void);
void page_loop_dec(void);

void control_direction(uint32_t A, uint32_t B, uint8_t aux_control);
void init_sequencer_controls(void);


#endif /* SEQUENCER_H_ */
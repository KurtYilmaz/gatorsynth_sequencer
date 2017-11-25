/*
 * timers.h
 *
 * Created: 9/24/2017 1:27:52 AM
 *  Author: Kurt
 */ 

 #include <asf.h>
 #include <stdbool.h>
 #include "leds.h"

#ifndef TIMERS_H_
#define TIMERS_H_

void timers_init(void);
void update_timers(int bpm);

//determine note actually being sent to the synth
uint16_t overflow_count;
uint16_t note_overflow_count;
uint16_t refresh_overflow_count;
uint16_t note_length;
uint8_t page_loop;
uint8_t curr_step;
uint8_t curr_page;
uint8_t curr_pattern;

//channel variables
uint8_t curr_page_ch[4];
uint8_t curr_pattern_ch[4];
uint8_t page_loop_ch[4];
uint8_t channel_mute[4];

//defines page displayed on buttons instead of what's actually playing
uint8_t display_page;

//Flags for display refreshes
// bool note_change;
// bool bpm_change;
// bool res_change;
// bool page_change;
// bool pattern_change;


//auxiliary variables
int resolution;




#endif /* TIMERS_H_ */
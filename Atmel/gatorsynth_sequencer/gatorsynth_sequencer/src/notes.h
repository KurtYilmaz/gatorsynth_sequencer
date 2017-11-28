/*
 * notes.h
 *
 * Created: 10/13/2017 9:00:42 PM
 *  Author: Kyle
 */ 


#ifndef NOTES_H_
#define NOTES_H_

#include <stdbool.h>

int patterns_loop[4];
int patterns[16][16][16][2];

float notes_get(uint8_t curr_step, uint8_t channel);
int notes_display_get(uint8_t display_page, uint8_t curr_step);
void notes_status_set(uint8_t display_page, int leds_status[]);
int notes_status_get(uint8_t curr_step, uint8_t channel);
void notes_clear(uint8_t curr_pattern);
void notes_default(void);
void notes_inc(uint8_t step);
void notes_dec(uint8_t step);

#endif /* NOTES_H_ */
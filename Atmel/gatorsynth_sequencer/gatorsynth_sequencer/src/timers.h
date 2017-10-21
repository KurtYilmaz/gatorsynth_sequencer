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

uint16_t overflow_count;
uint8_t curr_step;


#endif /* TIMERS_H_ */
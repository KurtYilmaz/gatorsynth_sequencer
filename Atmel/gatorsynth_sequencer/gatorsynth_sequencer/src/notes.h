/*
 * notes.h
 *
 * Created: 10/13/2017 9:00:42 PM
 *  Author: Kyle
 */ 


#ifndef NOTES_H_
#define NOTES_H_

#include <stdbool.h>


float notes_get(uint8_t curr_step);
void notes_inc(uint8_t step);
void notes_dec(uint8_t step);

#endif /* NOTES_H_ */
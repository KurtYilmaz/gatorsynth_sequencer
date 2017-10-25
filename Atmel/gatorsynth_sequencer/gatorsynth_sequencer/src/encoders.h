/*
 * encoders.h
 *
 * Created: 10/7/2017 9:43:30 PM
 *  Author: Kyle
 */ 


#ifndef ENCODERS_H_
#define ENCODERS_H_

uint8_t A_seq;
uint8_t B_seq;

void Encoder_init(void);
int encoder_direction(uint32_t A, uint32_t B);


#endif /* ENCODERS_H_ */
/*
 * sequencer.h
 *
 * Created: 9/22/2017 12:15:53 AM
 *  Author: Kurt
 */ 


#ifndef SEQUENCER_H_
#define SEQUENCER_H_


uint16_t bpm;

void bpm_inc();
void bpm_dec();

void bpm_direction(uint32_t A, uint32_t B);
void init_sequencer_controls(void);


#endif /* SEQUENCER_H_ */
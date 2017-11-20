/*
 * dac.h
 *
 * Created: 10/12/2017 6:53:58 PM
 *  Author: Kyle
 */ 


#ifndef DAC_H_
#define DAC_H_

void DAC_write_cv(float voltage, uint8_t channel);
void DAC_write_gate_on(uint8_t channel);
void DAC_write_gate_off(uint8_t channel);


#endif /* DAC_H_ */
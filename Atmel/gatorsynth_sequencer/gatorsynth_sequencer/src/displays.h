/*
 * displays.h
 *
 * Created: 10/29/2017 9:22:33 PM
 *  Author: Kyle
 */ 


#ifndef DISPLAYS_H_
#define DISPLAYS_H_

void display_command(uint8_t control_data);
void display_data(uint8_t data);
void display_reset(void);
void display_init(void);

void display_test();



#endif /* DISPLAYS_H_ */
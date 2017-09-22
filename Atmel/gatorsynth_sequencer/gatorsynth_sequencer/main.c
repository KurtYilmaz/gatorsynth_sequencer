/*
 * gatorsynth_sequencer.c
 *
 * Created: 9/22/2017 12:13:23 AM
 * Author : Kurt
 */ 


#include "sam.h"

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

	REG_PIOA_PER |= PIO_PER_P11; //enable PIO controller on PA11
	REG_PIOA_OER |= PIO_PER_P11; //enable output on pin PA11	

    /* Replace with your application code */
    while (1) 
    {

		REG_PIOA_SODR |= PIO_PER_P11; //set output high on pin PA11

		REG_PIOA_CODR |= PIO_PER_P11; //set output low on pin PA11

    }
}

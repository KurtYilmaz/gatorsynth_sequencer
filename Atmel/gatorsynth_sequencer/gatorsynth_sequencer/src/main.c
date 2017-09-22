/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	sysclk_init();
	board_init();
	WDT->WDT_MR = WDT_MR_WDDIS;

	REG_PIOA_PER |= PIO_PER_P11; //enable PIO controller on PA11
	REG_PIOA_OER |= PIO_PER_P11; //enable output on pin PA11

	/* Replace with your application code */
	while (1)
	{

		REG_PIOA_SODR |= PIO_PER_P11; //set output high on pin PA11
		delay_ms(500);

		REG_PIOA_CODR |= PIO_PER_P11; //set output low on pin PA11
		delay_ms(500);
	}
}

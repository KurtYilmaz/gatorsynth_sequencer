/*
 * sequencer.c
 *
 * Created: 9/22/2017 12:15:25 AM
 *  Author: Kurt
 */ 

 #include <asf.h>
 #include <board.h>
 #include <conf_board.h>
 #include <stdbool.h>

 #include "timers.h"
 #include "sequencer.h"
 #include "displays.h"
 #include "notes.h"
 #include "dac.h"


 void control_direction(uint32_t A, uint32_t B, uint8_t aux_control){

	//read Encoder input A
	bool A_in = REG_PIOA_PDSR & A;
	//read Encoder input B
	bool B_in = REG_PIOA_PDSR & B;
	
	A_seq = A_seq << 1;
	A_seq |= A_in;
	
	B_seq = B_seq << 1;
	B_seq |= B_in;
	
	A_seq &= 0b00001111;
	B_seq &= 0b00001111;


	//return true if turned right
	if ((A_seq == 0b00001001) && (B_seq == 0b00000011)){
		if (aux_control == 0){
			bpm_inc();
			update_timers(bpm);
			bpm_display(bpm);
		}
		else if (aux_control == 1){
			res_inc();
			update_timers(bpm);
			res_display(res_to_int(resolution));
		}
		else if (aux_control == 2){
			if (page_or_loop == 0){
				display_page_inc();
				page_display(display_page);
			}
			else if (page_or_loop == 1){
				page_loop_inc();
				loop_display(page_loop);
			}
		}
		else if (aux_control == 3){
			pattern_inc();
			pattern_display(curr_pattern);
		}
		else if (aux_control == 4){
			pattern_up(CHANNEL_1);
			output_display_1(curr_pattern_ch[0], curr_pattern_ch[1]);
		}
		else if (aux_control == 5){
			pattern_up(CHANNEL_2);
			output_display_1(curr_pattern_ch[0], curr_pattern_ch[1]);
		}
		else if (aux_control == 6){
			pattern_up(CHANNEL_3);
			output_display_2(curr_pattern_ch[2], curr_pattern_ch[3]);
		}
		else if (aux_control == 7){
			pattern_up(CHANNEL_4);
			output_display_2(curr_pattern_ch[2], curr_pattern_ch[3]);
		}

	}

	else if ((A_seq == 0b00000011) && (B_seq == 0b00001001)){

		if (aux_control == 0){
			bpm_dec();
			update_timers(bpm);
			bpm_display(bpm);
		}
		else if (aux_control == 1){
			res_dec();
			update_timers(bpm);
			res_display(res_to_int(resolution));
		}
		else if (aux_control == 2){
			if (page_or_loop == 0){
				display_page_dec();
				page_display(display_page);
			}
			else if (page_or_loop == 1){
				page_loop_dec();
				loop_display(page_loop);
			}
		}
		else if (aux_control == 3){
			pattern_dec();
			pattern_display(curr_pattern);
		}
		else if (aux_control == 4){
			pattern_down(CHANNEL_1);
			output_display_1(curr_pattern_ch[0], curr_pattern_ch[1]);
		}
		else if (aux_control == 5){
			pattern_down(CHANNEL_2);
			output_display_1(curr_pattern_ch[0], curr_pattern_ch[1]);
		}
		else if (aux_control == 6){
			pattern_down(CHANNEL_3);
			output_display_2(curr_pattern_ch[2], curr_pattern_ch[3]);
		}
		else if (aux_control == 7){
			pattern_down(CHANNEL_4);
			output_display_2(curr_pattern_ch[2], curr_pattern_ch[3]);
		}
	}


}

uint8_t res_to_int(uint8_t res){
	if (res == 0){
		return 1;
	}
	else if (res == 1){
		return 2;
	}
	else if (res == 2){
		return 4;
	}
	else if (res == 3){
		return 6;
	}
	else if (res == 4){
		return 8;
	}
	else if (res == 5){
		return 12;
	}
	else if (res == 6){
		return 16;
	}
	else if (res == 7){
		return 24;
	}
	else if (res == 8){
		return 32;
	}

	//default
	return 1;
}

void res_inc(){
	if (resolution < 8){
		resolution++;
	}
}

void res_dec(){
	if (resolution > 0){
		resolution--;
	}
}

 void bpm_inc(){
	if ( (bpm + bpm_adjust) <= 999){
		bpm = bpm + bpm_adjust;
	}
}

 void bpm_dec(){
	if ( (bpm - bpm_adjust) >= 20){
		bpm = bpm - bpm_adjust;
	}
}

void bpm_toggle(){
	if (bpm_adjust == 1){
		bpm_adjust = 5;
	}
	else if (bpm_adjust == 5){
		bpm_adjust = 10;
	}
	else if (bpm_adjust == 10){
		bpm_adjust = 20;
	}
	else if (bpm_adjust == 20){
		bpm_adjust = 1;
	}
}

 void display_page_inc(){
	if (display_page < 15){
		display_page++;
	}
}

 void display_page_dec(){
	if (display_page > 0){
		display_page--;
	}
}

 void pattern_inc(){
	  if (curr_pattern < 15){
		  curr_pattern++;
	  }
 }

 void pattern_dec(){
	  if (curr_pattern > 0){
		  curr_pattern--;
	  }
 }

void pattern_up(uint8_t channel){
	if (curr_pattern_ch[channel] < 15){
		curr_pattern_ch[channel]++;
	}
}

void pattern_down(uint8_t channel){
	  if (curr_pattern_ch[channel] > 0){
		  curr_pattern_ch[channel]--;
	  }
}

void page_loop_inc(){
	if (page_loop < 15){
		page_loop++;
	}
}

void page_loop_dec(){
	if (page_loop > 0){
		page_loop--;
	}
}

void aux_toggle(uint8_t button_row, uint8_t aux_encoders){

	switch(aux_encoders) {
		case 254 :
			//change bpm inc/dec scale
			bpm_toggle();
			break;
		case 253 :
			//toggle resolution or scale?
			break;
		case 251 :
			//toggle between page & loop variables
			page_or_loop = abs(page_or_loop - 1);
			if (page_or_loop == 0){
				page_display(display_page);
			}
			else if (page_or_loop == 1){
				loop_display(page_loop);
			}
			break;
		case 247 :
			if (pattern_clr == 0){
				pattern_clr = 1;					//set pattern clear
				REG_TC0_CCR1 |= TC_CCR_CLKEN | TC_CCR_SWTRG;		//start 2 sec timer
				clr_pattern_display(curr_pattern);	//output clear message to display
			}
			else if (pattern_clr == 1){
				note_overflow_count = 0;			//reset timer counter
				pattern_clr = 0;					//reset clear variable
				REG_TC0_CCR1 |= TC_CCR_CLKDIS;		//disable timer counter
				notes_clear(curr_pattern);			//clear the current pattern
				pattern_display(curr_pattern);		//return display to default
			}
			break;
		case 239 :
			channel_mute[CHANNEL_1] = abs(channel_mute[CHANNEL_1] - 1);
			DAC_write_gate_off(CHANNEL_1);
			break;
		case 223 :
			channel_mute[CHANNEL_2] = abs(channel_mute[CHANNEL_2] - 1);
			DAC_write_gate_off(CHANNEL_2);
			break;
		case 191 :
			channel_mute[CHANNEL_3] = abs(channel_mute[CHANNEL_3] - 1);
			DAC_write_gate_off(CHANNEL_3);
			break;
		case 127 :
			channel_mute[CHANNEL_4] = abs(channel_mute[CHANNEL_4] - 1);
			DAC_write_gate_off(CHANNEL_4);
			break;
		default :
			break;
	}

	switch(button_row) {
		case 254 :
			
			break;
		case 253 :
			
			break;
		case 251 :
			
			break;
		case 247 :
			
			break;
		case 239 :
			
			break;
		case 223 :
		
			break;
		case 191 :
			
			break;
		case 127 :
			
			break;
		default :
			break;

}
}


 void init_sequencer_controls(){

	bpm = 120;
	bpm_adjust = 1;

	page_or_loop = 0;
	pattern_clr = 0;
	pause = 0;
	pause_count = 0;

	A_seq = 0;
	B_seq = 0;

	//enable clock for PIOA
	REG_PMC_PCER0 |= PMC_PCER0_PID11;

	/**************			CONFIGURE PAUSE/PLAY BUTTON				**************/
	//set up PA2 as pause/play interrupt pin
	REG_PIOA_PER |= PIO_PER_P2; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P2; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P2; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P2;	//enable pull-up resistor

	//set PA18 as pause/play LED output
	REG_PIOA_OER |= PIO_OER_P18;
	REG_PIOA_SODR |= PIO_SODR_P18; 

	/**************			CONFIGURE 8 STEP AUX ENCODERS			**************/

	//Set up PA0 as AUX ENC 0 INPUT A
	REG_PIOA_PER |= PIO_PER_P0; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P0; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P0; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P0;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P0; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P0;	//start debounce filter

	//Set up PA1 as AUX ENC 0 INPUT B
	REG_PIOA_PER |= PIO_PER_P1; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P1; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P1; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P1;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P1; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P1;	//start debounce filter



	//Set up PA6 as AUX ENC 1 INPUT A
	REG_PIOA_PER |= PIO_PER_P6; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P6; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P6; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P6;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P6; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P6;	//start debounce filter

	//Set up PA7 as AUX ENC 1 INPUT B
	REG_PIOA_PER |= PIO_PER_P7; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P7; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P7; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P7;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P7; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P7;	//start debounce filter


	
	//Set up PA8 as AUX ENC 2 INPUT A
	REG_PIOA_PER |= PIO_PER_P8; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P8; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P8; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P8;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P8; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P8;	//start debounce filter

	//Set up PA9 as AUX ENC 2 INPUT B
	REG_PIOA_PER |= PIO_PER_P9; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P9; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P9; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P9;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P9; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P9;	//start debounce filter



	//Set up PA16 as AUX ENC 3 INPUT A
	REG_PIOA_PER |= PIO_PER_P16; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P16; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P16; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P16;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P16; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P16;	//start debounce filter

	//Set up PA17 as AUX ENC 3 INPUT B
	REG_PIOA_PER |= PIO_PER_P17; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P17; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P17; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P17;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P17; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P17;	//start debounce filter



	//Set up PA20 as AUX ENC 4 INPUT A
	REG_PIOA_PER |= PIO_PER_P20; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P20; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P20; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P20;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P20; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P20;	//start debounce filter

	//Set up PA21 as AUX ENC 4 INPUT B
	REG_PIOA_PER |= PIO_PER_P21; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P21; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P21; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P21;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P21; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P21;	//start debounce filter



	//Set up PA22 as AUX ENC 5 INPUT A
	REG_PIOA_PER |= PIO_PER_P22; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P22; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P22; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P22;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P22; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P22;	//start debounce filter

	//Set up PA23 as AUX ENC 5 INPUT B
	REG_PIOA_PER |= PIO_PER_P23; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P23; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P23; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P23;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P23; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P23;	//start debounce filter



	//Set up PA24 as AUX ENC 6 INPUT A
	REG_PIOA_PER |= PIO_PER_P24; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P24; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P24; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P24;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P24; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P24;	//start debounce filter

	//Set up PA25 as AUX ENC 6 INPUT B
	REG_PIOA_PER |= PIO_PER_P25; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P25; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P25; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P25;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P25; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P25;	//start debounce filter



	//Set up PA26 as AUX ENC 7 INPUT A
	REG_PIOA_PER |= PIO_PER_P26; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P26; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P26; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P26;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P26; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P26;	//start debounce filter

	//Set up PA27 as AUX ENC 7 INPUT B
	REG_PIOA_PER |= PIO_PER_P27; //enable PIO controller
	REG_PIOA_ODR |= PIO_ODR_P27; //disable output
	REG_PIOA_PPDDR |= PIO_PPDDR_P27; //disable pull-down resistor
	REG_PIOA_PUER |= PIO_PUER_P27;	//enable pull-up resistor
	REG_PIOA_IFSCER |= PIO_IFSCER_P27; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P27;	//start debounce filter


	/**************			CONFIGURE AUX ENCODER INTERRUPTS			**************/

	uint32_t flag_clear = REG_PIOA_ISR;	//clear left over interrupt flags

	//configure interrupt for pause/play button
	REG_PIOA_IER |= PIO_IER_P2;			//enable input rising edge interrupt
	REG_PIOA_FELLSR |= PIO_FELLSR_P2;
	REG_PIOA_IFSCER |= PIO_IFSCER_P2; //turn on slow clock debounce
	REG_PIOA_IFER |= PIO_IFER_P2;	//start debounce filter

	//Enable interrupts for Aux Encoder 0
	REG_PIOA_IER |= PIO_IER_P0;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P0;
	REG_PIOA_IER |= PIO_IER_P1;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P1;

	//Enable interrupts for Aux Encoder 1
	REG_PIOA_IER |= PIO_IER_P6;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P6;
	REG_PIOA_IER |= PIO_IER_P7;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P7;

	//Enable interrupts for Aux Encoder 2
	REG_PIOA_IER |= PIO_IER_P8;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P8;
	REG_PIOA_IER |= PIO_IER_P9;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P9;

	//Enable interrupts for Aux Encoder 3
	REG_PIOA_IER |= PIO_IER_P16;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P16;
	REG_PIOA_IER |= PIO_IER_P17;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P17;

	//Enable interrupts for Aux Encoder 4
	REG_PIOA_IER |= PIO_IER_P20;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P20;
	REG_PIOA_IER |= PIO_IER_P21;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P21;

	//Enable interrupts for Aux Encoder 5
	REG_PIOA_IER |= PIO_IER_P22;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P22;
	REG_PIOA_IER |= PIO_IER_P23;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P23;

	//Enable interrupts for Aux Encoder 6
	REG_PIOA_IER |= PIO_IER_P24;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P24;
	REG_PIOA_IER |= PIO_IER_P25;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P25;

	//Enable interrupts for Aux Encoder 7
	REG_PIOA_IER |= PIO_IER_P26;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P26;
	REG_PIOA_IER |= PIO_IER_P27;			//enable input rising edge interrupt
	REG_PIOA_REHLSR |= PIO_REHLSR_P27;

	NVIC_EnableIRQ(PIOA_IRQn);			//enable PORT A interrupts


 }


 void PIOA_Handler(){

	 uint32_t status = REG_PIOA_ISR;	//read PIOC interrupt status & clear interrupt flags

	 //check if Aux Encoder 1 was rotated
	 if ( (status & PIO_ISR_P0) || (status & PIO_ISR_P1) ){
		 control_direction(PIO_ODSR_P0, PIO_ODSR_P1, 0);
	 }
	 
	 //check if Pause/Play button was pushed
	 else if ( (status & PIO_ISR_P2) ){
		pause_count++;
		if (pause_count == 2){
			if (pause == 0){
				REG_PIOA_CODR |= PIO_CODR_P18;
				pause = 1;

				DAC_write_gate_off(CHANNEL_1);
				DAC_write_gate_off(CHANNEL_2);
				DAC_write_gate_off(CHANNEL_3);
				DAC_write_gate_off(CHANNEL_4);

				overflow_count = 0;	
				REG_TC0_CCR0 |= TC_CCR_CLKDIS;
			}
			else if (pause == 1){
				REG_PIOA_SODR |= PIO_SODR_P18; 
				pause = 0;
				REG_TC0_CCR0 |= TC_CCR_CLKEN | TC_CCR_SWTRG;
			}
			pause_count= 0;
		}
	 }

	 //check if Aux Encoder 2 was rotated
	 else if ( (status & PIO_ISR_P6) || (status & PIO_ISR_P7) ){
		 control_direction(PIO_ODSR_P6, PIO_ODSR_P7, 1);
	 }

	 //check if Aux Encoder 3 was rotated
	 else if ( (status & PIO_ISR_P8) || (status & PIO_ISR_P9) ){
		control_direction(PIO_ODSR_P8, PIO_ODSR_P9, 2);
	 }

	 else if ( (status & PIO_ISR_P10) ){
		/***************CLOCK IN INT***************/
	 }

	 //check if Aux Encoder 4 was rotated
	 else if ( (status & PIO_ISR_P16) || (status & PIO_ISR_P17) ){
		control_direction(PIO_ODSR_P16, PIO_ODSR_P17, 3);
	 }

	 //check if Aux Encoder 5 was rotated
	 else if ( (status & PIO_ISR_P20) || (status & PIO_ISR_P21) ){
		control_direction(PIO_ODSR_P20, PIO_ODSR_P21, 4);
	 }

	 //check if Aux Encoder 6 was rotated
	 else if ( (status & PIO_ISR_P22) || (status & PIO_ISR_P23) ){
		control_direction(PIO_ODSR_P22, PIO_ODSR_P23, 5);
	 }

	 //check if Aux Encoder 7 was rotated
	 else if ( (status & PIO_ISR_P24) || (status & PIO_ISR_P25) ){
		 control_direction(PIO_ODSR_P24, PIO_ODSR_P25, 6);
	 }
	 
	 //check if Aux Encoder 8 was rotated
	 else if ( (status & PIO_ISR_P26) || (status & PIO_ISR_P27) ){
		 control_direction(PIO_ODSR_P26, PIO_ODSR_P27, 7);
	 }

 }
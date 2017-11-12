/*
 * Steps.c
 *
 * Created: 10/13/2017 9:00:14 PM
 *  Author: Kyle
 */ 

 #include <asf.h>
 //#include "dac.h"
 //#include "encoders.h"
 #include "timers.h"

 #define Base 0

 //Octave 1
 #define A0 (Base)
 #define A0_SH (A0 + 1*0.0833)
 #define B0 (A0 + 2*0.0833)
 #define C1 (A0 + 3*0.0833)
 #define C1_SH (A0 + 4*0.0833)
 #define D1 (A0 + 5*0.0833)
 #define D1_SH (A0 + 6*0.0833)
 #define E1 (A0 + 7*0.0833)
 #define F1 (A0 + 8*0.0833)
 #define F1_SH (A0 + 9*0.0833)
 #define G1 (A0 + 10*0.0833)
 #define G1_SH (A0 + 11*0.0833)

 //Octave 2
 #define A1 (Base + 1)
 #define A1_SH (A1 + 1*0.0833)
 #define B1 (A1 + 2*0.0833)
 #define C2 (A1 + 3*0.0833)
 #define C2_SH (A1 + 4*0.0833)
 #define D2 (A1 + 5*0.0833)
 #define D2_SH (A1 + 6*0.0833)
 #define E2 (A1 + 7*0.0833)
 #define F2 (A1 + 8*0.0833)
 #define F2_SH (A1 + 9*0.0833)
 #define G2 (A1 + 10*0.0833)
 #define G2_SH (A1 + 11*0.0833)

 //Octave 3
 #define A2 (Base + 2)
 #define A2_SH (A2 + 1*0.0833)
 #define B2 (A2 + 2*0.0833)
 #define C3 (A2 + 3*0.0833)
 #define C3_SH (A2 + 4*0.0833)
 #define D3 (A2 + 5*0.0833)
 #define D3_SH (A2 + 6*0.0833)
 #define E3 (A2 + 7*0.0833)
 #define F3 (A2 + 8*0.0833)
 #define F3_SH (A2 + 9*0.0833)
 #define G3 (A2 + 10*0.0833)
 #define G3_SH (A2 + 11*0.0833)

 //Octave 4
 #define A3 (Base + 3)
 #define A3_SH (A3 + 1*0.0833)
 #define B3 (A3 + 2*0.0833)
 #define C4 (A3 + 3*0.0833)
 #define C4_SH (A3 + 4*0.0833)
 #define D4 (A3 + 5*0.0833)
 #define D4_SH (A3 + 6*0.0833)
 #define E4 (A3 + 7*0.0833)
 #define F4 (A3 + 8*0.0833)
 #define F4_SH (A3 + 9*0.0833)
 #define G4 (A3 + 10*0.0833)
 #define G4_SH (A3 + 11*0.0833)

 //Octave 5
 #define A4 (Base + 4)
 #define A4_SH (A4 + 1*0.0833)
 #define B4 (A4 + 2*0.0833)
 #define C5 (A4 + 3*0.0833)
 #define C5_SH (A4 + 4*0.0833)
 #define D5 (A4 + 5*0.0833)
 #define D5_SH (A4 + 6*0.0833)
 #define E5 (A4 + 7*0.0833)
 #define F5 (A4 + 8*0.0833)
 #define F5_SH (A4 + 9*0.0833)
 #define G5 (A4 + 10*0.0833)
 #define G5_SH (A4 + 11*0.0833)

 //Octave 6
 #define A5 (Base + 5)
 #define A5_SH (A5 + 1*0.0833)
 #define B5 (A5 + 2*0.0833)
 #define C6 (A5 + 3*0.0833)
 #define C6_SH (A5 + 4*0.0833)
 #define D6 (A5 + 5*0.0833)
 #define D6_SH (A5 + 6*0.0833)
 #define E6 (A5 + 7*0.0833)
 #define F6 (A5 + 8*0.0833)
 #define F6_SH (A5 + 9*0.0833)
 #define G6 (A5 + 10*0.0833)
 #define G6_SH (A5 + 11*0.0833)

 //Octave 7
 #define A6 (Base + 6)
 #define A6_SH (A6 + 1*0.0833)
 #define B6 (A6 + 2*0.0833)
 #define C7 (A6 + 3*0.0833)
 #define C7_SH (A6 + 4*0.0833)
 #define D7 (A6 + 5*0.0833)
 #define D7_SH (A6 + 6*0.0833)
 #define E7 (A6 + 7*0.0833)
 #define F7 (A6 + 8*0.0833)
 #define F7_SH (A6 + 9*0.0833)
 #define G7 (A6 + 10*0.0833)
 #define G7_SH (A6 + 11*0.0833)

 //Octave 8
 #define A7 (Base + 7)
 #define A7_SH (A7 + 1*0.0833)
 #define B7 (A7 + 2*0.0833)
 #define C8 (A7 + 3*0.0833)
 #define C8_SH (A7 + 4*0.0833)
 #define D8 (A7 + 5*0.0833)
 #define D8_SH (A7 + 6*0.0833)
 #define E8 (A7 + 7*0.0833)
 #define F8 (A7 + 8*0.0833)
 #define F8_SH (A7 + 9*0.0833)
 #define G8 (A7 + 10*0.0833)
 #define G8_SH (A7 + 11*0.0833)

 //Octave 9
 #define A8 (Base + 8)
 #define A8_SH (A8 + 1*0.0833)
 #define B8 (A8 + 2*0.0833)
 #define C9 (A8 + 3*0.0833)
 #define C9_SH (A8 + 4*0.0833)
 #define D9 (A8 + 5*0.0833)
 #define D9_SH (A8 + 6*0.0833)
 #define E9 (A8 + 7*0.0833)
 #define F9 (A8 + 8*0.0833)
 #define F9_SH (A8 + 9*0.0833)
 #define G9 (A8 + 10*0.0833)
 #define G9_SH (A8 + 11*0.0833)

 //Octave 10
 #define A9 (Base + 9)
 #define A9_SH (A9 + 1*0.0833)
 #define B9 (A9 + 2*0.0833)
 #define C10 (A9 + 3*0.0833)
 #define C10_SH (A9 + 4*0.0833)
 #define D10 (A9 + 5*0.0833)
 #define D10_SH (A9 + 6*0.0833)
 #define E10 (A9 + 7*0.0833)
 #define F10 (A9 + 8*0.0833)
 #define F10_SH (A9 + 9*0.0833)
 #define G10 (A9 + 10*0.0833)
 #define G10_SH (A9 + 11*0.0833)

 //Octave 11
 #define A10 (Base + 10)

 float notes_lookup[121] = {A0, A0_SH, B0, C1, C1_SH, D1, D1_SH, E1, F1, F1_SH, G1, G1_SH,
						 A1, A1_SH, B1, C2, C2_SH, D2, D2_SH, E2, F2, F2_SH, G2, G2_SH,
						 A2, A2_SH, B2, C3, C3_SH, D3, D3_SH, E3, F3, F3_SH, G3, G3_SH,
						 A3, A3_SH, B3, C4, C4_SH, D4, D4_SH, E4, F4, F4_SH, G4, G4_SH,
						 A4, A4_SH, B4, C5, C5_SH, D5, D5_SH, E5, F5, F5_SH, G5, G5_SH,
						 A5, A5_SH, B5, C6, C6_SH, D6, D6_SH, E6, F6, F6_SH, G6, G6_SH,
						 A6, A6_SH, B6, C7, C7_SH, D7, D7_SH, E7, F7, F7_SH, G7, G7_SH,
						 A7, A7_SH, B7, C8, C8_SH, D8, D8_SH, E8, F8, F8_SH, G8, G8_SH,
						 A8, A8_SH, B8, C9, C9_SH, D9, D9_SH, E9, F9, F9_SH, G9, G9_SH,
						 A9, A9_SH, B9, C10, C10_SH, D10, D10_SH, E10, F10, F10_SH, G10, G10_SH,
						 A10};


 int notes_index[16] = { 0, 1, 2, 3, 4, 5, 6, 7,
						 8, 9, 10, 11, 12, 13, 14, 15};


/* [pattern #][page #][note #][Note, Note Status] */
int patterns[16][16][16][2] = {};



float notes_get(uint8_t curr_step){
	int lookup_index = patterns[curr_pattern][curr_page][curr_step][0];
	return notes_lookup[lookup_index];
}

int notes_status_get(uint8_t curr_step){
	return patterns[curr_pattern][curr_page][curr_step][1];
}

int notes_display_get(uint8_t display_page, uint8_t step){
	return patterns[curr_pattern][display_page][step][1];
}

void notes_status_set(uint8_t display_page, int leds_status[]){

	/* match notes status to current display page status */
	for (int i = 0; i < 16; i++){
		patterns[curr_pattern][display_page][i][1] = leds_status[i];
	}

}


void notes_inc(uint8_t step){
	if (patterns[curr_pattern][display_page][step][0] < 120){
		patterns[curr_pattern][display_page][step][0]++;
	}
}

void notes_dec(uint8_t step){
	if (patterns[curr_pattern][display_page][step][0] > 0){
		patterns[curr_pattern][display_page][step][0]--;
	}
}
 
 
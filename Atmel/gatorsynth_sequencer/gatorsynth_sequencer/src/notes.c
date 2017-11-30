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
 #include "sequencer.h"
 #include "notes.h"

 #define Base 1

 //Octave 1
 #define C0 (Base)
 #define C0_SH (C0 + 1*0.0833)
 #define D0 (C0 + 2*0.0833)
 #define D0_SH (C0 + 3*0.0833)
 #define E0 (C0 + 4*0.0833)
 #define F0 (C0 + 5*0.0833)
 #define F0_SH (C0 + 6*0.0833)
 #define G0 (C0 + 7*0.0833)
 #define G0_SH (C0 + 8*0.0833)
 #define A0 (C0 + 9*0.0833)
 #define A0_SH (C0 + 10*0.0833)
 #define B0 (C0 + 11*0.0833)

 //Octave 2
 #define C1 (Base + 1)
 #define C1_SH (C1 + 1*0.0833)
 #define D1 (C1 + 2*0.0833)
 #define D1_SH (C1 + 3*0.0833)
 #define E1 (C1 + 4*0.0833)
 #define F1 (C1 + 5*0.0833)
 #define F1_SH (C1 + 6*0.0833)
 #define G1 (C1 + 7*0.0833)
 #define G1_SH (C1 + 8*0.0833)
 #define A1 (C1 + 9*0.0833)
 #define A1_SH (C1 + 10*0.0833)
 #define B1 (C1 + 11*0.0833)

 //Octave 3
 #define C2 (Base + 2)
 #define C2_SH (C2 + 1*0.0833)
 #define D2 (C2 + 2*0.0833)
 #define D2_SH (C2 + 3*0.0833)
 #define E2 (C2 + 4*0.0833)
 #define F2 (C2 + 5*0.0833)
 #define F2_SH (C2 + 6*0.0833)
 #define G2 (C2 + 7*0.0833)
 #define G2_SH (C2 + 8*0.0833)
 #define A2 (C2 + 9*0.0833)
 #define A2_SH (C2 + 10*0.0833)
 #define B2 (C2 + 11*0.0833)

 //Octave 4
 #define C3 (Base + 3)
 #define C3_SH (C3 + 1*0.0833)
 #define D3 (C3 + 2*0.0833)
 #define D3_SH (C3 + 3*0.0833)
 #define E3 (C3 + 4*0.0833)
 #define F3 (C3 + 5*0.0833)
 #define F3_SH (C3 + 6*0.0833)
 #define G3 (C3 + 7*0.0833)
 #define G3_SH (C3 + 8*0.0833)
 #define A3 (C3 + 9*0.0833)
 #define A3_SH (C3 + 10*0.0833)
 #define B3 (C3 + 11*0.0833)

 //Octave 5
 #define C4 (Base + 4)
 #define C4_SH (C4 + 1*0.0833)
 #define D4 (C4 + 2*0.0833)
 #define D4_SH (C4 + 3*0.0833)
 #define E4 (C4 + 4*0.0833)
 #define F4 (C4 + 5*0.0833)
 #define F4_SH (C4 + 6*0.0833)
 #define G4 (C4 + 7*0.0833)
 #define G4_SH (C4 + 8*0.0833)
 #define A4 (C4 + 9*0.0833)
 #define A4_SH (C4 + 10*0.0833)
 #define B4 (C4 + 11*0.0833)

 //Octave 6
 #define C5 (Base + 5)
 #define C5_SH (C5 + 1*0.0833)
 #define D5 (C5 + 2*0.0833)
 #define D5_SH (C5 + 3*0.0833)
 #define E5 (C5 + 4*0.0833)
 #define F5 (C5 + 5*0.0833)
 #define F5_SH (C5 + 6*0.0833)
 #define G5 (C5 + 7*0.0833)
 #define G5_SH (C5 + 8*0.0833)
 #define A5 (C5 + 9*0.0833)
 #define A5_SH (C5 + 10*0.0833)
 #define B5 (C5 + 11*0.0833)

 //Octave 7
 #define C6 (Base + 6)
 #define C6_SH (C6 + 1*0.0833)
 #define D6 (C6 + 2*0.0833)
 #define D6_SH (C6 + 3*0.0833)
 #define E6 (C6 + 4*0.0833)
 #define F6 (C6 + 5*0.0833)
 #define F6_SH (C6 + 6*0.0833)
 #define G6 (C6 + 7*0.0833)
 #define G6_SH (C6 + 8*0.0833)
 #define A6 (C6 + 9*0.0833)
 #define A6_SH (C6 + 10*0.0833)
 #define B6 (C6 + 11*0.0833)

 //Octave 8
 #define C7 (Base + 7)
 #define C7_SH (C7 + 1*0.0833)
 #define D7 (C7 + 2*0.0833)
 #define D7_SH (C7 + 3*0.0833)
 #define E7 (C7 + 4*0.0833)
 #define F7 (C7 + 5*0.0833)
 #define F7_SH (C7 + 6*0.0833)
 #define G7 (C7 + 7*0.0833)
 #define G7_SH (C7 + 8*0.0833)
 #define A7 (C7 + 9*0.0833)
 #define A7_SH (C7 + 10*0.0833)
 #define B7 (C7 + 11*0.0833)

 //Octave 9
 #define C8 (Base + 8)
 #define C8_SH (C8 + 1*0.0833)
 #define D8 (C8 + 2*0.0833)
 #define D8_SH (C8 + 3*0.0833)
 #define E8 (C8 + 4*0.0833)
 #define F8 (C8 + 5*0.0833)
 #define F8_SH (C8 + 6*0.0833)
 #define G8 (C8 + 7*0.0833)
 #define G8_SH (C8 + 8*0.0833)
 #define A8 (C8 + 9*0.0833)
 #define A8_SH (C8 + 10*0.0833)
 #define B8 (C8 + 11*0.0833)

 //Octave 10
 #define C9 (Base + 9)
//  #define C9_SH (C9 + 1*0.0833)
//  #define D9 (C9 + 2*0.0833)
//  #define D9_SH (C9 + 3*0.0833)
//  #define E9 (C9 + 4*0.0833)
//  #define F9 (C9 + 5*0.0833)
//  #define F9_SH (C9 + 6*0.0833)
//  #define G9 (C9 + 7*0.0833)
//  #define G9_SH (C9 + 8*0.0833)
//  #define A9 (C9 + 9*0.0833)
//  #define A9_SH (C9 + 10*0.0833)
//  #define B9 (C9 + 11*0.0833)
// 
//  //Octave 11
//  #define C10 (Base + 10)

#define LUT_C0		(0)
#define LUT_C0_SH	(1)
#define LUT_D0		(2)
#define LUT_D0_SH 	(3)
#define LUT_E0 		(4)
#define LUT_F0		(5)
#define LUT_F0_SH 	(6)
#define LUT_G0 		(7)
#define LUT_G0_SH 	(8)
#define LUT_A0 		(9)
#define LUT_A0_SH 	(10)
#define LUT_B0 		(11)

#define LUT_C1		LUT_C0 + 12
#define LUT_C1_SH	LUT_C0_SH + 12
#define LUT_D1		LUT_D0 + 12
#define LUT_D1_SH	LUT_D0_SH + 12
#define LUT_E1		LUT_E0 + 12
#define LUT_F1		LUT_F0 + 12
#define LUT_F1_SH	LUT_F0_SH + 12
#define LUT_G1		LUT_G0 + 12
#define LUT_G1_SH	LUT_G0_SH + 12
#define LUT_A1		LUT_A0 + 12
#define LUT_A1_SH	LUT_A0_SH + 12
#define LUT_B1		LUT_B0 + 12

#define LUT_C2		LUT_C1 + 12
#define LUT_C2_SH	LUT_C1_SH + 12
#define LUT_D2		LUT_D1 + 12
#define LUT_D2_SH	LUT_D1_SH + 12
#define LUT_E2		LUT_E1 + 12
#define LUT_F2		LUT_F1 + 12
#define LUT_F2_SH	LUT_F1_SH + 12
#define LUT_G2		LUT_G1 + 12
#define LUT_G2_SH	LUT_G1_SH + 12
#define LUT_A2		LUT_A1 + 12
#define LUT_A2_SH	LUT_A1_SH + 12
#define LUT_B2		LUT_B1 + 12

#define LUT_C3		LUT_C2 + 12
#define LUT_C3_SH	LUT_C2_SH + 12
#define LUT_D3		LUT_D2 + 12
#define LUT_D3_SH	LUT_D2_SH + 12
#define LUT_E3		LUT_E2 + 12
#define LUT_F3		LUT_F2 + 12
#define LUT_F3_SH	LUT_F2_SH + 12
#define LUT_G3		LUT_G2 + 12
#define LUT_G3_SH	LUT_G2_SH + 12
#define LUT_A3		LUT_A2 + 12
#define LUT_A3_SH	LUT_A2_SH + 12
#define LUT_B3		LUT_B2 + 12

#define LUT_C4		LUT_C3 + 12
#define LUT_C4_SH	LUT_C3_SH + 12
#define LUT_D4		LUT_D3 + 12
#define LUT_D4_SH	LUT_D3_SH + 12
#define LUT_E4		LUT_E3 + 12
#define LUT_F4		LUT_F3 + 12
#define LUT_F4_SH	LUT_F3_SH + 12
#define LUT_G4		LUT_G3 + 12
#define LUT_G4_SH	LUT_G3_SH + 12
#define LUT_A4		LUT_A3 + 12
#define LUT_A4_SH	LUT_A3_SH + 12
#define LUT_B4		LUT_B3 + 12

#define LUT_C5		LUT_C4 + 12
#define LUT_C5_SH	LUT_C4_SH + 12
#define LUT_D5		LUT_D4 + 12
#define LUT_D5_SH	LUT_D4_SH + 12
#define LUT_E5		LUT_E4 + 12
#define LUT_F5		LUT_F4 + 12
#define LUT_F5_SH	LUT_F4_SH + 12
#define LUT_G5		LUT_G4 + 12
#define LUT_G5_SH	LUT_G4_SH + 12
#define LUT_A5		LUT_A4 + 12
#define LUT_A5_SH	LUT_A4_SH + 12
#define LUT_B5		LUT_B4 + 12

#define LUT_C6		LUT_C5 + 12
#define LUT_C6_SH	LUT_C5_SH + 12
#define LUT_D6		LUT_D5 + 12
#define LUT_D6_SH	LUT_D5_SH + 12
#define LUT_E6		LUT_E5 + 12
#define LUT_F6		LUT_F5 + 12
#define LUT_F6_SH	LUT_F5_SH + 12
#define LUT_G6		LUT_G5 + 12
#define LUT_G6_SH	LUT_G5_SH + 12
#define LUT_A6		LUT_A5 + 12
#define LUT_A6_SH	LUT_A5_SH + 12
#define LUT_B6		LUT_B5 + 12

#define LUT_C7		LUT_C6 + 12
#define LUT_C7_SH	LUT_C6_SH + 12
#define LUT_D7		LUT_D6 + 12
#define LUT_D7_SH	LUT_D6_SH + 12
#define LUT_E7		LUT_E6 + 12
#define LUT_F7		LUT_F6 + 12
#define LUT_F7_SH	LUT_F6_SH + 12
#define LUT_G7		LUT_G6 + 12
#define LUT_G7_SH	LUT_G6_SH + 12
#define LUT_A7		LUT_A6 + 12
#define LUT_A7_SH	LUT_A6_SH + 12
#define LUT_B7		LUT_B6 + 12

#define LUT_C8		LUT_C7 + 12
#define LUT_C8_SH	LUT_C7_SH + 12
#define LUT_D8		LUT_D7 + 12
#define LUT_D8_SH	LUT_D7_SH + 12
#define LUT_E8		LUT_E7 + 12
#define LUT_F8		LUT_F7 + 12
#define LUT_F8_SH	LUT_F7_SH + 12
#define LUT_G8		LUT_G7 + 12
#define LUT_G8_SH	LUT_G7_SH + 12
#define LUT_A8		LUT_A7 + 12
#define LUT_A8_SH	LUT_A7_SH + 12
#define LUT_B8		LUT_B7 + 12

 float notes_lookup[109] = {C0, C0_SH, D0, D0_SH, E0, F0, F0_SH, G0, G0_SH, A0, A0_SH, B0, 
							C1, C1_SH, D1, D1_SH, E1, F1, F1_SH, G1, G1_SH, A1, A1_SH, B1, 
							C2, C2_SH, D2, D2_SH, E2, F2, F2_SH, G2, G2_SH, A2, A2_SH, B2, 
							C3, C3_SH, D3, D3_SH, E3, F3, F3_SH, G3, G3_SH, A3, A3_SH, B3, 
							C4, C4_SH, D4, D4_SH, E4, F4, F4_SH, G4, G4_SH, A4, A4_SH, B4, 
							C5, C5_SH, D5, D5_SH, E5, F5, F5_SH, G5, G5_SH, A5, A5_SH, B5, 
							C6, C6_SH, D6, D6_SH, E6, F6, F6_SH, G6, G6_SH, A6, A6_SH, B6, 
							C7, C7_SH, D7, D7_SH, E7, F7, F7_SH, G7, G7_SH, A7, A7_SH, B7, 
							C8, C8_SH, D8, D8_SH, E8, F8, F8_SH, G8, G8_SH, A8, A8_SH, B8, 
							C9};
							
// 							C9_SH, D9, D9_SH, E9, F9, F9_SH, G9, G9_SH, A9, A9_SH, B9, 
// 							C10};

// 
//  int notes_index[16] = { 0, 1, 2, 3, 4, 5, 6, 7,
// 						 8, 9, 10, 11, 12, 13, 14, 15};


/* [pattern #][page #][note #][Note, Note Status] */
//int patterns[16][16][16][3] = {};

	//test initializations

float notes_get(uint8_t curr_step, uint8_t channel){
	int lookup_index;

	if (channel == CHANNEL_1){
		lookup_index = patterns[curr_pattern_ch[0]][curr_page_ch[0]][curr_step][0];
	}
	else if (channel == CHANNEL_2){
		lookup_index = patterns[curr_pattern_ch[1]][curr_page_ch[1]][curr_step][0];
	}
	else if (channel == CHANNEL_3){
		lookup_index = patterns[curr_pattern_ch[2]][curr_page_ch[2]][curr_step][0];
	}
	else if (channel == CHANNEL_4){
		lookup_index = patterns[curr_pattern_ch[3]][curr_page_ch[3]][curr_step][0];
	}
	
	return notes_lookup[lookup_index];
}

uint8_t notes_status_get(uint8_t curr_step, uint8_t channel){

	if (channel == CHANNEL_1){
		return patterns[curr_pattern_ch[0]][curr_page_ch[0]][curr_step][1];
	}
	else if (channel == CHANNEL_2){
		return patterns[curr_pattern_ch[1]][curr_page_ch[1]][curr_step][1];
	}
	else if (channel == CHANNEL_3){
		return patterns[curr_pattern_ch[2]][curr_page_ch[2]][curr_step][1];
	}
	else if (channel == CHANNEL_4){
		return patterns[curr_pattern_ch[3]][curr_page_ch[3]][curr_step][1];
	}

	//default
	return patterns[curr_pattern_ch[0]][curr_page_ch[0]][curr_step][1];
}

uint8_t notes_display_get(uint8_t display_page, uint8_t step){
	return patterns[curr_pattern][display_page][step][1];
}

void notes_status_set(uint8_t display_page, int leds_status[]){

	/* match notes status to current display page status */
	for (int i = 0; i < 16; i++){
		patterns[curr_pattern][display_page][i][1] = leds_status[i];
	}

}

void notes_clear(uint8_t curr_pattern){
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			patterns[curr_pattern][i][j][0] = 48; //set note to C4
			patterns[curr_pattern][i][j][1]= 0;	  //turn notes all OFF
		}
	}
}

void notes_default(){
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			for (int k = 0; k < 16; k++){
				patterns[i][j][k][0] = 48; //set note to C4
				patterns[i][j][k][1]= 0;	  //turn notes all OFF
			}
		}
	}

	patterns[4][0][0][0] = LUT_D1;
	patterns[4][0][0][1] = 1;
	patterns[4][0][1][0] = LUT_D1;
	patterns[4][0][1][1] = 0;

	patterns[4][0][2][0] = LUT_A2;
	patterns[4][0][2][1] = 1;
	patterns[4][0][3][0] = LUT_A2;
	patterns[4][0][3][1] = 0;

	patterns[4][0][4][0] = LUT_A2;
	patterns[4][0][4][1] = 1;
	patterns[4][0][5][0] = LUT_A2;
	patterns[4][0][5][1] = 0;

	patterns[4][0][6][0] = LUT_E1;
	patterns[4][0][6][1] = 1;

	patterns[4][0][7][0] = LUT_E2;
	patterns[4][0][7][1] = 1;

	patterns[4][0][8][0] = LUT_B2;
	patterns[4][0][8][1] = 1;
	patterns[4][0][9][0] = LUT_B2;
	patterns[4][0][9][1] = 0;
	patterns[4][0][10][0] = LUT_B2;
	patterns[4][0][10][1] = 0;
	patterns[4][0][11][0] = LUT_B2;
	patterns[4][0][11][1] = 0;

	patterns[4][0][12][0] = LUT_F1;
	patterns[4][0][12][1] = 1;
	patterns[4][0][13][0] = LUT_F1;
	patterns[4][0][13][1] = 0;

	patterns[4][0][14][0] = LUT_C3;
	patterns[4][0][14][1] = 1;
	patterns[4][0][15][0] = LUT_C3;
	patterns[4][0][15][1] = 0;

	patterns[4][1][0][0] = LUT_C3;
	patterns[4][1][0][1] = 1;
	patterns[4][1][1][0] = LUT_C3;
	patterns[4][1][1][1] = 0;

	patterns[4][1][2][0] = LUT_E1;
	patterns[4][1][2][1] = 1;

	patterns[4][1][3][0] = LUT_E2;
	patterns[4][1][3][1] = 1;

	patterns[4][1][4][0] = LUT_B2;
	patterns[4][1][4][1] = 1;
	patterns[4][1][5][0] = LUT_B2;
	patterns[4][1][5][1] = 0;
	patterns[4][1][6][0] = LUT_B2;
	patterns[4][1][6][1] = 0;
	patterns[4][1][7][0] = LUT_B2;
	patterns[4][1][7][1] = 0;

	
	patterns[4][1][8][0] = LUT_D1;
	patterns[4][1][8][1] = 1;
	patterns[4][1][9][0] = LUT_D1;
	patterns[4][1][9][1] = 0;

	patterns[4][1][10][0] = LUT_A2;
	patterns[4][1][10][1] = 1;
	patterns[4][1][11][0] = LUT_A2;
	patterns[4][1][11][1] = 0;

	patterns[4][1][12][0] = LUT_A2;
	patterns[4][1][12][1] = 1;
	patterns[4][1][13][0] = LUT_A2;
	patterns[4][1][13][1] = 0;

	patterns[4][1][14][0] = LUT_E1;
	patterns[4][1][14][1] = 1;
	patterns[4][1][15][0] = LUT_E2;
	patterns[4][1][15][1] = 1;

	patterns[4][2][0][0] = LUT_B2;
	patterns[4][2][0][1] = 1;
	patterns[4][2][1][0] = LUT_B2;
	patterns[4][2][1][1] = 0;
	patterns[4][2][2][0] = LUT_B2;
	patterns[4][2][2][1] = 0;
	patterns[4][2][3][0] = LUT_B2;
	patterns[4][2][3][1] = 0;

	patterns[4][2][4][0] = LUT_F1;
	patterns[4][2][4][1] = 1;
	patterns[4][2][5][0] = LUT_F1;
	patterns[4][2][5][1] = 0;

	patterns[4][2][6][0] = LUT_C3;
	patterns[4][2][6][1] = 1;
	patterns[4][2][7][0] = LUT_C3;
	patterns[4][2][7][1] = 0;

	patterns[4][2][8][0] = LUT_C3;
	patterns[4][2][8][1] = 1;
	patterns[4][2][9][0] = LUT_C3;
	patterns[4][2][9][1] = 0;

	patterns[4][2][10][0] = LUT_E1;
	patterns[4][2][10][1] = 1;

	patterns[4][2][11][0] = LUT_E2;
	patterns[4][2][11][1] = 1;

	patterns[4][2][12][0] = LUT_B2;
	patterns[4][2][12][1] = 1;
	patterns[4][2][13][0] = LUT_B2;
	patterns[4][2][13][1] = 0;
	patterns[4][2][14][0] = LUT_B2;
	patterns[4][2][14][1] = 0;
	patterns[4][2][15][0] = LUT_B2;
	patterns[4][2][15][1] = 0;
	
	patterns[4][3][0][0] = LUT_D3;
	patterns[4][3][0][1] = 1;

	patterns[4][3][1][0] = LUT_F3;
	patterns[4][3][1][1] = 1;

	patterns[4][3][2][0] = LUT_D4;
	patterns[4][3][2][1] = 1;
	patterns[4][3][3][0] = LUT_D4;
	patterns[4][3][3][1] = 0;
	patterns[4][3][4][0] = LUT_D4;
	patterns[4][3][4][1] = 0;
	patterns[4][3][5][0] = LUT_D4;
	patterns[4][3][5][1] = 0;

	patterns[4][3][6][0] = LUT_D3;
	patterns[4][3][6][1] = 1;
	patterns[4][3][7][0] = LUT_F3;
	patterns[4][3][7][1] = 1;
	patterns[4][3][8][0] = LUT_D4;
	patterns[4][3][8][1] = 1;
	patterns[4][3][9][0] = LUT_D4;
	patterns[4][3][9][1] = 0;
	patterns[4][3][10][0] = LUT_D4;
	patterns[4][3][10][1] = 0;
	patterns[4][3][11][0] = LUT_D4;
	patterns[4][3][11][1] = 0;

	patterns[4][3][12][0] = LUT_E4;
	patterns[4][3][12][1] = 1;
	patterns[4][3][13][0] = LUT_E4;
	patterns[4][3][13][1] = 0;
	patterns[4][3][14][0] = LUT_E4;
	patterns[4][3][14][1] = 0;

	patterns[4][3][15][0] = LUT_F4;
	patterns[4][3][15][1] = 1;
	patterns[4][4][0][0] = LUT_E4;
	patterns[4][4][0][1] = 1;
	patterns[4][4][1][0] = LUT_F4;
	patterns[4][4][1][1] = 1;
	patterns[4][4][2][0] = LUT_E4;
	patterns[4][4][2][1] = 1;
	patterns[4][4][3][0] = LUT_C4;
	patterns[4][4][3][1] = 1;
	patterns[4][4][4][0] = LUT_A3;
	patterns[4][4][4][1] = 1;
	patterns[4][4][5][0] = LUT_A3;
	patterns[4][4][5][1] = 0;
	patterns[4][4][6][0] = LUT_A3;
	patterns[4][4][6][1] = 0;
	patterns[4][4][7][0] = LUT_A3;
	patterns[4][4][7][1] = 0;

	patterns[4][4][8][0] = LUT_A3;
	patterns[4][4][8][1] = 1;
	patterns[4][4][9][0] = LUT_A3;
	patterns[4][4][9][1] = 0;

	patterns[4][4][10][0] = LUT_D3;
	patterns[4][4][10][1] = 1;
	patterns[4][4][11][0] = LUT_D3;
	patterns[4][4][11][1] = 0;

	patterns[4][4][12][0] = LUT_F3;
	patterns[4][4][12][1] = 1;
	patterns[4][4][13][0] = LUT_G3;
	patterns[4][4][13][1] = 1;
	patterns[4][4][14][0] = LUT_A3;
	patterns[4][4][14][1] = 1;
	patterns[4][4][15][0] = LUT_A3;
	patterns[4][4][15][1] = 0;
	patterns[4][5][0][0] = LUT_A3;
	patterns[4][5][0][1] = 0;
	patterns[4][5][1][0] = LUT_A3;
	patterns[4][5][1][1] = 0;

	patterns[4][5][2][0] = LUT_A3;
	patterns[4][5][2][1] = 1;
	patterns[4][5][3][0] = LUT_A3;
	patterns[4][5][3][1] = 0;

	patterns[4][5][4][0] = LUT_D3;
	patterns[4][5][4][1] = 1;
	patterns[4][5][5][0] = LUT_D3;
	patterns[4][5][5][1] = 0;

	patterns[4][5][6][0] = LUT_F3;
	patterns[4][5][6][1] = 1;
	patterns[4][5][7][0] = LUT_G3;
	patterns[4][5][7][1] = 1;

	patterns[4][5][8][0] = LUT_E3;
	patterns[4][5][8][1] = 1;
	patterns[4][5][9][0] = LUT_E3;
	patterns[4][5][9][1] = 0;
	patterns[4][5][10][0] = LUT_E3;
	patterns[4][5][10][1] = 0;
	patterns[4][5][11][0] = LUT_E3;
	patterns[4][5][11][1] = 0;

	patterns[4][5][12][0] = LUT_D3;
	patterns[4][5][12][1] = 1;
	patterns[4][5][13][0] = LUT_F3;
	patterns[4][5][13][1] = 1;

	patterns[4][5][14][0] = LUT_D4;
	patterns[4][5][14][1] = 1;
	patterns[4][5][15][0] = LUT_D4;
	patterns[4][5][15][1] = 0;
	patterns[4][6][0][0] = LUT_D4;
	patterns[4][6][0][1] = 0;
	patterns[4][6][1][0] = LUT_D4;
	patterns[4][6][1][1] = 0;

	patterns[4][6][2][0] = LUT_D3;
	patterns[4][6][2][1] = 1;
	patterns[4][6][3][0] = LUT_F3;
	patterns[4][6][3][1] = 1;

	patterns[4][6][4][0] = LUT_D4;
	patterns[4][6][4][1] = 1;
	patterns[4][6][5][0] = LUT_D4;
	patterns[4][6][5][1] = 0;
	patterns[4][6][6][0] = LUT_D4;
	patterns[4][6][6][1] = 0;
	patterns[4][6][7][0] = LUT_D4;
	patterns[4][6][7][1] = 0;

	patterns[4][6][8][0] = LUT_E4;
	patterns[4][6][8][1] = 1;
	patterns[4][6][9][0] = LUT_E4;
	patterns[4][6][9][1] = 0;
	patterns[4][6][10][0] = LUT_E4;
	patterns[4][6][10][1] = 0;

	patterns[4][6][11][0] = LUT_F4;
	patterns[4][6][11][1] = 1;
	patterns[4][6][12][0] = LUT_E4;
	patterns[4][6][12][1] = 1;
	patterns[4][6][13][0] = LUT_F4;
	patterns[4][6][13][1] = 1;
	patterns[4][6][14][0] = LUT_E4;
	patterns[4][6][14][1] = 1;
	patterns[4][6][15][0] = LUT_C4;
	patterns[4][6][15][1] = 1;
	patterns[4][7][0][0] = LUT_A3;
	patterns[4][7][0][1] = 1;
	patterns[4][7][1][0] = LUT_A3;
	patterns[4][7][1][1] = 0;
	patterns[4][7][2][0] = LUT_A3;
	patterns[4][7][2][1] = 0;
	patterns[4][7][3][0] = LUT_A3;
	patterns[4][7][3][1] = 0;

	patterns[4][7][4][0] = LUT_A3;
	patterns[4][7][4][1] = 1;
	patterns[4][7][5][0] = LUT_A3;
	patterns[4][7][5][1] = 0;

	patterns[4][7][6][0] = LUT_D3;
	patterns[4][7][6][1] = 1;
	patterns[4][7][7][0] = LUT_D3;
	patterns[4][7][7][1] = 0;

	patterns[4][7][8][0] = LUT_F3;
	patterns[4][7][8][1] = 1;
	patterns[4][7][9][0] = LUT_G3;
	patterns[4][7][9][1] = 1;

	patterns[4][7][10][0] = LUT_A3;
	patterns[4][7][10][1] = 1;
	patterns[4][7][11][0] = LUT_A3;
	patterns[4][7][11][1] = 0;

	patterns[4][7][12][0] = LUT_A2;
	patterns[4][7][12][1] = 1;
	patterns[4][7][13][0] = LUT_A2;
	patterns[4][7][13][1] = 0;

	patterns[4][7][14][0] = LUT_A3;
	patterns[4][7][14][1] = 1;
	patterns[4][7][15][0] = LUT_A3;
	patterns[4][7][15][1] = 0;

	patterns[4][8][0][0] = LUT_D3;
	patterns[4][8][0][1] = 1;
	patterns[4][8][1][0] = LUT_D3;
	patterns[4][8][1][1] = 0;

	patterns[4][8][2][0] = LUT_A2;
	patterns[4][8][2][1] = 1;
	patterns[4][8][3][0] = LUT_A2;
	patterns[4][8][3][1] = 0;
	patterns[4][8][4][0] = LUT_A2;
	patterns[4][8][4][1] = 1;
	patterns[4][8][5][0] = LUT_A2;
	patterns[4][8][5][1] = 0;

	patterns[4][8][6][0] = LUT_E2;
	patterns[4][8][6][1] = 1;
	patterns[4][8][7][0] = LUT_E2;
	patterns[4][8][6][1] = 0;

	patterns[4][8][8][0] = LUT_B2;
	patterns[4][8][8][1] = 1;
	patterns[4][8][9][0] = LUT_B2;
	patterns[4][8][9][1] = 0;
	patterns[4][8][10][0] = LUT_B2;
	patterns[4][8][10][1] = 0;
	patterns[4][8][11][0] = LUT_B2;
	patterns[4][8][11][1] = 0;

	patterns[4][8][12][1] = 0;
	patterns[4][8][13][1] = 0;

	patterns[4][8][14][0] = LUT_C3;
	patterns[4][8][14][1] = 1;
	patterns[4][8][15][0] = LUT_C3;
	patterns[4][8][15][1] = 0;

	
// 	patterns[4][0][12][1] = 1;
// 	patterns[4][0][13][1] = 0;
// 	patterns[4][0][14][1] = 1;
// 	patterns[4][0][15][1] = 0;
// 
// 	patterns[4][1][0][1] = 1;
// 	patterns[4][1][1][1] = 0;
// 
// 	patterns[4][0][0][0] = 1;
// 	patterns[4][0][1][0] = 1;
// 	patterns[4][0][2][0] = ;
// 	patterns[4][0][3][0] = ;
// 	patterns[4][0][4][0] = ;
// 	patterns[4][0][5][0] = ;
// 	patterns[4][0][6][0] = ;
// 	patterns[4][0][7][0] = ;
// 	patterns[4][0][8][0] = ;
// 	patterns[4][0][9][0] = ;
// 	patterns[4][0][10][0] = ;
// 	patterns[4][0][11][0] = ;
// 	patterns[4][0][12][0] = ;
// 	patterns[4][0][13][0] = ;
// 	patterns[4][0][14][0] = ;
// 	patterns[4][0][15][0] = ;
// 
// 	patterns[4][0][0][0] = ;
// 	patterns[4][0][1][0] = ;
// 	patterns[4][0][2][0] = ;
// 	patterns[4][0][3][0] = ;
// 	patterns[4][0][4][0] = ;
// 	patterns[4][0][5][0] = ;
// 	patterns[4][0][6][0] = ;
// 	patterns[4][0][7][0] = ;
// 	patterns[4][0][8][0] = ;
// 	patterns[4][0][9][0] = ;
// 	patterns[4][0][10][0] = ;
// 	patterns[4][0][11][0] = ;
// 	patterns[4][0][12][0] = ;
// 	patterns[4][0][13][0] = ;
// 	patterns[4][0][14][0] = ;
// 	patterns[4][0][15][0] = ;

// 	patterns[4][0][9][0] = 61;
// 	patterns[4][0][10][0] = LUT_D5;
// 	patterns[4][0][11][0] = LUT_D5;


}


void notes_inc(uint8_t step){
	if (patterns[curr_pattern][display_page][step][0] < 108){
		patterns[curr_pattern][display_page][step][0]++;
	}

// 	patterns[curr_pattern][display_page][0][0] = 60;
// 	patterns[curr_pattern][display_page][1][0] = 60;
// 	patterns[curr_pattern][display_page][2][0] = 62;
// 	patterns[curr_pattern][display_page][3][0] = 64;
// 	patterns[curr_pattern][display_page][4][0] = 67;
// 	patterns[curr_pattern][display_page][5][0] = 67;
// 	patterns[curr_pattern][display_page][6][0] = 67;
// 	patterns[curr_pattern][display_page][7][0] = 64;
// 
// 	patterns[curr_pattern][display_page][8][0] = 64; 
// 	patterns[curr_pattern][display_page][9][0] = 64;
// 	patterns[curr_pattern][display_page][10][0] = 60;
// 	patterns[curr_pattern][display_page][11][0] = 55; 
// 	patterns[curr_pattern][display_page][12][0] = 55;
// 	patterns[curr_pattern][display_page][13][0] = 55;
// 	patterns[curr_pattern][display_page][14][0] = 57;
// 	patterns[curr_pattern][display_page][15][0] = 59;
// 
// 	patterns[curr_pattern][display_page][0][1] = 1;
// 	patterns[curr_pattern][display_page][1][1] = 1;
// 	patterns[curr_pattern][display_page][2][1] = 1;
// 	patterns[curr_pattern][display_page][3][1] = 1;
// 	patterns[curr_pattern][display_page][4][1] = 0;
// 	patterns[curr_pattern][display_page][5][1] = 1;
// 	patterns[curr_pattern][display_page][6][1] = 0;
// 	patterns[curr_pattern][display_page][7][1] = 1;
// 
// 	patterns[curr_pattern][display_page][8][1] = 1;
// 	patterns[curr_pattern][display_page][9][1] = 1;
// 	patterns[curr_pattern][display_page][10][1] = 1;
// 	patterns[curr_pattern][display_page][11][1] = 1;
// 	patterns[curr_pattern][display_page][12][1] = 0;
// 	patterns[curr_pattern][display_page][13][1] = 1;
// 	patterns[curr_pattern][display_page][14][1] = 1;
// 	patterns[curr_pattern][display_page][15][1] = 1;
// 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][0][0] = 28;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][1][0] = 28;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][2][0] = 28; 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][3][0] = 0; 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][4][0] = 28;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][5][0] = 28; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][6][0] = 28; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][7][0] = 0; //
//
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][8][0] = 25; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][9][0] = 0; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][10][0] = 0; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][11][0] = 25; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][12][0] = 25; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][13][0] = 28; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][14][0] = 0; //
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][15][0] = 28; //
// 
// 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][0][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][1][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][2][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][3][1] = 0;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][4][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][5][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][6][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][7][1] = 0;
// 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][8][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][9][1] = 0;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][10][1] = 0;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][11][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][12][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][13][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][14][1] = 0;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][15][1] = 1;
}

void notes_dec(uint8_t step){
	if (patterns[curr_pattern][display_page][step][0] > 0){
		patterns[curr_pattern][display_page][step][0]--;
	}

// 	patterns[curr_pattern][display_page][0][0] = 60; //C5
// 	patterns[curr_pattern][display_page][1][0] = 60; //C5
// 	patterns[curr_pattern][display_page][2][0] = 62; //D5
// 	patterns[curr_pattern][display_page][3][0] = 64; //E5
// 	patterns[curr_pattern][display_page][4][0] = 67; //G5
// 	patterns[curr_pattern][display_page][5][0] = 67; //G5
// 	patterns[curr_pattern][display_page][6][0] = 67; //G5
// 	patterns[curr_pattern][display_page][7][0] = 64; //E5
// 
// 	patterns[curr_pattern][display_page][8][0] = 64; //F5
// 	patterns[curr_pattern][display_page][9][0] = 64; //E5
// 	patterns[curr_pattern][display_page][10][0] = 60; //C5
// 	patterns[curr_pattern][display_page][11][0] = 55; //G4
// 	patterns[curr_pattern][display_page][12][0] = 55; //G4
// 	patterns[curr_pattern][display_page][13][0] = 55; //G4
// 	patterns[curr_pattern][display_page][14][0] = 57; //A4
// 	patterns[curr_pattern][display_page][15][0] = 59; //B4
// 
// 	patterns[curr_pattern][display_page][0][1] = 1;
// 	patterns[curr_pattern][display_page][1][1] = 1;
// 	patterns[curr_pattern][display_page][2][1] = 1;
// 	patterns[curr_pattern][display_page][3][1] = 1;
// 	patterns[curr_pattern][display_page][4][1] = 0;
// 	patterns[curr_pattern][display_page][5][1] = 1;
// 	patterns[curr_pattern][display_page][6][1] = 0;
// 	patterns[curr_pattern][display_page][7][1] = 1;
// 
// 	patterns[curr_pattern][display_page][8][1] = 1;
// 	patterns[curr_pattern][display_page][9][1] = 1;
// 	patterns[curr_pattern][display_page][10][1] = 1;
// 	patterns[curr_pattern][display_page][11][1] = 1;
// 	patterns[curr_pattern][display_page][12][1] = 0;
// 	patterns[curr_pattern][display_page][13][1] = 1;
// 	patterns[curr_pattern][display_page][14][1] = 1;
// 	patterns[curr_pattern][display_page][15][1] = 1;
// 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][0][0] = 28; //E2
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][1][0] = 28; //E2
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][2][0] = 28; //E2
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][3][0] = 0; //REST
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][4][0] = 28; //E2
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][5][0] = 28; //E2
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][6][0] = 28; //E2
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][7][0] = 0; //REST
// 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][8][0] = 25; //C2_SH
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][9][0] = 0; //REST
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][10][0] = 0; //REST
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][11][0] = 25; //C2_SH
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][12][0] = 25; //C2_SH
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][13][0] = 28; //E2
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][14][0] = 0; //REST
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][15][0] = 28; //E2
// 
// 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][0][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][1][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][2][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][3][1] = 0;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][4][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][5][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][6][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][7][1] = 0;
// 
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][8][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][9][1] = 0;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][10][1] = 0;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][11][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][12][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][13][1] = 1;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][14][1] = 0;
// 	patterns[curr_pattern_ch[1]][curr_page_ch[1]][15][1] = 1;
}
 
 
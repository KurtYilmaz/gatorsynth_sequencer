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

 #define Base 3

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
 #define C9_SH (C9 + 1*0.0833)
 #define D9 (C9 + 2*0.0833)
 #define D9_SH (C9 + 3*0.0833)
 #define E9 (C9 + 4*0.0833)
 #define F9 (C9 + 5*0.0833)
 #define F9_SH (C9 + 6*0.0833)
 #define G9 (C9 + 7*0.0833)
 #define G9_SH (C9 + 8*0.0833)
 #define A9 (C9 + 9*0.0833)
 #define A9_SH (C9 + 10*0.0833)
 #define B9 (C9 + 11*0.0833)

 //Octave 11
 #define C10 (Base + 10)

 float notes_lookup[121] = {C0, C0_SH, D0, D0_SH, E0, F0, F0_SH, G0, G0_SH, A0, A0_SH, B0, 
							C1, C1_SH, D1, D1_SH, E1, F1, F1_SH, G1, G1_SH, A1, A1_SH, B1, 
							C2, C2_SH, D2, D2_SH, E2, F2, F2_SH, G2, G2_SH, A2, A2_SH, B2, 
							C3, C3_SH, D3, D3_SH, E3, F3, F3_SH, G3, G3_SH, A3, A3_SH, B3, 
							C4, C4_SH, D4, D4_SH, E4, F4, F4_SH, G4, G4_SH, A4, A4_SH, B4, 
							C5, C5_SH, D5, D5_SH, E5, F5, F5_SH, G5, G5_SH, A5, A5_SH, B5, 
							C6, C6_SH, D6, D6_SH, E6, F6, F6_SH, G6, G6_SH, A6, A6_SH, B6, 
							C7, C7_SH, D7, D7_SH, E7, F7, F7_SH, G7, G7_SH, A7, A7_SH, B7, 
							C8, C8_SH, D8, D8_SH, E8, F8, F8_SH, G8, G8_SH, A8, A8_SH, B8, 
							C9, C9_SH, D9, D9_SH, E9, F9, F9_SH, G9, G9_SH, A9, A9_SH, B9, 
							C10};

// 
//  int notes_index[16] = { 0, 1, 2, 3, 4, 5, 6, 7,
// 						 8, 9, 10, 11, 12, 13, 14, 15};


/* [pattern #][page #][note #][Note, Note Status] */
int patterns[16][16][16][2] = {};

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

int notes_status_get(uint8_t curr_step, uint8_t channel){

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
 
 
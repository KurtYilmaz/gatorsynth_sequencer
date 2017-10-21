/*
 * notes.h
 *
 * Created: 10/13/2017 9:00:42 PM
 *  Author: Kyle
 */ 


#ifndef NOTES_H_
#define NOTES_H_

#include <stdbool.h>

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


uint8_t notes_status[16] = {1, 0, 1, 0, 1, 0, 1, 0,
						0, 1, 1, 1, 1, 0, 0, 1};

float notes[16] = {A0, 0, B1, 0, C2_SH, 0, A3, 0,
					0, D1, G2, B3, F1_SH, 0, 0, D2};


#endif /* NOTES_H_ */
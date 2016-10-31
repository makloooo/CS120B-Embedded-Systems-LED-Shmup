/*
 * Life_Bars.h
 *
 * Created: 5/27/2016 2:24:11 AM
 *  Author: Mark
 */ 


#ifndef LIFE_BARS_H_
#define LIFE_BARS_H_

// Integer values for convenience
unsigned char p1_life = 0;
unsigned char p2_life = 0;

// These go into the shift register and their respective ports
unsigned short life_data = 0x0000; // left half = p2[1-8], right half = p1[1-8]
unsigned char p_9to10 = 0x00; // bit[3:2] = p2_9/10, bit[1:0] = p1_9/10

unsigned short p1_bits = 0x0000;
unsigned short p2_bits = 0x0000;

// Life-Bar Control
// !!! ONLY UPDATES GLOBAL VARIABLES !!!
enum LED_States {LED_Start, LED_Idle, LED_Convert};
int Update_Life(int state) {
	
	unsigned char k;
	
	switch (state) {
		case LED_Start:
			p1_life = 0;
			p2_life = 0;
			state = LED_Convert;
		break;
		
		case LED_Convert:
			// dont really need to reset it all the time, but meh
			for (p1_bits = 0x00, k = 0; k < p1_life; ++k) {
				p1_bits <<= 1;
				p1_bits += 1;
			}
			for (p2_bits = 0x00, k = 0; k < p2_life; ++k) {
				p2_bits <<= 1;
				p2_bits += 1;
			}
			
			life_data = (p2_bits << 8) | (p1_bits & 0x00FF);
			p_9to10 = (((p2_bits >> 8) << 2) | (p1_bits >> 8)) << 4;
			state = LED_Idle;
		break;
		
		case LED_Idle:
			// USART check for incoming transmission
			
			if (GetBit(stg_event, START_GAME)) {
				p1_life = 10, p2_life = 0;
				state = LED_Convert;
			}
			
//			if (GetBit(stg_event, P1_EXTEND) && p1_life < 10) {++p1_life; state = LED_Convert;}
			if (GetBit(stg_event, P1_HIT) && p1_life > 0) {--p1_life; state = LED_Convert;}
// 			if (GetBit(stg_event, P2_EXT	END) && p2_life < 10) {++p2_life; state = LED_Convert;}
 			//if (GetBit(stg_event, P2_HIT) && p2_life > 0) {--p2_life; state = LED_Convert;}
		break;
		
		default:
		break;
	}
	return state;
}



// Throw actual assigning to pins
enum Update_States {Start, Display};
int Display_Life(int state) {
	switch(state) {
		case Start:
		state = Display;
		break;
		
		case Display:
		transmit_short(&PORTA, life_data);
		PORTA = (PORTA & 0x0F) | p_9to10;
		
		break;
		
		default:
		break;
	}
	return state;
}

#endif /* LIFE_BARS_H_ */
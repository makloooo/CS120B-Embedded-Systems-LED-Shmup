/*
 * Player_Input.h
 *
 * Created: 5/28/2016 12:27:20 AM
 *  Author: Mark
 */ 

#ifndef GET_INPUT_H_
#define GET_INPUT_H_

// For the old shmump
/* Format:
	B[7] = sudoku (yellow)
	B[6] = shot (p_clr)
	B[5] = start (joystick press)
	B[4] = up
	B[2] = down
	B[1] = left
	B[0] = right
*/

//enum Controls {RIGHT, LEFT, DOWN, A3_BROKEN, UP, ENTER, SHOT, KAMIKAZE};

// For the chumpass snake game
enum Controls {SHOT, RIGHT, UP, A3_BROKEN, LEFT, DOWN};

enum Input_States {Input_Start, Input_Read};
int Player_Input(int state) {
	static unsigned char i;
	
	switch(state) {
		case Input_Start:
			p1_input = 0x00;
			//p2_input = 0x00;
			state = Input_Read;
		break;
		
		case Input_Read:
		break;
		
		default:
		break;
	}
	
	switch(state) {
		case Input_Start:
		break;
		
		case Input_Read:
			p1_input = 0x00;
			//p2_input = 0x00;
			// let PORTA be p1, PORTC p2
			for (i = 0; i < 8; ++i) {
				if (!GetBit(PINA, i)) p1_input = SetBit(p1_input, i, 1);
				//if (!GetBit(PINC, i)) p2_input = SetBit(p2_input, i, 1);
			}
			// if (!GetBit(PINA, 3)) PORTB = 0xFF;
		break;
		
		default:
		break;
	}
	return state;
}

#endif /* GET_INPUT_H_ */
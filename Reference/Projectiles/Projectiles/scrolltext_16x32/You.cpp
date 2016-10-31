#include "You.h"

You::You(byte num, byte _x, byte _y) {
	x = _x;
	y = _y;
	
	core_color = (num == 1) ? BLUE : GREEN; // SAVES SPACE
	
	frame = 0;
	life = 10;
}

void You::Move() {
	if (usart.Has_Input(UP) && y > 0) --y;
	if (usart.Has_Input(DOWN) && y < 31) ++y;
	if (usart.Has_Input(LEFT) && x > 0) --x;
	if (usart.Has_Input(RIGHT) && x < 31) ++x;
}

void You::Draw() {
	static uint8_t cnt = 0;
	switch (state) {
		case Pl_Normal:
			draw_panel(x, y, frame, 3);
			matrix.drawPixel(x, y, return_color(core_color));
		break;
		
		case Pl_Invincible:
			if (frame % 20 < 10) {
				draw_panel(x, y, cnt, 3);
				matrix.drawPixel(x, y, return_color(core_color));
			}
			else if (frame % 20 >= 10); // nothing or something
		break;
		
		case Pl_Explode:
			draw_explosion_l(x, y, frame, 3, core_color);
		break;
		
		default:
		break;
	}
}

Pl_States You::Get_State() {
	return state;
}

byte You::Get_Life() {
	return life;
}

bool You::Compare_Coordinates(byte obj_x, byte obj_y) {
	return (x == obj_x && y == obj_y);
}

void You::Receieve_Damage() {
	if (state != Pl_Normal) return;
	--life;
	//if (core_color == BLUE) 
	usart.Signal_Event(P1_HIT);
	//else if (core_color == GREEN) usart.Signal_Event(P2_HIT);
	if (life > 0) {
		frame = 0;
		state = Pl_Invincible;
	}
	else {
		frame = 0;
		state = Pl_Explode;
	}
}

void You::Tick() {
	switch (state) {
		case Pl_Start:
			if (usart.Has_Signal(START_GAME)) {
				state = Pl_Normal;
			}
		break;
		
		case Pl_Normal:
			// Transitions happen in Recieve Damage
		break;
		
		case Pl_Invincible:
			state = (frame++ >= 60) ? Pl_Normal : Pl_Invincible;
		break;
		
		case Pl_Explode:
		// No coming back from here.
		break;
		
		default:
		break;
	}
	
	switch (state) {
		case Pl_Start:
		break;
		
		case Pl_Normal:
		Move();
		Draw();
		break;
		
		case Pl_Invincible:
		Move();
		Draw();
		break;
		
		case Pl_Explode:
		Draw();
		usart.Signal_Event(LOSE);
		break;
		
		default:
		break;
	}
}

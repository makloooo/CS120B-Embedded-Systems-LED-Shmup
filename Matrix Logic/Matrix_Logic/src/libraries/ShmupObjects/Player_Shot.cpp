#include "Player_Shot.h"

PlayerShot::PlayerShot() {
	active = false;
	state = PS_Exit;
}

void PlayerShot::create(byte _x, byte _y, byte _xv, byte _yv) {
	x = _x;
	y = _y;
	x_vel = _xv;
	y_vel = _yv;
	
	active = true;
	
	state = PS_Start;
}

void PlayerShot::move() {
	x_orig = x;
	y_orig = y;
	
	x += x_vel;
	y += y_vel;
}

bool PlayerShot::collision_check() {
	// collision with others handled in their own classes
	// collision with screen edges;
	if (x <= 0 || x >= STG_WIDTH) return true;
	if (y <= 0 || y >= STG_HEIGHT) return true;
}

void PlayerShot::draw() {
	// draw 1st
	Send_To_Matrix(this);
}

void PlayerShot::Tick() {
	static bool hit;
	
	switch(state) {
		case PS_Start:
			hit = false;
			state = PS_Update;
		break;
		
		case PS_Update:
			if (hit) { 
				state = PS_Exit;
				active = false;
			}
		break;
		
		case PS_Exit:
			if (active) state = PS_Start;
		break;
		
		default:
		break;
	}
	switch(state) {
		case PS_Start:
		break;
		
		case PS_Update:
			move();
			hit = collision_check();
			draw(); // might wanna draw here, as p bullets have lower layer prio than others
		break;
		
		case PS_Exit:
			// deactivate bullet
		break;
		
		default:
		break;
	}
}
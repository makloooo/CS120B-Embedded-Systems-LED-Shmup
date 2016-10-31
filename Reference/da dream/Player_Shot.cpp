#include "Player_Shot.h"

PlayerShot::PlayerShot(byte _x, byte _y) {
	x = _x;
	y = _y;
	
	x_orig = _x;
	y_orig = _y;
	
	x_vel = 0;
	y_vel = -3;
	
	index = pl_bullets.size()-1;
	
	state = PS_Start;
}

PlayerShot::PlayerShot(byte _x, byte _y, byte _xv, byte _yv) {
	x = _x;
	y = _y;
	
	x_orig = _x;
	y_orig = _y;
	
	x_vel = _xv;
	y_vel = _yv;
	
	index = pl_bullets.size()-1;
	
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
	matrix.drawLine(x_orig, y_orig, x, y, Colors[YELLOW]);
}

void PlayerShot::Tick() {
	static bool hit;
	
	switch(state) {
		case PS_Start:
			hit = false;
			state = PS_Update;
		break;
		
		case PS_Update:
			state = (hit) ? PS_Exit : state;
		break;
		
		case PS_Exit:
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
			// manage linked list before deleting
			for (int i = index+1; i < pl_bullets.size(); ++i) --pl_bullets.get(i)->index;
			pl_bullets.remove(index);
			delete this; // oh god
		break;
		
		default:
		break;
	}
}
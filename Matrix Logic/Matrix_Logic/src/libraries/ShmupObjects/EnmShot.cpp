#include "EnmShot.h"

bool check_hit(byte _x, byte _y) {
	if (_x == p1.x && _y == p1.y) {
		bitWrite(game_event, P1_HIT, HIGH);
		return true;
	}
	if (_x == p2.x && _y == p2.y) {
		bitWrite(game_event, P2_HIT, HIGH);
		return true;
	}
}

EnmShot::EnmShot() {
	active = false;
	state = ES_Exit;
}

void EnmShot::create(E_Types _type, byte _x, byte _y, byte _xv, byte _yv) {
	x = _x;
	y = _y;
	
	x_vel = _xv;
	y_vel = _yv;
	
	type = _type;
	
	state = ES_Start;
	active = true;
}

void EnmShot::move() {
	x += x_vel;
	y += y_vel;
}

void EnmShot::draw() {
	Send_To_Matrix(this);
}

// E_Shot_States {ES_Start, ES_Update, ES_Exit};
void EnmShot::Tick() {
	switch(state) {
		case ES_Start:
		hit = false;
		state = ES_Update;
		break;
		
		case ES_Update:
		if (hit) {
			active = false;
			state = ES_Exit;
		}
		break;
		
		case ES_Exit:
			if (active) state = ES_Start;
		break;
		
		default:
		break;
	}
	switch(state) {
		case ES_Start:
		break;
		
		case ES_Update:
		move();
		hit = collision_check();
		draw(); // might wanna draw here, as p bullets have lower layer prio than others
		break;
		
		case ES_Exit:
			// idle
		break;
		
		default:
		break;
	}
}

bool EnmShot::collision_check() {
	switch (type) {
		case DOT:
			return dot_check();
		break;
		
		case LASER:
			return laser_check();
		break;
		
		case BALL:
			return ball_check();
		break;
		
		default:
		break;
	}
}

bool EnmShot::dot_check() {
	if (x == p1.x && y == p1.y) {
		bitWrite(game_event, P1_HIT, HIGH);
		return true;
	}
	if (x == p2.x && y == p2.y) {
		bitWrite(game_event, P2_HIT, HIGH);
		return true;
	}
	// collision with screen edges;
	if (x <= 0 || x >= STG_WIDTH) return true;
	if (y <= 0 || y >= STG_HEIGHT) return true;
	return false;
}

bool EnmShot::laser_check() {
	byte x0 = x-x_vel;
	byte y0 = y-y_vel;
	byte x1 = x;
	byte y1 = y;
	
	byte steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		_swap_int8_t(x0, y0);
		_swap_int8_t(x1, y1);
	}

	if (x0 > x1) {
		_swap_int8_t(x0, x1);
		_swap_int8_t(y0, y1);
	}

	byte dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	byte err = dx / 2;
	byte ystep;

	if (y0 < y1) {
		ystep = 1;
		} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			if (check_hit(y0, x0)) return true;
			} else {
			if (check_hit(x0, y0)) return true;
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
	if (x-x_vel <= 0 || x-x_vel >= STG_WIDTH) return true;
	if (y-y_vel <= 0 || y-y_vel >= STG_HEIGHT) return true;
	return false;
}

bool EnmShot::ball_check() {
	byte x0 = x;
	byte y0 = y;
	byte r = 5;
	
	byte f = 1 - r;
	byte ddF_x = 1;
	byte ddF_y = -2 * r;
	byte x = 0;
	byte y = r;

	if (check_hit(x0  , y0+r)) return true;
	if (check_hit(x0  , y0-r)) return true;
	if (check_hit(x0+r, y0  )) return true;
	if (check_hit(x0-r, y0  )) return true;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (check_hit(x0 + x, y0 + y)) return true;
		if (check_hit(x0 - x, y0 + y)) return true;
		if (check_hit(x0 + x, y0 - y)) return true;
		if (check_hit(x0 - x, y0 - y)) return true;
		if (check_hit(x0 + y, y0 + x)) return true;
		if (check_hit(x0 - y, y0 + x)) return true;
		if (check_hit(x0 + y, y0 - x)) return true;
		if (check_hit(x0 - y, y0 - x)) return true;
	}
	if (x-x_vel <= 0 || x-x_vel >= STG_WIDTH) x_vel *= -1;
	if (y-y_vel <= 0 || y-y_vel >= STG_HEIGHT) return true;
	return false;
}
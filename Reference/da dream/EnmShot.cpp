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

EnmShot::EnmShot(byte _x, byte _y, byte xv, byte yv) {
	x = _x;
	y = _y;
	
	x_vel = xv;
	y_vel = yv;
	
	index = enm_bullets.size()-1;
	
	state = ES_Start;
}

void EnmShot::move() {
	x += x_vel;
	y += y_vel;
}

// E_Shot_States {ES_Start, ES_Update, ES_Exit};
void EnmShot::Tick() {
	switch(state) {
		case ES_Start:
		hit = false;
		state = ES_Update;
		break;
		
		case ES_Update:
		state = (hit) ? ES_Exit : state;
		break;
		
		case ES_Exit:
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
		// manage linked list before deleting
		for (int i = index+1; i < enm_bullets.size(); ++i) --enm_bullets.get(i)->index;
		enm_bullets.remove(index);
		delete this; // oh god
		break;
		
		default:
		break;
	}
}

bool EnmDot::collision_check() {
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
}

void EnmDot::draw() {
	matrix.drawPixel(x, y, Colors[RED]);
}

bool EnmLaser::collision_check() {
	byte x0 = x-x_vel;
	byte y0 = y-y_vel;
	byte x1 = x;
	byte y1 = y;
	
	int8_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		_swap_int8_t(x0, y0);
		_swap_int8_t(x1, y1);
	}

	if (x0 > x1) {
		_swap_int8_t(x0, x1);
		_swap_int8_t(y0, y1);
	}

	int8_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int8_t err = dx / 2;
	int8_t ystep;

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
}

void EnmLaser::draw() {
	matrix.drawLine(x, y, x-x_vel, y-y_vel, Colors[ORANGE]);
}

bool EnmBall::collision_check() {
	byte x0 = x;
	byte y0 = y;
	byte r = 5;
	
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

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
}

void EnmBall::draw() {
	matrix.drawCircle(x, y, 5, Colors[PURPLE]);
}
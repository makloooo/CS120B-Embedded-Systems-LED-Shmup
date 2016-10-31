#include "Projectiles.h"

void Projectile::Tick() {
	switch (state) {
		case Proj_Start:
		state = Proj_Inactive;
		break;
		
		case Proj_Inactive:
		// Inactivity to Activity handled by external functions.
		break;
		
		case Proj_Active:
		// Activity to Inactivity handled by external functions.
		break;
	}
	
	switch (state) {
		case Proj_Start:
		break;
		
		case Proj_Inactive:
		break;
		
		case Proj_Active:
			Move();
			Draw();
			if (Collision_Check(1)) player.Receieve_Damage();
		break;
	}
}

Proj_States Projectile::Get_State()	{
	return state;
}

void Laser::Deactivate() {
	matrix.drawLine(x, y, vx, vy, return_color(clr));
	if (frame <= time + 4) state = Proj_Inactive;
}

/*
Ball::Ball() {
	state = Proj_Start;
}

void Ball::Move() {
	x += vx;
	y += vy;
	
	if((x <= 0 && vx < 0) || (x >= (matrix.width() - 1) && vx > 0)) vx *= -1;
	if((y <= 0 && vy < 0) || (y >= (matrix.height() - 1) && vy > 0)) vy *= -1;
}

void Ball::Draw() {
	matrix.fillCircle(x, y, r, matrix.Color333(0, 0, 1)); // Drawing
}

void Ball::Create(byte _x, byte _y, byte _vx, byte _vy, byte _r) {
	x = _x;
	y = _y;
	vx = _vx;
	vy = _vy;
	
	r = _r;
	
	state = Proj_Active;
}

bool Ball::Collision_Check() {
	int8_t f = 1 - r;
	int8_t ddF_x = 1;
	int8_t ddF_y = -2 * r;
	int8_t x = 0;
	int8_t y = r;

	if(player.Compare_Coordinates(this->x  , this->y+r)) return true;
	if(player.Compare_Coordinates(this->x  , this->y-r)) return true;
	if(player.Compare_Coordinates(this->x+r, this->y  )) return true;
	if(player.Compare_Coordinates(this->x-r, this->y  )) return true;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if(player.Compare_Coordinates(this->x + x, this->y + y)) return true;
		if(player.Compare_Coordinates(this->x - x, this->y + y)) return true;
		if(player.Compare_Coordinates(this->x + x, this->y - y)) return true;
		if(player.Compare_Coordinates(this->x - x, this->y - y)) return true;
		if(player.Compare_Coordinates(this->x + y, this->y + x)) return true;
		if(player.Compare_Coordinates(this->x - y, this->y + x)) return true;
		if(player.Compare_Coordinates(this->x + y, this->y - x)) return true;
		if(player.Compare_Coordinates(this->x - y, this->y - x)) return true;
	}
}

Dot::Dot() {
	state = Proj_Start;
}

void Dot::Move() {
	x += vx;
	y += vy;
	
	if((x <= 0) || (x >= (matrix.width() - 1))) vx *= -1;
	if((y <= 0) || (y >= (matrix.height() - 1))) vy *= -1;
}

void Dot::Draw() {
	matrix.drawPixel(x,y, matrix.Color333(0, 2, 2));
}

void Dot::Create(byte _x, byte _y, byte _vx, byte _vy) {
	x = _x;
	y = _y;
	vx = _vx;
	vy = _vy;
	
	state = Proj_Active;
}

bool Dot::Collision_Check() {
	return player.Compare_Coordinates(x, y);
}
*/

Laser::Laser() {
	state = Proj_Start;
}

bool Laser::Create(int8_t _x, int8_t _y, int8_t _x0, int8_t _y0, byte _thick, uint16_t _time, Colors c) {
	if (state != Proj_Inactive) return false;
	
	x = _x;
	y = _y;
	vx = _x0;
	vy = _y0;
	
	clr = c;
	
	time = _time;
	frame = 0;
	
	thick = _thick;
	
	state = Proj_Warn;
	
	return true;
}

void Laser::Start_Rotate() {
	state = Proj_Rotate;
}

void Laser::Shift_X0(int8_t offs) {
	x += offs;
}
void Laser::Shift_X1(int8_t offs) {
	vx += offs;
}
void Laser::Shift_Y0(int8_t offs) {
	y += offs;
}
void Laser::Shift_Y1(int8_t offs) {
	vy += offs;
}

uint16_t Laser::Get_Time() {
	return time;
}

bool Laser::Collision_Check(byte num) {
	int16_t x0 = x;
	int16_t y0 = y;
	int16_t x1 = vx;
	int16_t y1 = vy;
	
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		_swap_int16_t(x0, y0);
		_swap_int16_t(x1, y1);
	}

	if (x0 > x1) {
		_swap_int16_t(x0, x1);
		_swap_int16_t(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
		} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			if (num == 1) {
				if (player.Compare_Coordinates(y0, x0)) return true;
			}
			else if (num == 2) {
				//if (player2.Compare_Coordinates(y0, x0)) return true;
			}
		}
		else {
			if (num == 1) {
				if (player.Compare_Coordinates(x0, y0)) return true;
			}
			else if (num == 2) {
				//if (player2.Compare_Coordinates(x0, y0)) return true;
			}
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
	return false;
}

void Laser::Draw() {
	if (state == Proj_Warn) {
		if (frame <= 71) matrix.drawLine(x, y, vx, vy, matrix.Color333(1, 1, 1));
		else  matrix.drawLine(x, y, vx, vy, return_color(clr));
	}
	else if (state == Proj_Lethal || state == Proj_Rotate) {
		int16_t steep = abs(vy - y) > abs(vx - x);
		for (int8_t i = -thick; i <= thick; ++i) {
			if (!steep) matrix.drawLine(x, y+i, vx, vy+i, return_color(clr));
			else matrix.drawLine(x+i, y, vx+i, vy, return_color(clr));
		}
		if (frame % 2 == 0 && !(frame % 4 == 0)) ++thick;
		else if (frame % 4 == 0) --thick;
	}
}

void Laser::Tick() {
	switch (state) {
		case Proj_Start:
			state = Proj_Inactive;
		break;
		case Proj_Warn:
			if (frame % 4 == 0) state = Proj_Active;
			
			if (frame > 75) {
				frame = 0;
				state = Proj_Lethal;
			}
		break;
		case Proj_Active: // Actually no drawing of warn
			if (frame % 4 == 0) state = Proj_Warn;
		break;
		case Proj_Lethal:
			if (frame >= time) Deactivate();
		break;
		case Proj_Inactive:
			// Activation same thing
		break;
		case Proj_Rotate:
			if (frame >= time) Deactivate();
			// Also handled in external function
		break;
		default:
		break;
	}
	switch (state) {
		case Proj_Start:
		break;
		case Proj_Inactive:
		break;
		
		case Proj_Warn:
		++frame;
		Draw(); 
		break;
		
		case Proj_Active:
		++frame; 
		break;
		
		case Proj_Lethal:
		++frame;
		Draw(); 
		if (player.Get_State() == Pl_Normal) {
			if (Collision_Check(1)) player.Receieve_Damage();
		}
// 		if (player2.Get_State() == Pl_Normal) {
// 			if (Collision_Check(2)) player2.Receieve_Damage();
// 		}
		break;
		
		case Proj_Rotate:
		// Also handled in external function
		++frame;
		Draw();
		if (player.Get_State() == Pl_Normal) {
			if (Collision_Check(1)) player.Receieve_Damage();
		}
		
		if (frame % 5 == 0) {
			if (x < 32 && y <= 0) Shift_X0(1); // Top Edge Shifting Right
			else if (x >= 32 && y < 32) Shift_Y0(1); // Right Edge Shifting Down
			else if (x > 0 && y >= 32) Shift_X0(-1); // Bottom Edge Shifting Left
			else if (x <= 0 && y > 0) Shift_Y0(-1); // Left Edge Shifting Up
		
			if (vx < 32 && vy <= 0) Shift_X1(1); // Top Edge Shifting Right
			else if (vx >= 32 && vy < 32) Shift_Y1(1); // Right Edge Shifting Down
			else if (vx > 0 && vy >= 32) Shift_X1(-1); // Bottom Edge Shifting Left
			else if (vx <= 0 && vy > 0) Shift_Y1(-1); // Left Edge Shifting Up
		}
		break;
		
		
		default:
		break;
	}
	//pixelDebug(4, 1, matrix.Color333(0, 0, 1));
}
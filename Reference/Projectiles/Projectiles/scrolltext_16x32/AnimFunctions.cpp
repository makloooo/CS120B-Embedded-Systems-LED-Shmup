#include "AnimFunctions.h"

void draw_ship(byte& x, byte& y, Colors& clr) {
	for (byte i = 0; i < 4; ++i) {
		for (byte j = 0; j < 3; ++j) {
			if(pgm_read_byte(&(ship[i][j]))) {
				matrix.drawPixel(x+j-1, y+i-2, matrix.Color333(1, 1, 1));
			}
		}
	}
	matrix.drawPixel(x, y, return_color(clr));
}

void draw_cross(byte& x, byte& y, byte& frame, Colors& clr) {
	for (byte i = 0; i < 3; ++i) {
		for (byte j = 0; j < 3; ++j) {
			if(pgm_read_byte(&(enm_cross[frame][i][j]))) {
				matrix.drawPixel(x+j-1, y+i-1, return_color(clr));
			}
		}
	}
}

void draw_tracer(byte& x, byte& y, byte& frame, byte frm_delay) {
	if (++frame >= 8*frm_delay) frame = 0;
	for (byte i = 0; i < 3; ++i) {
		for (byte j = 0; j < 3; ++j) {
			if(pgm_read_byte(&(enm_tracer[frame/frm_delay][i][j]))) {
				matrix.drawPixel(x+j-1, y+i-1, matrix.Color333(1, 1, 1));
			}
		}
	}
}

void draw_panel(byte& x, byte& y, byte& frame, byte frm_delay) {
	if (++frame >= 4*frm_delay) frame = 0;
	for (byte i = 0; i < 5; ++i) {
		for (byte j = 0; j < 5; ++j) {
			if(pgm_read_byte(&(enm_panel[frame/frm_delay][i][j]))) {
				matrix.drawPixel(x+j-2, y+i-2, matrix.Color333(7, 7, 7));
			}
		}
	}
}

void draw_eyeball(byte& x, byte& y, byte& frame, byte frm_delay) {
	if (++frame >= 2*frm_delay) frame = 0;
	for (byte i = 0; i < 11; ++i) {
		for (byte j = 0; j < 11; ++j) {
			if(pgm_read_byte(&(eyeball[frame/frm_delay][i][j]))) {
				matrix.drawPixel(x+j-5, y+i-5, matrix.Color333(1, 1, 1));
			}
		}
	}
}

void draw_explosion_l(byte& x, byte& y, byte& frame, byte frm_delay, Colors& clr) {
	if (frame >= 9*frm_delay-1) return;
	++frame;
	for (byte i = 0; i < 5; ++i) {
		for (byte j = 0; j < 5; ++j) {
			if(pgm_read_byte(&(bigger_explode[frame/frm_delay][i][j]))) {
				matrix.drawPixel(x+j-2, y+i-2, matrix.Color333(5, 5, 5));
			}
		}
	}
}
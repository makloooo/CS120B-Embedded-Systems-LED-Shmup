#include "EnmTypes.h"

void Enm_Cross::shoot() {
	byte xv, yv = 0;
	while (xv == 0 && yv == 0) { // ensuring no stationary bullets
		xv = random(-2, 2);
		yv = random(-2, 2);
	}
	enm_bullets.add(new EnmDot(x, y, xv, yv)); // simple
	xv, yv = 0;
	while (xv == 0 && yv == 0) {
		xv = random(-2, 2);
		yv = random(-2, 2);
	}
	enm_bullets.add(new EnmDot(x, y, xv, yv));
	xv, yv = 0;
	while (xv == 0 && yv == 0) {
		xv = random(-2, 2);
		yv = random(-2, 2);
	}
	enm_bullets.add(new EnmDot(x, y, xv, yv));
}

void Enm_Cross::draw() {
	if (frame >= 2) frame = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if(enm_cross[frame][i][j]) matrix.drawPixel(x+j-1, y+i-1, Colors[WHITE]);
		}
	}
}

void Enm_Line::shoot() {
	enm_bullets.add(new EnmDot(x-1, y, -1, 2)); // ugly
	enm_bullets.add(new EnmDot(x, y, 0, 2));
	enm_bullets.add(new EnmDot(x+1, y, 1, 2));
}

void Enm_Line::draw() {
	if (frame >= 4) frame = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if(enm_line[frame][i][j]) matrix.drawPixel(x+j-1, y+i-1, Colors[WHITE]);
		}
	}
}

void Enm_Tracer::shoot() {
	// fast firing single lasers
	enm_bullets.add(new EnmLaser(x, y, random(-2, 2), random(1, 3)));
}

void Enm_Tracer::draw() {
	if (frame >= 8) frame = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if(enm_tracer[frame][i][j]) matrix.drawPixel(x+j-1, y+i-1, Colors[WHITE]);
		}
	}
}

void Enm_Panel::shoot() {
	enm_bullets.add(new EnmBall(x, y, -3, 1));
	enm_bullets.add(new EnmBall(x, y, 3, 1));

	enm_bullets.add(new EnmLaser(x, y, random(-3, -2), 2));
	enm_bullets.add(new EnmLaser(x, y, random(-1, 1), 2));
	enm_bullets.add(new EnmLaser(x, y, random(2, 3), 2));
}

void Enm_Panel::draw() {
	if (frame >= 8) frame = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if(enm_panel[frame][i][j]) matrix.drawPixel(x+j-2, y+i-2, Colors[WHITE]);
		}
	}
}

void Enm_Panel::anim_explode() {
	if (frame >= 9) return;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if(bigger_explode[frame][i][j]) matrix.drawPixel(x+j-2, y+i-2, Colors[WHITE]);
		}
	}
}
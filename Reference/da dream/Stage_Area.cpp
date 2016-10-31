#include "Stage_Area.h"

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

StageArea::StageArea() {
	clearMatrix();
}

byte StageArea::getSegment(byte r, byte c) {
	return matrix_data[r][c];
}

void StageArea::writeSegment(byte r, byte c, byte seq) {
	matrix_data[r][c] = seq;
	return;
}

void StageArea::clearMatrix() {
	for (byte i = 0; i < DATA_H; ++i) {
		for (byte j = 0; j < DATA_W; ++j) {
			matrix_data[i][j] = 0;
		}
	}
}

void StageArea::placePixel(byte x, byte y) {
	byte seg = getSegment(x/8, y);
	bitWrite(seg, 7-(x%8), HIGH);
	writeSegment(x, y, seg);
}

void StageArea::placeLine(byte x0, byte y0, byte x1, byte y1) {
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
		  placePixel(y0, x0);
		  } else {
		  placePixel(x0, y0);
	  }
	  err -= dy;
	  if (err < 0) {
		  y0 += ystep;
		  err += dx;
	  }
  }
}

void StageArea::placeCircle(byte x0, byte y0, byte r) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  placePixel(x0  , y0+r);
  placePixel(x0  , y0-r);
  placePixel(x0+r, y0  );
  placePixel(x0-r, y0  );

  while (x<y) {
	  if (f >= 0) {
		  y--;
		  ddF_y += 2;
		  f += ddF_y;
	  }
	  x++;
	  ddF_x += 2;
	  f += ddF_x;

	  placePixel(x0 + x, y0 + y);
	  placePixel(x0 - x, y0 + y);
	  placePixel(x0 + x, y0 - y);
	  placePixel(x0 - x, y0 - y);
	  placePixel(x0 + y, y0 + x);
	  placePixel(x0 - y, y0 + x);
	  placePixel(x0 + y, y0 - x);
	  placePixel(x0 - y, y0 - x);
  }
}
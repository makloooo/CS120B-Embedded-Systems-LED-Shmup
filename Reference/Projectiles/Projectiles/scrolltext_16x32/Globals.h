#ifndef GLOBALS_H_
#define GLOBALS_H_
#include <Arduino.h>

#include <Adafruit_GFX.h>   
#include <RGBmatrixPanel.h> 

#include <MsTimer2.h>

#include <math.h>

#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

#define CLK 8 
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

extern RGBmatrixPanel matrix;

enum PROGMEM Events {START_GAME, P1_HIT, P2_HIT, LOSE, WIN, ACTION};
enum PROGMEM Controls {SHOT, RIGHT, UP, BROKEN, LEFT, DOWN};
	
enum PROGMEM Colors {RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE};
#include "Bitmaps.h"
#include "AnimFunctions.h"

#define MS_PER_TICK	25
#define DEBUG_SEC	1000/MS_PER_TICK	

inline void getFreeRam() {
	extern int __heap_start, *__brkval;
	uint16_t v;

	v = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);

	Serial.print(F("Free RAM: "));
	Serial.print(v, DEC);
	Serial.println(F(" bytes"));
}

inline void pixelDebug(byte x, byte y, uint16_t color) {
	matrix.drawPixel(x, y, color);
}

inline uint16_t return_color(Colors c) {
	switch (c) {
		case RED:
		return matrix.Color333(1, 0, 0);
		case ORANGE:
		return matrix.Color333(2, 1, 0);
		case YELLOW:
		return matrix.Color333(1, 1, 0);
		case GREEN:
		return matrix.Color333(0, 1, 0);
		case CYAN:
		return matrix.Color333(0, 1, 1);
		case BLUE:
		return matrix.Color333(0, 0, 1);
		case PURPLE:
		return matrix.Color333(1, 0, 1);
	}
}
#endif /* GLOBALS_H_ */
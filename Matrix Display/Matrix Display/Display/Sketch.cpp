/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
//#include "Globals.h"
/*End of auto generated code by Atmel studio */
#include <gamma.h>
#include <RGBmatrixPanel.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <avr/pgmspace.h>

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

#include "Bitmaps.h"

enum Graphic {P1, P2, PL_SHOT, ENM_CROSS, ENM_LINE, ENM_TRACER, ENM_PANEL,
			  ES_DOT, ES_LASER, ES_BALL, BS_EYE, ANIM_EXPLODE, ANIM_BIG_EXPLODE};
struct MatrixData {
	byte start;
	Graphic sprite;
	byte frame;
	byte x;
	byte y;
	byte x0;
	byte y0;
	byte end;
};
MatrixData data;

//#include <Wire.h>
byte usartData;

byte objData = 0x00;
void Draw_Object(MatrixData*);
void Store_Data();

#include <MsTimer2.h>

byte debug = 0x00;

bool UpdateFlag = false;
void Tick() {
	UpdateFlag = true;
	++debug;
}

enum PROGMEM clr_index {RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE};
uint16_t Colors[8];

void receiveEvent(int);

void setup() {
	// Slave Reader
	//Wire.begin(8);
	//Wire.onReceive(receiveEvent);
	
	Serial.begin(9600);
	while (!Serial);
	
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	
	MsTimer2::set(50, Tick);
	MsTimer2::start();
	
	matrix.begin();
	
	Colors[RED]		= matrix.Color333(3, 0, 0); // red
	Colors[ORANGE]	= matrix.Color333(2, 1, 0); // orange
	Colors[YELLOW]	= matrix.Color333(3, 3, 0); // yellow
	Colors[GREEN]	= matrix.Color333(0, 3, 0); // green
	Colors[CYAN]	= matrix.Color333(0, 3, 3); // cyan
	Colors[BLUE]	= matrix.Color333(0, 0, 3); // blue
	Colors[PURPLE]	= matrix.Color333(3, 0, 3); // purple
	Colors[WHITE]	= matrix.Color333(3, 3, 3);  // white
	
	matrix.fillScreen(0);
	
	// matrix.drawPixel(15, 15, Colors[WHITE]);
	
	for (byte i = 0; i < 4; ++i) {
		for (byte j = 0; j < 3; ++j) {
			if(pgm_read_byte(&(ship[i][j]))) matrix.drawPixel(14+j, 13+i, Colors[WHITE]);
		}
	}
	matrix.drawPixel(15, 15, Colors[BLUE]);
}

Graphic sprites[13] = {P1, P2, PL_SHOT, ENM_CROSS, ENM_LINE, ENM_TRACER, ENM_PANEL,
					   ES_DOT, ES_LASER, ES_BALL, BS_EYE, ANIM_EXPLODE, ANIM_BIG_EXPLODE};
// enum Type {GRAPHIC, FRAME, POSX, POSY, POSX0, POSY0} dataType = GRAPHIC;
void loop() {
	//byte spi;
	if (UpdateFlag) {
		if (debug >= 20) {
			static boolean output = HIGH;
			
			digitalWrite(LED_BUILTIN, output);
			output = !output;
			debug = 0;
		}
		//matrix.fillScreen(0);
		UpdateFlag = false;
		++debug;
	}
}

/*
void receiveEvent(int numBytes) {
	//if (numBytes == 8) {
		data.start = Wire.read();
		data.sprite = sprites[Wire.read()];
		data.frame = Wire.read();
		data.x = Wire.read();
		data.y = Wire.read();
		data.x0 = Wire.read();
		data.y0 = Wire.read();
		data.end = Wire.read();
	//}
	//else Serial.println(F("Unexpected number of bytes."));
	//Draw_Object(&data);
}
*/

void Draw_Player(MatrixData* obj, byte num) {
	uint16_t coreColor = (num == 1) ? Colors[RED] : Colors[GREEN];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 3; ++j) {
			if(pgm_read_byte(&(ship[i][j]))) matrix.drawPixel(obj->x+j-1, obj->y+i-2, Colors[WHITE]);
		}
	}
	matrix.drawPixel(obj->x, obj->y, coreColor);
}

void Draw_Object(MatrixData* obj) {
	static byte k = 0;
	switch (obj->sprite) {
		case P1:
			Draw_Player(obj, 1); break;
		case P2:
			Draw_Player(obj, 2); break;
		case PL_SHOT:
			matrix.drawLine(obj->x, obj->y, obj->x0, obj->y0, Colors[ORANGE]);
			break;
		case ENM_CROSS:
			if (obj->frame >= 2) obj->frame = 0;
			for (byte i = 0; i < 3; ++i) {
				for (byte j = 0; j < 3; ++j) {
					if(pgm_read_byte(&(enm_cross[obj->frame][i][j]))) {
						matrix.drawPixel(obj->x+j-1, obj->y+i-1, Colors[WHITE]);
					}
				}
			}
		break;
		case ENM_LINE:
			if (obj->frame >= 4) obj->frame = 0;
			for (byte i = 0; i < 3; ++i) {
				for (byte j = 0; j < 3; ++j) {
					if(pgm_read_byte(&(enm_line[obj->frame][i][j]))) {
						matrix.drawPixel(obj->x+j-1, obj->y+i-1, Colors[WHITE]); 
					}
				}
			}
		break;
		case ENM_TRACER:
			if (obj->frame >= 8) obj->frame = 0;
			for (byte i = 0; i < 3; ++i) {
				for (byte j = 0; j < 3; ++j) {
					if(pgm_read_byte(&(enm_tracer[obj->frame][i][j]))) { 
						matrix.drawPixel(obj->x+j-1, obj->y+i-1, Colors[WHITE]);
					}
				}
			}
		break;
		case ENM_PANEL:
			if (obj->frame >= 8) obj->frame = 0;
			for (byte i = 0; i < 5; ++i) {
				for (byte j = 0; j < 5; ++j) {
					if(pgm_read_byte(&(enm_panel[obj->frame][i][j]))) {
						matrix.drawPixel(obj->x+j-2, obj->y+i-2, Colors[WHITE]);
					}
				}
			}
		break;
		case ES_DOT:
			matrix.drawPixel(obj->x, obj->y, Colors[BLUE]); break;
		case ES_LASER:
			matrix.drawLine(obj->x, obj->y, obj->x0, obj->y0, Colors[CYAN]); break;
		case ES_BALL:
			matrix.drawCircle(obj->x, obj->y, 5, Colors[PURPLE]); break;
		case BS_EYE:
			if (obj->frame == 2) obj->frame = 0;
			else if (obj->frame == 3 && obj->x0 >= 75) ++k; 
			else obj->frame = 0;
			for (byte i = k; i < 11; ++i) {
				for (byte j = 0; j < 11; ++j) {
					if(pgm_read_byte(&(eyeball[obj->frame][i][j]))) {
						matrix.drawPixel(obj->x+j-5, obj->y+i-5, Colors[WHITE]);
					}
				}
			}
			matrix.drawPixel(obj->x, obj->y, Colors[BLUE]);
		break;
		case ANIM_EXPLODE:
			if (obj->frame >= 3) return;
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					if(pgm_read_byte(&(explode[obj->frame][i][j]))) {
						matrix.drawPixel(obj->x+j-1, obj->y+i-1, Colors[WHITE]);
					}
				}
			}
		break;
		case ANIM_BIG_EXPLODE:
			if (obj->frame >= 9) return;
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					if(pgm_read_byte(&(bigger_explode[obj->frame][i][j]))) {
						matrix.drawPixel(obj->x+j-2, obj->y+i-2, Colors[WHITE]);
					}
				}
			}
		break;
		default:
		break;
	}
}
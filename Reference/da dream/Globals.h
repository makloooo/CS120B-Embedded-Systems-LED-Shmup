#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <Arduino.h>

#include <LinkedList.h>

#include <math.h>
#include <gamma.h>
#include <RGBmatrixPanel.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>



#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

static RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
#define SEGMENT_LEN	8
#define STG_WIDTH	32
#define STG_HEIGHT	32

#define DATA_W		STG_WIDTH/SEGMENT_LEN
#define DATA_H		STG_HEIGHT

#ifndef _swap_int8_t
#define _swap_int8_t(a, b) { int8_t t = a; a = b; b = t; }
#endif

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

enum PROGMEM Events {START_GAME, P1_HIT, P1_EXTEND, P2_HIT, P2_EXTEND, PAUSE, WIN, BOSS_ACTION};
enum PROGMEM Controls {RIGHT, LEFT, DOWN, A3_BROKEN, UP, ENTER, SHOT, SUDOKU};

// Matrix to be sent to Display Arduino
//static StageArea display;

// Global USART Signal to send back to the UI on ATMega1284(1)
static byte game_event;

// Global USART Signals into Arduino with controller input from ATMega1284(2)
static byte p1_input;
static byte p2_input;

// Forward Declarations
class Player;
class PlayerShot;
class Enemy;
class EnmShot;
class EyeBall;

extern LinkedList<PlayerShot*> pl_bullets;
extern LinkedList<EnmShot*> enm_bullets;
extern LinkedList<Enemy*> enms;

extern Player p1;
extern Player p2;

extern EyeBall* boss;

enum PROGMEM clr_index {RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE, WHITE};

const uint16_t PROGMEM Colors[8] = {
	matrix.Color333(3, 0, 0), // red
	matrix.Color333(1, 2, 0), // orange
	matrix.Color333(3, 3, 0), // yellow
	matrix.Color333(0, 3, 0), // green
	matrix.Color333(0, 3, 3), // cyan
	matrix.Color333(0, 0, 3), // blue
	matrix.Color333(3, 0, 3), // purple
	matrix.Color333(3, 3, 3)  // white
};

// Animation data
const bool PROGMEM explode[3][3][3] = {
	{
		{0, 0, 0},
		{0, 1, 0},
		{0, 0, 0},
	},
	{
		{1, 0, 1},
		{0, 1, 0},
		{1, 0, 1},
	},
	{
		{1, 0, 1},
		{0, 0, 0},
		{1, 0, 1},
	},
};

const bool PROGMEM bigger_explode[9][5][5] = {
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 0, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 0, 1, 0, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 1, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 1, 0},
		{1, 0, 0, 0, 1}
	},
	{
		{1, 0, 0, 0, 1},
		{0, 1, 0, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0},
		{1, 0, 0, 0, 1}
	},
	{
		{1, 0, 0, 0, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 0, 0, 0, 1}
	},
};

const bool PROGMEM ship[4][3] =
{
	{0, 1, 0},
	{0, 1, 0},
	{1, 0, 1},
	{0, 1, 0}
};

const bool PROGMEM enm_cross[2][3][3] = 
{
	{
		{0, 1, 0},
		{1, 1, 1},
		{0, 1, 0},
	},
	{
		{1, 0, 1},
		{0, 1, 0},
		{1, 0, 1},
	}
};

const bool PROGMEM enm_line[4][3][3] =
{
	{
		{0, 0, 0},
		{1, 1, 1},
		{0, 0, 0},
	},
	{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
	},
	{
		{0, 0, 0},
		{1, 1, 1},
		{0, 0, 0},
	},
	{
		{0, 0, 1},
		{0, 1, 0},
		{1, 0, 0},
	}
};

const bool PROGMEM enm_tracer[8][3][3] =
{
	{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 0},
	},
	{
		{0, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
	},
	{
		{0, 0, 0},
		{0, 0, 1},
		{0, 0, 1},
	},
	{
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 0},
	},
	{
		{0, 0, 1},
		{0, 1, 0},
		{0, 0, 0},
	},
	{
		{0, 0, 0},
		{0, 1, 0},
		{1, 0, 0},
	},
	{
		{0, 0, 0},
		{1, 0, 0},
		{1, 0, 0},
	},
	{
		{1, 0, 0},
		{1, 0, 0},
		{0, 0, 0},
	},
};

const bool PROGMEM enm_panel[4][5][5] = {
	{
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1}
	},
	{
		{0, 1, 0, 0, 0},
		{0, 1, 1, 1, 1},
		{0, 1, 1, 1, 0},
		{1, 1, 1, 1, 0},
		{0, 0, 0, 1, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 1, 1, 1, 0},
		{1, 1, 1, 1, 1},
		{0, 1, 1, 1, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 0, 1, 0},
		{1, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 1},
		{0, 1, 0, 0, 0}
	}
};

const bool PROGMEM eyeball[3][11][11] = {
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
		{0 ,0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
		{0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0},
		{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
		{0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
		{1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
		{1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
		{0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0}
	},
	{
		{0,0,0,1,1,1,1,1,0,0,0},
		{0,0,1,0,0,0,0,0,1,0,0},
		{0,1,0,0,1,1,1,0,0,1,0},
		{1,0,0,1,0,1,0,1,0,0,1},
		{1,0,1,0,0,1,0,0,1,0,1},
		{1,1,0,0,0,1,0,0,0,1,1},
		{1,0,1,0,0,1,0,0,1,0,1},
		{1,0,0,1,0,1,0,1,0,0,1},
		{0,1,0,0,1,1,1,0,0,1,0},
		{0,0,1,0,0,0,0,0,1,0,0},
		{0,0,0,1,1,1,1,1,0,0,0}
	},
};
#endif /* GLOBALS_H_ */
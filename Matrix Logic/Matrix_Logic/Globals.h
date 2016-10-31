#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#include <MsTimer2.h>

#include <math.h>

#ifndef _swap_int8_t
#define _swap_int8_t(a, b) { int8_t t = a; a = b; b = t; }
#endif

#define STG_WIDTH	32
#define STG_HEIGHT	32

// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr

enum PROGMEM Events {START_GAME, P1_HIT, P1_EXTEND, P2_HIT, P2_EXTEND, PAUSE, WIN, BOSS_ACTION};
enum PROGMEM Controls {RIGHT, LEFT, DOWN, A3_BROKEN, UP, ENTER, SHOT, SUDOKU};

// Global USART Signal to send back to the UI on ATMega1284(1)
extern byte game_event;

// Global USART Signals into Arduino with controller input from ATMega1284(2)
extern byte p1_input;
extern byte p2_input;

// Forward Declarations
class Player;
class PlayerShot;
class Enemy;
class EnmShot;
class EyeBall;

#define PS_MAX	32
#define ES_MAX	64
#define ENM_MAX	8

extern byte num_PS_active;
extern PlayerShot* pl_bullets[PS_MAX];

extern byte num_ES_active;
extern EnmShot* enm_bullets[ES_MAX];

extern byte num_enm_active;
extern Enemy* enms[ENM_MAX];

extern Player p1;
extern Player p2;

extern EyeBall* boss;

extern byte debug;

enum Graphic {P1, P2, PL_SHOT, ENM_CROSS, ENM_LINE, ENM_TRACER, 
			  ENM_PANEL, ES_DOT, ES_LASER, ES_BALL, 
			  BS_EYE, ANIM_EXPLODE, ANIM_BIG_EXPLODE};
			  
// Order: GRAPHIC, FRAME, POSX, POSY, POSX0, POSY0, 0xFE
void Send_To_Matrix(Player*, byte);
void Send_To_Matrix(PlayerShot*);
void Send_To_Matrix(Enemy*);
void Send_To_Matrix(EnmShot*);
void Send_To_Matrix(EyeBall*);
void Send_To_Matrix(Graphic, byte, byte, byte); // General Graphic
#endif /* GLOBALS_H_ */
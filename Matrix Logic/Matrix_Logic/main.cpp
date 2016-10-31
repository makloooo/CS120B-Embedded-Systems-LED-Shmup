#include "Globals.h"
#include "Player.h"
#include "Enemy.h"
#include "Eyeball.h"
#include "Director.h"

byte num_PS_active = 0;
PlayerShot* pl_bullets[PS_MAX];

byte num_ES_active = 0;
EnmShot* enm_bullets[ES_MAX];

byte num_enm_active = 0;
Enemy* enms[ENM_MAX];

Player p1(1, 10);
Player p2(2, 10);

EyeBall* boss;

Director* dir = NULL;

byte game_event = 0x00;
byte p1_input = 0x00;
byte p2_input = 0x00;

byte debug = 0;

// RX (p2_input), TX (game_event)
SoftwareSerial altSerial(2, 3);

bool UpdateFlag = false;

/*
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

MatrixData d;
*/

// Each player's input will be marked by a bit
/* Format:
	B[7] = sudoku (yellow)
	B[6] = shot (p_clr)
	B[5] = start (joystick press)
	B[4] = up
	B[2] = down
	B[1] = left
	B[0] = right
*/
void recieve_signals() {
	if (Serial.available()) {
		p1_input = Serial.read();
	}
	if (altSerial.available()) {
		p2_input = altSerial.read();
	}
}

void clear_signals() {
	game_event = 0x00;
	p1_input = 0x00;
	p2_input = 0x00;
}

void Tick() {
	UpdateFlag = true;
}

void setup() {
	// These two are used for P1, P2 input
	Serial.begin(9600);
	while (!Serial);
	altSerial.begin(9600);
	while (!altSerial);
	
	MsTimer2::set(50, Tick);
	MsTimer2::start();
	
	for (byte i = 0; i < ES_MAX; ++i) {
		if (i < PS_MAX) pl_bullets[i] = new PlayerShot;
		if (i < ENM_MAX) enms[i] = new Enemy;
		enm_bullets[i] = new EnmShot;
	}
	dir = new Director;
	
	Wire.begin();
	
	clear_signals();
	return;
}

byte x = 0;

void loop() {
	if (UpdateFlag) {
		// clear_signals();
	
		// Artificially tick the display to update
		//altSerial.write(0xFF);
	
		// Get inputs from both playersS
		// recieve_signals();
	
		// debug ticker
		if (debug >= 10) {
			static boolean output = HIGH;
			digitalWrite(LED_BUILTIN, output);
			output = !output;
			debug = 0;
		} else ++debug;
		// Tick the director to update the matrix.
		// This also updates game_event as well
		dir->Tick();
		// Director sends all object data to matrix.
	
		// Send USART signal to UI Chip.
		if (game_event) {
			Serial.write(game_event);
			altSerial.write(game_event);
		}
		UpdateFlag = false;
	}
}

/* Transmission functions. */
// 	enum Graphic {P1, P2, PL_SHOT, ENM_CROSS, ENM_LINE, ENM_TRACER,
// 				  ENM_PANEL, ES_DOT, ES_LASER, ES_BALL,
// 				  BS_EYE, ANIM_EXPLODE, ANIM_BIG_EXPLODE};
void Send_To_Matrix(Player* pl, byte num) {
	++debug;
	
	Wire.beginTransmission(8);
	Wire.write('<');
	Serial.println(F("Just sent start character."));
	if (num == 1) Wire.write(P1);
	else Wire.write(P2);
	Wire.write(pl->frame);
	Wire.write(pl->x);
	Wire.write(pl->y);
	Wire.write(0);
	Wire.write(0);
	Wire.write('>');
	Wire.endTransmission();
}

void Send_To_Matrix(PlayerShot* ps) {
	/*
	altSerial.write('<'); // Start Object
	altSerial.write(PL_SHOT);
	altSerial.write(ps->x);
	altSerial.write(ps->y);
	altSerial.write(ps->x - ps->x_vel);
	altSerial.write(ps->y - ps->y_vel);
	altSerial.write('>'); // Signal to draw to buffer
	*/
	
	/*
	d.start = '<';
	d.sprite = PL_SHOT;
	d.frame = 0;
	d.x = ps->x;
	d.y = ps->y;
	d.x0 = ps->x_orig;
	d.y0 = ps->y_orig;
	d.end = '>';
	
	byte arr[sizeof(d)];
	memcpy(arr, &d, sizeof(d));
	altSerial.write(arr, sizeof(d));
	*/
}

void Send_To_Matrix(Enemy* enm) {
	altSerial.write('<'); // Start Object
	Graphic graphic;
	switch(enm->type) {
		case CROSS:
			altSerial.write(ENM_CROSS); break;
		case LINE:
			altSerial.write(ENM_LINE); break;
		case TRACER:
			altSerial.write(ENM_TRACER); break;
		case PANEL:
			altSerial.write(ENM_PANEL); break;
		default: 
			break;
	}
	altSerial.write(enm->frame);
	altSerial.write(enm->x);
	altSerial.write(enm->y);
	altSerial.write('>'); // Signal to draw to buffer
}

void Send_To_Matrix(EnmShot* es) {
	altSerial.write('<'); // Start Object
	switch(es->type) {
		case DOT:
			altSerial.write(ES_DOT); break;
		case LASER:
			altSerial.write(ES_LASER); break;
		case BALL:
			altSerial.write(ES_BALL); break;
		default:
			break;
	}
	altSerial.write(es->x);
	altSerial.write(es->y);
	if (es->type == LASER) altSerial.write(es->x - es->x_vel); // x0
	if (es->type == LASER) altSerial.write(es->y - es->y_vel); // y0
	altSerial.write('>'); // Signal to draw to buffer
}

void Send_To_Matrix(EyeBall* boss) {
	altSerial.write(BS_EYE);
	altSerial.write(boss->frame);
	altSerial.write(boss->x);
	altSerial.write(boss->y);
	altSerial.write(boss->cnt); // using x0 as cnt
	altSerial.write(0xFE);
}

void Send_To_Matrix(Graphic anim, byte frame, byte x, byte y) {
	altSerial.write(anim);
	altSerial.write(frame);
	altSerial.write(x);
	altSerial.write(y);
}
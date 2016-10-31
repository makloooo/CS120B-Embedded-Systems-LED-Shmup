#ifndef PLAYER_H
#define PLAYER_H

#include "Globals.h"
#include "Player_Shot.h"
#include "EnmShot.h"
#include "Arduino.h"

enum PROGMEM P_States {Player_Start, Player_Update, Player_Explode, Player_Respawn, Player_Inactive, Player_Lost};
class Player {
	private:
		byte num;
		byte life;
		byte power;
		byte speed;
		
		uint16_t coreColor; // might ptr this if out of space
		
		P_States state;
		
		byte* signal;
		
		// sm data
		byte i;
		bool honor;
		bool wait;
		byte frame;
		
		void spawn();
		void shoot();
		void move();
		void extend();
		
		void draw();
		void anim_explode(byte frame);
	public:
		byte x;
		byte y;
	
		bool active;
	
		Player(byte _num, byte _life);
		
		void Tick();
};


#endif
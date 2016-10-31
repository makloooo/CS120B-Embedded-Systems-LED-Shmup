#ifndef PLAYER_SHOT_H_
#define PLAYER_SHOT_H_

#include "Globals.h"
#include "Arduino.h"

enum P_Shot_States {PS_Start, PS_Update, PS_Exit};
class PlayerShot {
	private:
		byte x_orig;
		byte y_orig;
		
		byte x_vel;
		byte y_vel;
		
		byte state;
		//byte type;
		
		void move();
		bool collision_check();
		
		void draw();
	public:
		byte x;
		byte y;
		
		byte index;
		
		PlayerShot(byte, byte);
		PlayerShot(byte, byte, byte, byte);
		void Tick();
};
#endif /* PLAYER_SHOT_H_ */
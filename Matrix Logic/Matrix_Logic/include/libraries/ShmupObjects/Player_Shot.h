#ifndef PLAYER_SHOT_H_
#define PLAYER_SHOT_H_

#include "../../../Globals.h"
#include "Arduino.h"

enum P_Shot_States {PS_Start, PS_Update, PS_Exit};
class PlayerShot {
	private:

		
		byte state;
		
		void move();
		bool collision_check();
		
		void draw();
	public:
		byte x;
		byte y;
		byte x_vel;
		byte y_vel;
		byte x_orig;
		byte y_orig;
		
		bool active;
		
		PlayerShot();
		void Tick();
		
		void create(byte, byte, byte, byte);
};
#endif /* PLAYER_SHOT_H_ */
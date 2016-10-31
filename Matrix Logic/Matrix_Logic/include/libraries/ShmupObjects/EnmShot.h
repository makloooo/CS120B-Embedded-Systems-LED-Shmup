#ifndef ENMSHOT_H_
#define ENMSHOT_H_

#include "Arduino.h"
#include "Player.h"
#include "../../../Globals.h"

enum PROGMEM E_Types {DOT, LASER, BALL};
enum PROGMEM E_Shot_States {ES_Start, ES_Update, ES_Exit};
class EnmShot {
	protected:
		E_Shot_States state;
	
		void move();
		bool collision_check();
		void draw();
		
		bool dot_check();
		bool laser_check();
		bool ball_check();
		
		//sm data
		bool hit;
	public:
		byte x;
		byte y;
		byte x_vel;
		byte y_vel;
		
		E_Types type;
		bool active;
		
		EnmShot();
		void Tick();

		void create(E_Types, byte, byte, byte, byte);
};

#endif /* ENMSHOT_H_ */
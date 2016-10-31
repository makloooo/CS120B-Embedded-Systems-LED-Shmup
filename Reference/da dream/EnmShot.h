#ifndef ENMSHOT_H_
#define ENMSHOT_H_

#include "Arduino.h"
#include "Player.h"
#include "Globals.h"

enum PROGMEM E_Shot_States {ES_Start, ES_Update, ES_Exit};
class EnmShot {
	protected:
		byte x_vel;
		byte y_vel;
	
		E_Shot_States state;
		//byte type;
	
		void move();
		virtual bool collision_check() = 0;
		virtual void draw() = 0;
	
		//sm data
		bool hit;
	public:
		byte x;
		byte y;
		
		byte index;
		
		EnmShot(byte, byte, byte, byte);
		void Tick();
};

class EnmDot : public EnmShot {
	protected:
		bool collision_check();
		void draw();
	public:
		EnmDot(byte _x, byte _y, byte xv, byte yv) : EnmShot(x, y, x_vel, y_vel) {};
};

class EnmLaser : public EnmShot {
	protected:
		bool collision_check();
		void draw();
	public:
		EnmLaser(byte _x, byte _y, byte xv, byte yv) : EnmShot(x, y, x_vel, y_vel) {};
};

class EnmBall : public EnmShot {
	// bouncy
	protected:
		void move();
		bool collision_check();
		void draw();
	public:
		EnmBall(byte _x, byte _y, byte xv, byte yv) : EnmShot(x, y, x_vel, y_vel) {};
};

#endif /* ENMSHOT_H_ */
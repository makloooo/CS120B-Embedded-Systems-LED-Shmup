#ifndef ENM_TYPES_H_
#define ENM_TYPES_H_

#include "Globals.h"
#include "Enemy.h"
#include "Arduino.h"

class Enm_Cross : public Enemy {
	private:
		void shoot();
		void draw();
	public:
		Enm_Cross(byte, byte, byte, byte, byte) : Enemy(x, y, x_vel, y_vel, expire_time) {};
};

class Enm_Line : public Enemy {
	private:
		void shoot();
		void draw();
	public:
		Enm_Line(byte, byte, byte, byte, byte) : Enemy(x, y, x_vel, y_vel, expire_time) {};
};

class Enm_Tracer : public Enemy {
	private:
		void shoot();
		void draw();
	public:
		Enm_Tracer(byte, byte, byte, byte, byte) : Enemy(x, y, x_vel, y_vel, expire_time) {};
};

class Enm_Panel : public Enemy {
	private:
		void shoot();
		void draw();
	public:
		void anim_explode();
	public:
		Enm_Panel(byte, byte, byte, byte, byte) : Enemy(x, y, x_vel, y_vel, expire_time) {};
};

#endif /* ENM_TYPES_H_ */
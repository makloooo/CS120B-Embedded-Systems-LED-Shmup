#ifndef ENEMY_H_
#define ENEMY_H_

#include "Globals.h"
#include "Player_Shot.h"
#include "EnmShot.h"
#include "Arduino.h"

enum PROGMEM Enm_States {Enm_Start, Enm_Update, Enm_Explode, Enm_Exit};
class Enemy {
	protected:
		byte index;
	
		byte x;
		byte y;
	
		byte x_vel;
		byte y_vel;
	
		byte life;
		
		byte exist_time;
		byte expire_time;
		
		//sm data
		Enm_States state = Enm_Start;
		PlayerShot* hit;
		byte cnt;
		byte frame;
		bool unlocked;
		
		void move();
		virtual void shoot() = 0;
		virtual void draw() = 0;
		
		virtual void anim_explode();
		void absorb_bullet(PlayerShot*);
		PlayerShot* collision_check();
	public:
		Enemy(byte, byte, byte, byte, byte);
		void Tick();
		
		void Open_Fire();
};

#endif /* ENEMY_H_ */
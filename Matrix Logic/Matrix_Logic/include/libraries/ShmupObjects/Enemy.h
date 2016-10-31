#ifndef ENEMY_H_
#define ENEMY_H_

#include "../../../Globals.h"
#include "Player_Shot.h"
#include "EnmShot.h"
#include "Arduino.h"

enum PROGMEM Enm_Types {CROSS, LINE, TRACER, PANEL};
enum PROGMEM Enm_States {Enm_Start, Enm_Update, Enm_Explode, Enm_Exit};
class Enemy {
	protected:
		byte index;
		
		byte life;
		
		byte exist_ticks;
		byte expire_ticks;
		
		//sm data
		Enm_States state = Enm_Start;
		PlayerShot* hit;
		byte cnt;
		bool unlocked;
		
		void move();
		void shoot();
		void draw();
		
		void cross_shoot();
		void line_shoot();
		void tracer_shoot();
		
		void panel_shoot();
		void panel_anim_explode();
		
		void anim_explode(); // case by case
		void absorb_bullet(PlayerShot*);
		PlayerShot* collision_check();
	public:
		Enemy();
		void Tick();
		
		byte x;
		byte y;
		byte x_vel;
		byte y_vel;
		
		Enm_Types type;
		
		byte frame;
		bool active;
		
		void getStatus();
		
		void create(Enm_Types, byte, byte, byte, byte, byte, byte);
		void Open_Fire();
};

#endif /* ENEMY_H_ */
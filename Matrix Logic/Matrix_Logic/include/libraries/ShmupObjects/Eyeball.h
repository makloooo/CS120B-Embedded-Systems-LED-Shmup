#ifndef BOSS_1_H_
#define BOSS_1_H_

#include "../../../Globals.h"
#include "Player_Shot.h"
#include "EnmShot.h"
#include "Arduino.h"

enum PROGMEM B1_States {B1_Start, B1_Update, B1_Explode, B1_Exit};
enum PROGMEM B1_Moves {AUTO, LEFT_STOP, RIGHT_STOP, GO_CENTER, OSCILLATE};
enum PROGMEM B1_Shots {DOTS_N_BALLS, RAPID_LASER, BALL_RING, RIGHT_BALL_SPREAD, LEFT_BALL_SPREAD};
class EyeBall {
	protected:

	
	byte x_vel;
	byte y_vel;
	
	uint16_t life;
	byte bar_len;
	
	//sm data
	B1_States state = B1_Start;
	PlayerShot* hit;
	bool unlocked;
	bool flag;
	B1_Moves m_pat;
	B1_Shots s_pat;
	
	// explosion rands
	byte ex_frm;
	byte m;
	byte n;
	
	void move();
	void shoot();
	void draw();
	
	bool place_explosion(byte x, byte y);
	
	bool anim_explode(); // return true when done
	void absorb_bullet(PlayerShot*);
	PlayerShot* collision_check();
	
	public:
	byte x;
	byte y;
	
	uint16_t cnt;
	byte frame;
	bool active;
	
	EyeBall();
	void Tick();
	
	void Set_Move(B1_Moves);
	void Set_Shot(B1_Shots);
	void Open_Fire(bool);
};

#endif /* BOSS_1_H_ */
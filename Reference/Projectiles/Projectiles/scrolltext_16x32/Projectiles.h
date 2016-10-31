/*
 * Ball.h
 *
 * Created: 6/3/2016 10:19:25 AM
 *  Author: Mark
 */ 
#ifndef PROJECTILES_H_
#define PROJECTILES_H_

#include "Globals.h"
#include "You.h"
#include "Director.h"

class Director;

extern Director director;
extern You player;
extern You player2;

enum PROGMEM Proj_States {Proj_Start, Proj_Inactive, Proj_Active, Proj_Lethal, Proj_Warn, Proj_Rotate};
class Projectile {
	protected:
	int8_t x, y, vx, vy;
	Proj_States state;
	
	virtual bool Collision_Check(byte) = 0;
	virtual void Move() = 0;
	virtual void Draw() = 0;
	
	public:
	
	virtual bool Create(int8_t, int8_t, int8_t, int8_t, byte, uint16_t, Colors) = 0;
	
	Proj_States Get_State();
	
	void Tick();
};

/*
class Ball : public Projectile {
	private:
	uint8_t r;
	
	bool Collision_Check();
	void Move();
	void Draw();
	
	public:
	Ball();
	
	inline void Create(byte, byte, byte, byte) {};
	void Create(byte, byte, byte, byte, byte);
	inline void Create(byte, byte, byte, byte, byte, byte) {};
};
*/

/*
class Dot : public Projectile {
	private:
	
	bool Collision_Check();
	void Move();
	void Draw();
	
	public:
	Dot();
	void Create(byte, byte, byte, byte);
	inline void Create(byte, byte, byte, byte, byte) {};
	inline void Create(byte, byte, byte, byte, byte, byte) {};
};
*/

class Laser : public Projectile {
	private:
	// Here we can let vx = x0 and vy = y0
	uint16_t time;
	int8_t thick;
	int16_t frame;
	
	Colors clr;
	
	void Draw();
	inline void Move() {};
	bool Collision_Check(byte);
	
	public:
	Laser();
	
	void Shift_X0(int8_t offs);
	void Shift_X1(int8_t offs);
	void Shift_Y0(int8_t offs);
	void Shift_Y1(int8_t offs);
	//void Shift_Y
	
	uint16_t Get_Time();
	bool Create(int8_t, int8_t, int8_t, int8_t, byte, uint16_t, Colors);
	void Deactivate();
	
	void Start_Rotate();
	
	void Tick();
};
#endif /* PROJECTILES_H_ */
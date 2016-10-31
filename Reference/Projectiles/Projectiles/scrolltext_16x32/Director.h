#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include "Globals.h"
#include "Projectiles.h"
#include "You.h"

#define MAX_BULLETS 4

class Projectile;
class Laser;

extern You player;

enum PROGMEM Shot_Types {DOT, BALL, LASER};
enum PROGMEM Dir_States {Start, Wait, Play, Win, Lose};
class Director {
	private:
		uint16_t count;
		Dir_States state;
		
		//Ball* b[4];
		Laser* l[MAX_BULLETS];
		
		uint8_t aux;
		
		void Animate_Sequence();
		void Tick_Projectiles();
		void Change_Projectile_Type(uint8_t, Shot_Types);
		void Chip_Time();
	public:
		Director();
		
		void Level_Control();
		uint16_t Get_Count();
		
		void Tick();
};
#endif /* DIRECTOR_H_ */
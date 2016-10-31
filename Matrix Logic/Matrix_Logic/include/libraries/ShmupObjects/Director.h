#ifndef DIRECTOR_H_
#define DIRECTOR_H_

#include "../../../Globals.h"
#include "Arduino.h"
#include "Player.h"
#include "Enemy.h"
#include "Eyeball.h"

enum PROGMEM Dir_States {Dir_Start, Dir_Menu, Dir_Stage,
						 Dir_Pause, Dir_Win};
class Director {
	private:
		Dir_States state;
		uint16_t count;
		
		void spawnEnemy(Enm_Types, byte, byte, byte, byte, byte, byte);
	public:
		Director();
		void Tick();
};

#endif /* DIRECTOR_H_ */
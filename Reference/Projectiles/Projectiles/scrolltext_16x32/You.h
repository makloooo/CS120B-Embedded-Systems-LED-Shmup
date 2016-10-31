#ifndef YOU_H_
#define YOU_H_

#include "Globals.h"
#include "SignalControl.h"
extern Signals usart;

enum PROGMEM Pl_States {Pl_Start, Pl_Normal, Pl_Explode, Pl_Invincible};
class You {
	private:
	byte x, y, life, frame;
	
	Colors core_color;
	
	Pl_States state;
	void Move();
	void Draw();
	
	public:
	You(byte, byte, byte);
	void Tick();
	
	Pl_States Get_State();
	byte Get_Life();
	bool Compare_Coordinates(byte, byte);
	void Receieve_Damage();
};
#endif /* YOU_H_ */
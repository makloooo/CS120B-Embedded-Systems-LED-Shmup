#ifndef SIGNALCONTROL_H_
#define SIGNALCONTROL_H_

#include "Globals.h"

#define	EMPTY_SIGNAL	0x00

enum PROGMEM Signal_States {Signal_Start, Signal_Send, Signal_Recieve};
class Signals {
	private:
	byte control;
	byte stage;
	
	Signal_States state;
	
	void Chip_Time();
	
	public:
	Signals();
	void Tick();
	
	bool Has_Signal(Events);
	bool Has_Input(Controls);
	
	void Signal_Event(Events);
	
	void Clear_Signals();
	void Send_Signals();
	void Receive_Signals();
};
#endif /* SIGNALCONTROL_H_ */
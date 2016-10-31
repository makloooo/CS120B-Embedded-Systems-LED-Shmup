#include "SignalControl.h"
Signals::Signals() {
	Clear_Signals();
	state = Signal_Start;
}

void Signals::Clear_Signals() {
	control = EMPTY_SIGNAL;
	stage = EMPTY_SIGNAL;
}

void Signals::Send_Signals() {
	if (Serial.availableForWrite()) {
		Serial.write(stage);
	}
}

void Signals::Receive_Signals() {
	if (Serial.available() > 0) {
		control = Serial.read();
	}
}

bool Signals::Has_Signal(Events e) {
	return bitRead(stage, e);
}

bool Signals::Has_Input(Controls c) {
	return bitRead(control, c);
}

void Signals::Signal_Event(Events e) {
	bitWrite(stage, e, HIGH);
}

void Signals::Tick() {
	switch (state) {
		case Signal_Start:
			Clear_Signals();
			state = Signal_Recieve;
		break;
		
		case Signal_Recieve:
		state = Signal_Send; break;
		
		case Signal_Send:
		state = Signal_Recieve; break;
		
		default:
		break;
	}
	switch (state) {
		case Signal_Start:
		break;
		
		case Signal_Recieve:
		Receive_Signals(); 
		break;
		
		case Signal_Send:
		Send_Signals();
		break;
		
		default:
		break;
	}
}
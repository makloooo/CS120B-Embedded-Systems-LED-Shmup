#include "Globals.h"
#include "SignalControl.h"
#include "You.h"
#include "Director.h"
#include "Projectiles.h"
//#include "Renderer.h"

You player(1, 14, 16);
//You player2(2, 18, 16);
Director director;
Signals usart;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

byte debug = 0;

bool UpdateFlag = false;
void Tick() {
	++debug;
	UpdateFlag = true;
}

void setup() {
	Serial.begin(9600);
	while(!Serial);
	
	pinMode(LED_BUILTIN, OUTPUT);
	
	MsTimer2::set(MS_PER_TICK, Tick);
	MsTimer2::start();
	
	matrix.begin();
}

void loop() {
	/*
	if (debug >= DEBUG_SEC/2) {
		static boolean output = HIGH;
		
		//getFreeRam();
		
		digitalWrite(LED_BUILTIN, output);
		output = !output;
		debug = 0;
	}
	*/
	
	if (UpdateFlag) {
		matrix.fillScreen(0);
		
		usart.Clear_Signals();
		
		usart.Receive_Signals();
		director.Tick();
		player.Tick();
		//player2.Tick();
		usart.Send_Signals();
		
		UpdateFlag = false;
	}
}
/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
//#include "Globals.h"
/*End of auto generated code by Atmel studio */
#include <gamma.h>
#include <RGBmatrixPanel.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);


//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio

byte x = 15;
byte y = 15;

byte matrix_data = 0;

void setup() {
	Serial.begin(9600);
	while (!Serial);
	
	matrix.begin();
	
	matrix.fillScreen(0);
	matrix.drawPixel(x-1, y, matrix.Color333(1, 1, 1));
	matrix.drawPixel(x+1, y, matrix.Color333(1, 1, 1));
	matrix.drawPixel(x, y, matrix.Color333(0, 0, 1));
	matrix.drawPixel(x, y+1, matrix.Color333(1, 1, 1));
	matrix.drawPixel(x, y-1, matrix.Color333(1, 1, 1));
	matrix.drawPixel(x, y-2, matrix.Color333(1, 1, 1));
	matrix.swapBuffers(false);
}

void loop() {
	
	if (Serial.available()) {
		matrix_data = Serial.read();
	}
	
	if (matrix_data != 0x00) {
		if (bitRead(matrix_data, 0)) x = (x < 32) ? x+1 : x;
		if (bitRead(matrix_data, 1)) y = (y > 0) ? y-1 : y;
		if (bitRead(matrix_data, 2)) y = (y < 32) ? y+1 : y;
		if (bitRead(matrix_data, 4)) x = (x > 0) ? x-1 : x;
		matrix.fillScreen(0);
		matrix.drawPixel(x-1, y, matrix.Color333(1, 1, 1));
		matrix.drawPixel(x+1, y, matrix.Color333(1, 1, 1));
		matrix.drawPixel(x, y, matrix.Color333(0, 0, 1));
		matrix.drawPixel(x, y+1, matrix.Color333(1, 1, 1));
		matrix.drawPixel(x, y-1, matrix.Color333(1, 1, 1));
		matrix.drawPixel(x, y-2, matrix.Color333(1, 1, 1));
		matrix.swapBuffers(false);
		matrix_data = 0x00;
	}
	
}

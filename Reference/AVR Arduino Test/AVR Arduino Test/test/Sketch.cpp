/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
/*End of auto generated code by Atmel studio */

#include <MsTimer2.h>

#include <gamma.h>
#include <RGBmatrixPanel.h>

#include <Adafruit_GFX.h>
#include <gfxfont.h>

#define CLK 8
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

byte x = 0;

void flash() {
  matrix.fillScreen(0);
  
  matrix.drawPixel(x, 15, matrix.Color333(2, 2, 2));
  x = (x < 32) ? x+1 : 0;
}

void setup() {
  matrix.begin();
  MsTimer2::set(50, flash);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
  matrix.swapBuffers(false);
}

/*
 * Shift Register Test.c
 *
 * Created: 5/16/2016 2:38:38 PM
 * Author : Mark
 */ 

#include <avr/io.h>
#include "shift_reg.h"
#include "timer.h"

int main(void)
{
    /* Replace with your application code */
	DDRA = 0xFF; PORTA = 0x00;
	
	unsigned char data = 0xAA;
	
	TimerSet(500);
	TimerOn();
	
    while (1) 
    {
		transmit_char(data);
		while(!TimerFlag);
		data = ~data;
		TimerFlag = 0;
	}
}


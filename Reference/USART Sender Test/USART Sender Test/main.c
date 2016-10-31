/*
 * USART Test.c
 *
 * Created: 5/18/2016 2:19:13 PM
 * Author : Mark
 */ 

#include <avr/io.h>
#include "timer.h"
#include "shift_reg.h"
#include "usart_ATmega1284.h"

unsigned char data = 0xAA;

enum States {Init, Blink} state;
void Tick() {
	switch(state) {
		case Init:
		state = Blink;
		break;
		
		case Blink:
		transmit_data_ch(data);
		data = ~data;
		break;
	}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	
	initUSART(0);
	
	TimerSet(50);
	TimerOn();
	
	state = Init;
	
	unsigned short LED_period = 1000;
	unsigned short LED_elapsed_time = 1000;
	
    while (1) 
    {
		if (USART_IsSendReady(0)) {
			USART_Send(data, 0);
		}
		if (LED_elapsed_time >= LED_period) {
			Tick();
			LED_elapsed_time = 0;
		}
		while(!TimerFlag);
		TimerFlag = 0;
		LED_elapsed_time += 50;
    }
}
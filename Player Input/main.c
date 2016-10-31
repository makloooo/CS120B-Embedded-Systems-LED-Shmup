/*
 * Game Logic.c
 *
 * Created: 5/27/2016 5:53:13 PM
 * Author : Mark
 */ 

#include <avr/io.h>
#include "bit.h"
#include "scheduler.h"
#include "timer.h"
#include "usart_ATmega1284.h"

unsigned char p1_input = 0;
//unsigned char p2_input = 0;

#include "Player_Input.h"
#include "Send_Input.h"

int main(void) {
	DDRB = 0xFF; PORTB = 0x00; // Debug Output
	DDRA = 0x00; PORTA = 0xFF; // Input
	DDRC = 0x00; PORTC = 0xFF; // Input
	DDRD = 0xFA; PORTD = 0x05; // Output
	
	// Period for the tasks
	unsigned long Player_Input_calc = 50;
	unsigned long Send_Input_calc = 15;
	
	// Calculating GCD
	unsigned long tmpGCD = 1;
	tmpGCD = findGCD(Player_Input_calc, Send_Input_calc);
	//tmpGCD = findGCD(tmpGCD, Send_Input_calc);
	
	// GCD for all tasks or smallest time unit for tasks
	unsigned long GCD = tmpGCD;
	
	// Recalculate GCD periods for scheduler
	unsigned long Player_Input_period = Player_Input_calc/GCD;
	unsigned long Send_Input_period = Send_Input_calc/GCD;
	
	// Declare an array of tasks
	static task task1, task2;
	task* tasks[] = { &task1, &task2 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
	
	// Task 1
	task1.state = Input_Start;
	task1.period = Player_Input_period;
	task1.elapsedTime = Player_Input_period;
	task1.TickFct = &Player_Input;
	
	// Task 2
	task2.state = Send_Start;
	task2.period = Send_Input_period;
	task2.elapsedTime = Send_Input_period;
	task2.TickFct = &Send_Input;
	
	// Set the Timer and turn it on
	TimerSet(GCD);
	TimerOn();
	
	// Initialize USART
	initUSART(0);
	// initUSART(1);
	
	unsigned short i;
	
	while (1)
	{
		// Scheduler code
		for (i = 0; i < numTasks; i++) {
			// Task is ready for tick
			if (tasks[i]->elapsedTime == tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while (!TimerFlag);
		TimerFlag = 0;
		PORTB = 0x00;
	}
}
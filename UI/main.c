/*
 * Main.c
 *
 * Created: 5/25/2016 7:17:48 PM
 * Author : Mark
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include "shift_reg.h"
#include "timer.h"
#include "scheduler.h"
#include "usart_ATmega1284.h"
#include "io.h"
#include "bit.h"

unsigned char stg_event = 0x00;

//enum Events {START_GAME, P1_HIT, P1_EXTEND, P2_HIT, P2_EXTEND, PAUSE, WIN, BOSS_ACTION};
enum Events {START_GAME, P1_HIT, P2_HIT, LOSE, WIN, ACTION};

#include "LCD_Control.h"
#include "Life_Bars.h"

int main(void) {
    DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFE; PORTD = 0x01; // oooo oooi
	    
    // Period for the tasks
    unsigned long LCD_Control_calc = 25;
    unsigned long Update_Life_calc = 25;
	unsigned long Display_Life_calc = 50;
    
    // Calculating GCD
    unsigned long tmpGCD = 1;
    tmpGCD = findGCD(LCD_Control_calc, Update_Life_calc);
	tmpGCD = findGCD(tmpGCD, Display_Life_calc);
    
    // GCD for all tasks or smallest time unit for tasks
    unsigned long GCD = tmpGCD;
    
    // Recalculate GCD periods for scheduler
    unsigned long LCD_Control_period = LCD_Control_calc/GCD;
    unsigned long Update_Life_period = Update_Life_calc/GCD;
	unsigned long Display_Life_period = Display_Life_calc/GCD;
    
    // Declare an array of tasks
    static task task1, task2, task3;
    task* tasks[] = { &task1, &task2, &task3 };
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    
    // Task 1
    task1.state = LCD_Start;
    task1.period = LCD_Control_period;
    task1.elapsedTime = LCD_Control_period;
    task1.TickFct = &LCD_Control;
    
    // Task 2
    task2.state = LED_Start;
    task2.period = Update_Life_period;
    task2.elapsedTime = Update_Life_period;
    task2.TickFct = &Update_Life;
    
    // Task 3
    task3.state = Start;
    task3.period = Display_Life_period;
    task3.elapsedTime = Display_Life_period;
    task3.TickFct = &Display_Life;
	
    // Set the Timer and turn it on
    TimerSet(GCD);
    TimerOn();
	
    unsigned short i;
    
	initUSART(0);
	initUSART(1);
	
	USART_Flush(0);
	
	if (USART_HasReceived(0)) stg_event = USART_Receive(0);
    while (1)
    {
	    // Scheduler code
		//if (USART_HasReceived(0)) stg_event = USART_Receive(0);
		PORTB = stg_event;
	    for (i = 0; i < numTasks; i++) {
		    // Task is ready for tick
		    if (tasks[i]->elapsedTime == tasks[i]->period) {
			    tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			    tasks[i]->elapsedTime = 0;
		    }
		    tasks[i]->elapsedTime += 1;
	    }
		stg_event = 0x00;
	    while (!TimerFlag);
		if (USART_HasReceived(0)) stg_event = USART_Receive(0);
	    TimerFlag = 0;
		PORTB = 0;
    }
}
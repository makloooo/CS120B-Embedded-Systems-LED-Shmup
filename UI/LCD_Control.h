/*
 * LCD_Control.h
 *
 * Created: 5/27/2016 2:22:26 AM
 *  Author: Mark
 */ 
#ifndef LCD_CONTROL_H_
#define LCD_CONTROL_H_

#define DISPLAY_SIZE 16

#define DASH 0xB0
#define SLASH 0x2F
#define LINE 0x7C
#define BLOCK 0xFF

unsigned char menu[32] = ">P1 Press Center>P2 Join Center";
unsigned char stage_string[9] = "Survive!";
unsigned char boss_string[6] = "Time:";
unsigned char stage_clear[12] = "You did it!";
unsigned char lose_str[13] = "Game Over...";

// Auxiliary animate function
void animate_bar_gen(unsigned char pos) {
	pos -= 3; LCD_Cursor(pos);
	if (pos >= 22 && pos < DISPLAY_SIZE*2 + 1) LCD_WriteData(BLOCK);
	++pos; LCD_Cursor(pos);
	if (pos >= 22 && pos < DISPLAY_SIZE*2 + 1) LCD_WriteData(LINE);
	++pos; LCD_Cursor(pos);
	if (pos >= 22 && pos < DISPLAY_SIZE*2 + 1) LCD_WriteData(SLASH);
	++pos; LCD_Cursor(pos);
	if (pos >= 22 && pos < DISPLAY_SIZE*2 + 1) LCD_WriteData(DASH);
}

// Display Stage Number, Boss HP, possibly score
// !!! ONLY UPDATES GLOBAL VARIABLES !!!
enum LCD_States {LCD_Start, LCD_Idle, LCD_InitBoss, LCD_DepleteHP, LCD_DisplayWin, LCD_NextStage, LCD_DisplayLose};
int LCD_Control(int state) {
	static unsigned char lcd_cnt;
	static unsigned char pos;
	static unsigned char stage_num;
	
	switch (state) {
		case LCD_Start:
		LCD_init();
		LCD_ClearScreen();
		LCD_DisplayString(1, menu);
		pos = 17;
		stage_num = 1;
		state = LCD_Idle;
		break;
		//---------------------------------
		case LCD_Idle:
		// Check USART Flag, if set, inspect and respond if called.
		if (GetBit(stg_event, START_GAME)) { // usart: stage begin
			LCD_DisplayString(1, stage_string);
			lcd_cnt = 1;
			state = LCD_InitBoss;
		}
		else if (GetBit(stg_event, WIN)) { // usart: time out
			lcd_cnt = 0;
			pos = 0; // rough way to set flags, but it works
			++stage_num;
			state = LCD_DisplayWin;
		}
		else if (GetBit(stg_event, LOSE)) {
			pos = 0;
			state = LCD_DisplayLose;
		}
		break;
		//---------------------------------
		case LCD_InitBoss:
		if (pos > DISPLAY_SIZE*2 + 3) {
			pos = DISPLAY_SIZE*2;
			state = LCD_DepleteHP;
		}
		else ++lcd_cnt;
		break;
		//---------------------------------
		case LCD_DepleteHP:
		if (pos < 22) {
			++pos;
			state = LCD_Idle;
		}
		if (GetBit(stg_event, WIN)) {
			lcd_cnt = 0;
			pos = 0; // rough way to set flags, but it works
			++stage_num;
			state = LCD_DisplayWin;
		}
		if (GetBit(stg_event, LOSE)) {
			pos = 0;
			state = LCD_DisplayLose;
		}
		break;
		//---------------------------------
		case LCD_DisplayWin:
// 		if (GetBit(stg_event, WIN)) { // usart: tbd, after boss destruction?
// 			state = LCD_NextStage;
// 		}
//		else 
		++lcd_cnt;
		break;
		//---------------------------------
		case LCD_DisplayLose:
		//if (GetBit(stg_event, ACTION)) state = LCD_Start;
		++lcd_cnt;
		break;
		//---------------------------------
		case LCD_NextStage:
		state = LCD_Idle;
		break;
		//---------------------------------
		default:
		break;
	}
	
	switch (state) {
		case LCD_Start:
		break;
		//---------------------------------
		case LCD_Idle:
		LCD_Cursor(0);
		break;
		//---------------------------------
		case LCD_InitBoss:
		LCD_Cursor(pos);
		if (pos > 22 && lcd_cnt % 2 == 0) {
			animate_bar_gen(pos);
			++pos;
		}
		else if (pos == 22) {
			if (lcd_cnt % 20 == 0) {
				LCD_WriteData(DASH);
				pos++;
			}
		}
		else if (pos < 22 && lcd_cnt % 5 == 0) {
			LCD_WriteData(boss_string[pos-17]);
			pos++;
			if (pos == 22) lcd_cnt = 1;
		}
		break;
		//---------------------------------
		case LCD_DepleteHP:
		if (GetBit(stg_event, ACTION)) { // usart: event back boss dmged 10%
			LCD_Cursor(pos);
			LCD_WriteData(0xFE);
			--pos;
			LCD_Cursor(0);
		}
		break;
		//---------------------------------
		case LCD_DisplayWin:
		if (pos == 0 && lcd_cnt % 10 == 0) {
			for (pos = 1; pos <= 11; ++pos) {
				LCD_Cursor(pos);
				LCD_WriteData(stage_clear[pos - 1]);
			}
			pos = 33;
		}
		else if (pos == 33 && lcd_cnt % 10 == 0) {
			for (pos = 1; pos <= 15; ++pos) {
				LCD_Cursor(pos);
				LCD_WriteData(0xFE);
			}
			pos = 0;
		}
		LCD_Cursor(0);
		break;
		//---------------------------------
		case LCD_NextStage:
		if (stage_num > 1) {
			for (pos = 1; pos <= DISPLAY_SIZE; ++pos) {
				LCD_Cursor(pos);
				LCD_WriteData(0xFE);
			}
			LCD_PlaceString(1, stage_string);
			LCD_Cursor(7);
			LCD_WriteData('0' + stage_num);
			pos = 22;
		}
		else LCD_DisplayString(1, stage_string);
		
		LCD_Cursor(0);
		state = LCD_Idle;
		break;
		//---------------------------------
		case LCD_DisplayLose:
		if (pos == 0 && lcd_cnt % 10 == 0) {
			for (pos = 1; pos < 13; ++pos) {
				LCD_Cursor(pos);
				LCD_WriteData(lose_str[pos - 1]);
			}
			pos = 33;
		}
		LCD_Cursor(0);
		default:
		break;
	}
	
	return state;
}

#endif /* LCD_CONTROL_H_ */
#include "Director.h"

Director::Director() {
	count = 0;
	state = Dir_Start;
}

// args: type, x, y, xv, yv, life, ticksAlive
void Director::spawnEnemy(Enm_Types type, byte x, byte y, byte x_vel, byte y_vel, byte _life, byte _ticks) {
	for (byte i = 0; i < ENM_MAX; ++i) {
		if (!enms[i]->active) {
			enms[i]->create(type, x, y, x_vel, y_vel, _life, _ticks);
		}
	}
}

void Director::Tick() {
	switch(state) {
		case Dir_Start:
			state = Dir_Menu;
		break;
		case Dir_Menu:
			if (bitRead(p1_input, SHOT)) {
				bitWrite(game_event, START_GAME, HIGH);
				state = Dir_Stage;
			}
		break;
		case Dir_Stage:
			if (bitRead(game_event, WIN)) state = Dir_Win;
			if (bitRead(game_event, PAUSE)) state = Dir_Pause;
		break;
		case Dir_Pause:
			if (bitRead(p1_input, ENTER)) state = Dir_Stage;
			if (p2.active && bitRead(p2_input, ENTER)) state = Dir_Stage;
		break;
		case Dir_Win:
			// Final State, no transitions out
		break;
		default:
		break;
	}
	
	switch(state) {
		case Dir_Start:
		break;
		case Dir_Menu:
			
			// draw menu screen
		break;
		case Dir_Stage:
			// tick all existing objects
			// drawing is done with each object tick
			p1.Tick();
			p2.Tick();
			
			/*
			for (byte i = 0; i < PS_MAX; ++i) {
				if (pl_bullets[i]->active) {
					pl_bullets[i]->Tick();
				}
			}
			*/
			
			/*
			if (boss != NULL) boss->Tick();
			for (byte i = 0; i < 8; ++i) {
				if (enms[i]->active) {
					enms[i]->Tick();
				}
			}
			for (byte i = 0; i < ES_MAX; ++i) {
				if (enm_bullets[i]->active) {
					enm_bullets[i]->Tick();
				}
			}
			
			
			// spawn enemies depending on internal count
			if (count > 5*200 && count < 10*200) {
				spawnEnemy(CROSS, 40, 6, -2, 0, 1, 60);
			}
			*/
			
			/*
			if (count > 65 && count < 75) {
				spawnEnemy(TRACER, -5, 15, 5, random(0, -2));
			}
			if (count == 100) {
				spawnEnemy(PANEL, 16, -5, 0, 1);
			}
			
			if (count > 150 && count < 200) {
				spawnEnemy(LINE, -3, 10, 3, 0);
				spawnEnemy(LINE, 39, 5, -3, 0);
			}
			
			// when ready, boss = new Eyeball();
			if (count == 250) {
				boss = new EyeBall();
			}
			*/
			
			// they should be automatically deleted
			++count;
		break;
		case Dir_Pause:
			// draw pause screen
			// ticking stops, so nothing is drawn
		break;
		case Dir_Win:
			// draw win screen
			p1.Tick();
			p2.Tick();
		break;
		default:
		break;
	}
	return;
}
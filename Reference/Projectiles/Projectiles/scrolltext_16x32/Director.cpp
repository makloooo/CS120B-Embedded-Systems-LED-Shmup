#include "Director.h"

Director::Director() {
	for (uint8_t i = 0; i < MAX_BULLETS; ++i){
		l[i] = new Laser;
	}
	state = Start;
}

void Director::Animate_Sequence() {
	for (uint8_t i = 0; i <= matrix.width(); i += 8) {
		matrix.drawPixel(i + count, 0, matrix.Color333(1, 0, 0));
		matrix.drawPixel(i + count - 4, 1, matrix.Color333(0, 1, 0));
		
		matrix.drawPixel(i-count, matrix.height()-1, matrix.Color333(1, 0, 0));
		matrix.drawPixel(i-count+4, matrix.height()-2, matrix.Color333(0, 1, 0));
		
		matrix.drawPixel(0, matrix.height()-i-count-1, matrix.Color333(1, 0, 0));
		matrix.drawPixel(1, matrix.height()-i-count+3, matrix.Color333(0, 1, 0));
		
		matrix.drawPixel(matrix.width()-1, i+count, matrix.Color333(1, 0, 0));
		matrix.drawPixel(matrix.width()-2, i+count-4, matrix.Color333(0, 1, 0));
	}
	
	if (++count % 8 == 0) count = 0;
}

void Director::Chip_Time() {
	if (count % 550 == 0) {
		usart.Signal_Event(ACTION);
	}
}

uint16_t Director::Get_Count() {
	return count;
}

// x1, y1, x1, y1, thickness, exist time (note 75 is spent warning), color
void Director::Level_Control() {
	// level goes here
	// values found on paint
	
	
	// initial laser
	if (count == 100) l[0]->Create(-1, 8, 32, 8, 5, 150, RED);
	
	// consecutive lasers
	if (count >= 400 && count <= 800) {
		if (count % 110 == 0 && count % 220 != 0) {
			l[aux%4]->Create(0, random(0, 32), 32, random(0, 32), 3, 100, RED);
			++aux;
		}
		else if (count % 220 == 0) {
			l[aux%4]->Create(random(0, 32), 0, random(0, 32), 32, 3, 100, RED);
			++aux;
		}
	}
	// 3 cross lasers
	if (count == 1000) {
		l[0]->Create(6, 0, 15, 32, 1, 100, RED);
		l[1]->Create(0, 24, 31, 6, 1, 100, RED);
	}
	if (count == 1200) {
		l[1]->Deactivate();
		l[1]->Create(0, 15, 31, 21, 1, 100, YELLOW);
		l[2]->Create(23, 0, 28, 31, 1, 100, YELLOW);
	}
	if (count == 1300) {
		l[0]->Deactivate();
		l[1]->Deactivate();
		l[2]->Deactivate();
		
		l[0]->Create(0, 0, 31, 26, 1, 100, BLUE);
		l[1]->Create(0, 29, 31, 11, 1, 100, BLUE);
		l[2]->Create(18, 0, 22, 31, 1, 100, BLUE);
	}
	if (count == 1400) {
		l[0]->Deactivate();
		l[1]->Deactivate();
		l[2]->Deactivate();
		
		l[0]->Create(0, 25, 22, 0, 1, 100, GREEN);
		l[1]->Create(0, 12, 22, 32, 1, 100, GREEN);
		l[2]->Create(0, 3, 31, 11, 1, 100, GREEN);
	}
	
	// Repeater lasers
	if (count >= 1450 && count <= 2300) {
		if (count % 60 == 0 && count % 120 != 0) {
			l[aux%4]->Create(0, random(0, 32), 32, random(0, 32), 1, 100, static_cast<Colors>(random(0, 7)));
			++aux;
		}
		else if (count % 120 == 0) {
			l[aux%4]->Create(random(0, 32), 0, random(0, 32), 32, 1, 100, static_cast<Colors>(random(0, 7)));
			++aux;
		}
	}
	
	// left wall enclose laser + a couple others
	if (count == 2300) {
		l[3]->Deactivate();
		l[3]->Create(30, 0, 30, 32, 3, 700, RED);
		aux = 0;
	}
	if (count >= 2350 && count <= 3200) {
		if (count % 60 == 0) {
			l[aux%2]->Create(0, random(0, 32), 32, random(0, 32), 1, 100, static_cast<Colors>(random(0, 7)));
			++aux;
		}
		if (count % 30 == 0) {
			l[3]->Shift_X0(-1);
			l[3]->Shift_X1(-1);
		}
	}
	
	// Shifter lasers
	
	if (count == 3400) {
		for (aux = 0; aux < MAX_BULLETS; ++aux) {
			l[aux]->Deactivate();
		}
		l[0]->Create(0, 15, 32, 0, 1, 700, RED);
	}
	if (count == 3475) l[0]->Start_Rotate();
	if (count == 4200) {
		l[0]->Deactivate();
		l[0]->Create(0, 8, 32, 8, 1, 700, RED);
		l[1]->Deactivate();
		l[1]->Create(0, 24, 32, 24, 1, 700, RED);
	}
	if (count == 4275) {
		l[0]->Start_Rotate();
		l[1]->Start_Rotate();
	}
	if (count == 5000) {
		for (aux = 0; aux < MAX_BULLETS; ++aux) {
			l[aux]->Deactivate();
		}
		l[0]->Create(0, 15, 26, 0, 1, 1400, RED);
		l[1]->Create(26, 0, 26, 32, 1, 1400, RED);
		l[2]->Create(26, 32, 0, 15, 1, 1400, RED);
	}
	if (count == 5075) {
		l[0]->Start_Rotate();
		l[1]->Start_Rotate();
		l[2]->Start_Rotate();
	}
	if (count >= 3600 && count <= 6400) {
		if (count % 80 == 0 && count % 160 != 0) {
			for(aux = 0; aux < 4; ++aux) {
				if (l[aux%4]->Create(0, random(0, 32), 32, random(0, 32), 1, 75, static_cast<Colors>(random(0, 7)))) {
					break;
				}
			}
		}
		else if (count % 160 == 0) {
			for(aux = 0; aux < 4; ++aux) {
				if (l[aux%4]->Create(random(0, 32), 0, random(0, 32), 32, 1, 75, static_cast<Colors>(random(0, 7)))) {
					break;
				}
			}
		}
	}
	
}

void Director::Tick_Projectiles() {
	for (uint8_t i = 0; i < MAX_BULLETS; ++i) {
		if (l[i]->Get_State() != Proj_Inactive) {
			l[i]->Tick();
		}
	}
	//if (count >= 120) pixelDebug(2, 1, matrix.Color333(0, 1, 0));
}

void Director::Tick() {
	switch (state) {
		case Start:
		state = Wait;
		break;
		
		case Wait:
		if (usart.Has_Input(SHOT)) {
			usart.Signal_Event(START_GAME);
			randomSeed(analogRead(5));
			count = 0;
			aux = 0;
			state = Play;
		}
		break;
		
		case Play:
			if (count >= 6600) state = Win;
			else if (player.Get_Life() <= 0) {
				count = 1;
				state = Lose;
			}
		break;
		
		case Win:
		break;
		
		case Lose:
		break;
		
		default:
		break;
	}
	switch (state) {
		case Start:
		break;
		
		case Wait:
		Animate_Sequence();
		break;
		
		case Play:
		Level_Control();
		Chip_Time();
		Tick_Projectiles();
		++count;
		break;
		
		case Win:
		usart.Signal_Event(WIN);
		break;
		
		case Lose:
		usart.Signal_Event(LOSE);
		Tick_Projectiles();
		break;
	}
}

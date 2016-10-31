#include "Player.h"

// Events {START_GAME, P1_HIT, P1_EXTEND, P2_HIT, P2_EXTEND, PAUSE, WIN, BOSS_ACTION};
Player::Player(byte _num, byte _life) {
	num = _num;
	life = _life;
	power = 1;
	speed = 1; // Unused as of now.
	
	x = (num == 1) ? STG_WIDTH / 2 - 2 : STG_WIDTH / 2 + 2;
	y = STG_HEIGHT - 3;

	state = Player_Start;
	
	// p1 == red, p2 == green
	//coreColor = (num == 1) ? Colors[RED] : Colors[GREEN];
	active = (num == 1) ? true : false;
	signal = (num == 1) ? &p1_input : &p2_input;
}

void Player::spawn() {
	// Re-init the player's position on the matrix.
	x = STG_WIDTH / 2;
	y = STG_HEIGHT - 2;
}

void Player::shoot() {
	// 'Spawn' bullet relative to player depending on usart
	// Ensure patten shot is relative to current power
	for (byte i = 0; i < PS_MAX; ++i) {
		if (!pl_bullets[i]->active) {
			pl_bullets[i]->create(x, y, 0, -3);
		}
	}
}

void Player::move() {
	// Update position on buffer matrix according to usart
	if (bitRead(*signal, UP) && y > 0) --y;
	if (bitRead(*signal, DOWN) && y < STG_HEIGHT) ++y;
	if (bitRead(*signal, LEFT) && x > 0) --x;
	if (bitRead(*signal, RIGHT) && x < STG_WIDTH) ++x;
}

void Player::extend() {
	if (life < 10) ++life;
	if (num == 1) bitWrite(game_event, P1_EXTEND, HIGH);
	else bitWrite(game_event, P2_EXTEND, HIGH);
}

void Player::draw() {
	Send_To_Matrix(this, num);
}

void Player::anim_explode(byte frame) {
	Send_To_Matrix(ANIM_BIG_EXPLODE, x, y, frame);
}

// Controls {RIGHT, LEFT, DOWN, A3_BROKEN, UP, ENTER, SHOT, SUDOKU};
// P_States {Player_Start, Player_Update, Player_Explode, Player_Inactive, Player_Lost};
void Player::Tick() {
	
	switch(state) { //  Transitions
		case Player_Start:
			state = Player_Inactive;
			wait = false;
			honor = false;
		break;
		
		case Player_Inactive:
			state = (active) ? Player_Update : state;
		break;
		
		case Player_Update:
			if (bitRead(*signal, SUDOKU)) {
				honor = true;
				state = Player_Explode;
			}
			// if pos overlap with bullet
			// state = Player_Explode;
		break;
		
		case Player_Explode:
			if (life <= 0) state = Player_Lost;
			else { 
				i = 1;
				frame = 0;
				state = Player_Respawn;
			}
		break;
		
		case Player_Respawn:
			if (i > 30) {
				spawn();
				state = Player_Update;
			}
			else ++i;
		break;
		
		case Player_Lost:
			// No coming back! See you, sucker!
		break;
		
		default:
		break;
	}
	
	switch (state) {
		case Player_Start:
		break;
		
		case Player_Inactive:
			if (bitRead(*signal, ENTER)) active = true;
		break;
		
		case Player_Update:
			move();
			if (bitRead(*signal, SHOT)) {
				if (!wait) {
					shoot();
					wait = true;
				} else wait = false;
			}
			else wait = false;
			if (bitRead(*signal, ENTER)) {
				// pause entire display
				bitWrite(game_event, PAUSE, HIGH);
			}
			draw();
		break;
		
		case Player_Explode:
		/*
			if (honor) { //oops
				pl_bullets.add(new PlayerShot(x, y, 0, 2));
				pl_bullets.add(new PlayerShot(x, y, 1, 1));
				pl_bullets.add(new PlayerShot(x, y, 2, 0));
				pl_bullets.add(new PlayerShot(x, y, 1, -1));
				pl_bullets.add(new PlayerShot(x, y, 0, -2));
				pl_bullets.add(new PlayerShot(x, y, -1, -1));
				pl_bullets.add(new PlayerShot(x, y, -2, 0));
				pl_bullets.add(new PlayerShot(x, y, -1, 1));
			}
			else {
				enm_bullets.add(new EnmLaser(x, y, 0, 2));
				enm_bullets.add(new EnmLaser(x, y, 1, 1));
				enm_bullets.add(new EnmLaser(x, y, 2, 0));
				enm_bullets.add(new EnmLaser(x, y, 1, -1));
				enm_bullets.add(new EnmLaser(x, y, 0, -2));
				enm_bullets.add(new EnmLaser(x, y, -1, -1));
				enm_bullets.add(new EnmLaser(x, y, -2, 0));
				enm_bullets.add(new EnmLaser(x, y, -1, 1));
			}
		*/
			--life;
			
			// Sending event to UI
			if (num == 1) bitWrite(game_event, P1_HIT, HIGH);
			else bitWrite(game_event, P2_HIT, HIGH);
		break;
		
		case Player_Respawn:
			if (i % 7 == 0) ++frame;
			anim_explode(frame);
		break;
		
		case Player_Lost:
		break;
		
		default:
		break;
	}
}
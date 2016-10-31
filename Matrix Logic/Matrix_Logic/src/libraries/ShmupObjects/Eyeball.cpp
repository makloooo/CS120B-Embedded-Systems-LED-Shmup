#include "EyeBall.h"

EyeBall::EyeBall() {
	x = 0;
	y = -11;
	
	x_vel = 0;
	y_vel = 1;
	
	// needs to be divisible by 11 cuz im dumb
	life = (p2.active) ? 329 : 164;
	bar_len = (p2.active) ? 30 : 15;
	
	hit = NULL;
	cnt = 0;
	frame = 0;
	unlocked = false;
	flag = false;
	
	m_pat = AUTO;
	s_pat = DOTS_N_BALLS;
}

void EyeBall::move() {
	switch(m_pat) {
		case GO_CENTER:
			if (x < 15) x_vel = 1;
			else if (x > 15) x_vel = -1;
			else x = 0;
		break;
		case LEFT_STOP:
			x_vel = (x > 6) ? -1 : 0;
		break;
		case RIGHT_STOP:
			x_vel = (x < 29) ? 1 : 0;
		break;
		case OSCILLATE:
			x_vel = (x_vel == 0) ? 1 : 0;
			if (x < 6 || x > 29) x_vel *= -1;
		break;
		default:
		break;
	}
	x += x_vel;
	y += y_vel;
}

void EyeBall::shoot() {
	switch(s_pat) {
		case DOTS_N_BALLS:
		break;
		case RAPID_LASER:
		break;
		case LEFT_BALL_SPREAD:
		break;
		case RIGHT_BALL_SPREAD:
		break;
		case BALL_RING:
		break;
		default:
		break;
	}
}

void EyeBall::draw() {
	Send_To_Matrix(this);
}

bool EyeBall::place_explosion(byte _x, byte _y) {
	ex_frm %= cnt % 9;
	if (cnt >= 9) return true;
	Send_To_Matrix(ANIM_BIG_EXPLODE, _x, _y, ex_frm);
	return false;
}

bool EyeBall::anim_explode() {
	if (place_explosion(m, n)) {
		// relocate next explosion
		m = x + random(-6, 6);
		n = y + random(-6, 6);
	}
	Send_To_Matrix(this);
	return cnt >= 90;
}

void EyeBall::absorb_bullet(PlayerShot* b) {
	if (b == NULL) return;
	
	b->active = false;
}

PlayerShot* EyeBall::collision_check() {
	PlayerShot* tmp;
	for (byte i = 0; i < PS_MAX; ++i) {
		tmp = pl_bullets[i];
		if ((tmp->x >= x-5 && tmp->x <= x+5)
		&& (tmp->y >= y-5 && tmp->y <= y+5)) return tmp;
	}
	return NULL;
}

void EyeBall::Tick() {

	switch(state) {
		case B1_Start:
		state = B1_Update;
		break;
		
		case B1_Update:
		if (life <= 0) {
			cnt = 1;
			frame = 3;
			m = x + random(-6, 6);
			n = y + random(-6, 6);
			state = B1_Explode;
		}
		else if (life % bar_len == 0) {
			bitWrite(game_event, BOSS_ACTION, HIGH);
		}
		break;
		
		case B1_Explode:
		if (anim_explode()) {
			state = B1_Exit;
		} else ++cnt;
		break;
		
		case B1_Exit:
		break;
		
		default:
		break;
	}
	
	switch(state) {
		case B1_Start:
		break;
		
		case B1_Update:
		++cnt;
		if (cnt % 5 == 0) flag = ~flag;
		move();
		
		if (unlocked && x >= 0 && x < STG_WIDTH) {
			if (y >= 0 && y < STG_HEIGHT) shoot();
		} // only shoot if within bounds
		
		draw();
		hit = collision_check();
		if (hit != NULL) {
			absorb_bullet(hit);
			--life;
			hit = NULL;
		}
		break;
		
		case B1_Explode:
		if (cnt % 5 == 0) {
			x = (flag) ? x+1 : x-1;
			flag = ~flag;
		}
		break;
		
		case B1_Exit:
		// manage linked list before deleting
		active = false;
		break;
		
		default:
		break;
	}
}

void EyeBall::Set_Move(B1_Moves pattern) {
	m_pat = pattern;
}

void EyeBall::Set_Shot(B1_Shots pattern) {
	s_pat = pattern;
}

void EyeBall::Open_Fire(bool _unlocked) {
	unlocked = _unlocked;
}
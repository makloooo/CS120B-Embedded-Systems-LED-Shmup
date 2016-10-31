#include "Enemy.h"

Enemy::Enemy() {
	active = false;
}

// args: type, x, y, xv, yv, life, ticksAlive
void Enemy::create(Enm_Types _type, byte _x, byte _y, byte _xv, byte _yv, byte _life, byte _ticks) {
	x = _x;
	y = _y;
	
	x_vel = _xv;
	y_vel = _yv;
	
	frame = 0;
	
	type = _type;
	
	life = _life;
	
	exist_ticks = 0;
	expire_ticks = _ticks;
	
	unlocked = false;
	active = true;
}

void Enemy::move() {
	// bouncy is handled in collision check
	x += x_vel;
	y += y_vel;
}

PlayerShot* Enemy::collision_check() {
	PlayerShot* tmp;
	for (byte i = 0; i < 16; ++i) {
		tmp = pl_bullets[i];
		if ((tmp->x >= x-1 && tmp->x <= x+1)
			&& (tmp->y >= y-1 && tmp->y <= y+1)) return tmp;
	}
	return NULL;
}

void Enemy::anim_explode() {
	Send_To_Matrix(ANIM_EXPLODE, x, y, frame);
}

void Enemy::Open_Fire() {
	unlocked = true;
}

void Enemy::absorb_bullet(PlayerShot* b) {
	if (b == NULL) return;
	b->active = false;
}

//Enm_States {Enm_Start, Enm_Update, Enm_Explode, Enm_Exit};
void Enemy::Tick() {

	switch(state) {
		case Enm_Start:
			state = Enm_Update;
		break;
		
		case Enm_Update:
			if (life <= 0) {
				cnt = 1;
				state = Enm_Explode;
			}
			if (exist_ticks >= expire_ticks) state = Enm_Exit;
		break;
		
		case Enm_Explode:
			if (cnt > 50) {
				state = Enm_Exit;
			} else ++cnt;
		break;
		
		case Enm_Exit:
		break;
		
		default:
		break;
	}
	
	switch(state) {
		case Enm_Start:
		break;
		
		case Enm_Update:
			++cnt;
			++exist_ticks;
			if (cnt % 5 == 0) ++frame;
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
		
		case Enm_Explode:
			if (cnt % 5 == 0) ++frame;
			anim_explode();
		break;
		
		case Enm_Exit:
			// Deactivate to disable drawing
			active = false;
		break;
		
		default:
		break;
	}
}

void Enemy::shoot() {
	switch(type) {
		case CROSS:
			cross_shoot();
		break;
		case LINE:
			line_shoot();
		break;
		case TRACER:
			tracer_shoot();
		break;
		case PANEL:
			panel_shoot();
		break;
		default:
		break;
	}
}

void Enemy::cross_shoot() {
	// rand velocity ring
	byte xv, yv = 0;
	while (xv == 0 && yv == 0) { // ensuring no stationary bullets
		xv = random(-2, 2);
		yv = random(-2, 2);
	}
	//enm_bullets.add(new EnmDot(x, y, xv, yv)); // simple
	xv, yv = 0;
	while (xv == 0 && yv == 0) {
		xv = random(-2, 2);
		yv = random(-2, 2);
	}
	//enm_bullets.add(new EnmDot(x, y, xv, yv));
	xv, yv = 0;
	while (xv == 0 && yv == 0) {
		xv = random(-2, 2);
		yv = random(-2, 2);
	}
	//enm_bullets.add(new EnmDot(x, y, xv, yv));
}

void Enemy::draw() {
	Send_To_Matrix(this);
}

void Enemy::line_shoot() {
	// spread shot
	byte offset = -1;
	for (byte i = 0; i < ES_MAX; ++i) {
		if (num_ES_active >= ES_MAX) break;
		if (!enm_bullets[i]->active) {
			enm_bullets[i]->create(DOT, x+offset, y, offset, 2); // ugly
		}
	}
}

void Enemy::tracer_shoot() {
	// fast firing single lasers
	//enm_bullets.add(new EnmLaser(x, y, random(-2, 2), random(1, 3)));
}

void Enemy::panel_shoot() {
	/*
	enm_bullets.add(new EnmBall(x, y, -3, 1));
	enm_bullets.add(new EnmBall(x, y, 3, 1));

	enm_bullets.add(new EnmLaser(x, y, random(-3, -2), 2));
	enm_bullets.add(new EnmLaser(x, y, random(-1, 1), 2));
	enm_bullets.add(new EnmLaser(x, y, random(2, 3), 2));
	*/
}

void Enemy::panel_anim_explode() {
	Send_To_Matrix(ANIM_BIG_EXPLODE, x, y, frame);
}
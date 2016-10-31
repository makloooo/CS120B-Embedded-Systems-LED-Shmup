#include "Enemy.h"

Enemy::Enemy(byte _x, byte _y, byte _x_vel, byte _y_vel, byte _time) {
	x = _x;
	y = _y;
	
	x_vel = _x_vel;
	y_vel = _y_vel;
	
	frame = 0;
	
	unlocked = false;
	
	exist_time = 0;
	expire_time = _time;
	
	// make sure to make director use list.add for push_back
	index = enms.size() - 1;
}

void Enemy::move() {
	x += x_vel;
	y += y_vel;
}

PlayerShot* Enemy::collision_check() {
	PlayerShot* tmp;
	for (byte i = 0; i < pl_bullets.size(); ++i) {
		tmp = pl_bullets.get(i);
		if ((tmp->x >= x-1 && tmp->x <= x+1)
			&& (tmp->y >= y-1 && tmp->y <= y+1)) return tmp;
	}
	return NULL;
}

void Enemy::anim_explode() {
	if (frame >= 3) return;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if(explode[frame][i][j]) matrix.drawPixel(x+j-1, y+i-1, Colors[WHITE]);
		}
	}
}

void Enemy::Open_Fire() {
	unlocked = true;
}

void Enemy::absorb_bullet(PlayerShot* b) {
	if (b == NULL) return;
	
	for (int i = b->index+1; i < pl_bullets.size(); ++i) --pl_bullets.get(i)->index;
	pl_bullets.remove(b->index);
	delete b; // oh god
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
			if (exist_time >= expire_time) state = Enm_Exit;
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
			++exist_time;
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
			// manage linked list before deleting
			for (int i = index+1; i < enms.size(); ++i) --enms.get(i)->index;
			enms.remove(index);
			delete this; // oh god
		break;
		
		default:
		break;
	}
}
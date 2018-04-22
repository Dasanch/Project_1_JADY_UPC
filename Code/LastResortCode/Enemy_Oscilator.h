#ifndef __ENEMY_OSCILATOR_H__
#define __ENEMY_OSCILATOR_H__

#include "Enemy.h"

class Enemy_Oscilator : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up=true;
	int original_y = 0;
	Animation Oscilator;

public:

	Enemy_Oscilator(int x, int y, powerupType pu_t);
	void Move();
};

#endif // __ENEMY_OSCILATOR_H__

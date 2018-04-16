#ifndef __ENEMY_DROPPER_H__
#define __ENEMY_DROPPER_H__

#include "Enemy.h"

class Enemy_PowerDropper : public Enemy
{
private:
	//float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_PowerDropper(int x, int y);

	void Move();
};

#endif // __ENEMY_DROPPER_H__

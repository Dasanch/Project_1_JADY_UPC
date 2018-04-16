#ifndef __ENEMY_BASIC_H__
#define __ENEMY_BASIC_H__

#include "Enemy.h"

class Enemy_Basic : public Enemy
{
private:
	//float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_Basic(int x, int y);

	void Move();
};

#endif // __ENEMY_BASIC_H__

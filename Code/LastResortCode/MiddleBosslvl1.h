#ifndef __ENEMY_METALCRAW_H__
#define __ENEMY_METALCRAW_H__

#include "Enemy.h"

class Enemy_MetalCraw_Torso : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation dropper;

public:

	Enemy_MetalCraw_Torso(int x, int y);

	void Move();
};

#endif // __ENEMY_METALCRAW_H__

#ifndef __ENEMY_BASIC_H__
#define __ENEMY_BASIC_H__

#include "Enemy.h"

class Enemy_Basic : public Enemy
{
private:
	
	bool going_up = true;
	Animation basicenemy;

public:

	Enemy_Basic(int x, int y);
	void Move();
};

#endif // __ENEMY_BASIC_H__

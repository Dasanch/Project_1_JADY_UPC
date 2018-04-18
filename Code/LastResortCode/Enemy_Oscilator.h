#ifndef __ENEMY_OSCILATOR_H__
#define __ENEMY_OSCILATOR_H__

#include "Enemy.h"

class Enemy_Oscilator : public Enemy
{
private:
	
	Animation Oscilator;

public:

	Enemy_Oscilator(int x, int y);
	void Move();
};

#endif // __ENEMY_OSCILATOR_H__

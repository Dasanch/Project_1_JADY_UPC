#ifndef __POWERUP_SPEED_H__
#define __POWERUP_SPEED_H__

#include "Powerup.h"

struct Collider;

class Powerup_Speed : public Powerup
{
public:
	Powerup_Speed(int x, int y);
	Animation speedAnim;
	void OnCollision(Collider*);
};

#endif // __POWERUP_SPEED_H__

#ifndef __POWERUP_SPEED_H__
#define __POWERUP_SPEED_H__

#include "Powerup.h"

class Powerup_Speed : public Powerup
{
public:
	Powerup_Speed(int x, int y);
	Animation speedAnim;
	//Effect on catch
};

#endif // __POWERUP_LASER_H__

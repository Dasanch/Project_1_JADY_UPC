#ifndef __POWERUP_LASER_H__
#define __POWERUP_LASER_H__

#include "Powerup.h"

class Powerup_Laser : public Powerup
{
public:
	Powerup_Laser(int x, int y);
	Animation laserAnim;
	//Effect on catch
};

#endif // __POWERUP_LASER_H__

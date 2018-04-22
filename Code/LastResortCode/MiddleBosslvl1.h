#ifndef __ENEMY_METALCRAW_H__
#define __ENEMY_METALCRAW_H__

#include "Enemy.h"
#include "SDL\include\SDL.h"
class Enemy_MetalCraw : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x;
	Animation torso;
	Animation Arm;
	Animation Lights;
	SDL_Rect Leg;

	Uint32 start_time = SDL_GetTicks();
	Uint32 current_time;
	int numparticles;
public:

	Enemy_MetalCraw(int x, int y, powerupType pu_t);

	void Move();
	void  Draw(SDL_Texture* sprites);
};


#endif // __ENEMY_METALCRAW_H__

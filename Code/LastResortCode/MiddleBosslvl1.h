#ifndef __ENEMY_METALCRAW_H__
#define __ENEMY_METALCRAW_H__

#include "Enemy.h"
#include "SDL\include\SDL.h"
class Enemy_MetalCraw_Torso : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation torso;
	Uint32 start_time = SDL_GetTicks();
	Uint32 current_time;
public:

	Enemy_MetalCraw_Torso(int x, int y);

	void Move();

};

class Enemy_MetalCraw_Arm : public Enemy
{
private:
	Animation Arm;
	Uint32 start_time = SDL_GetTicks();
	Uint32 current_time;
public:

	Enemy_MetalCraw_Arm(int x, int y);

	void Move();

};

#endif // __ENEMY_METALCRAW_H__

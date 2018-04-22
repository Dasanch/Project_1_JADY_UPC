#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Powerup
{
public:
	Animation* animation = nullptr;
	Collider* collider = nullptr;
	iPoint position;

public:
	Powerup(int x, int y);
	virtual ~Powerup();

	const Collider* GetCollider() const;
	virtual void OnCollision(Collider* collider);
};

#endif
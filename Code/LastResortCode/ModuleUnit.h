#ifndef __ModuleUnit_H__
#define __ModuleUnit_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleUnit : public Module
{
public:
	ModuleUnit();
	~ModuleUnit();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

public:
	Animation unitAnim;
	SDL_Texture* unitTx = nullptr;
	iPoint position;

	//We have an rotation (angular)
	//We'll be incrementing it when we move to a direction and decrement it when we move to another direction
	float rotation;
	const float rotateSpeed = 1;
	const float radius = 31;
};

#endif
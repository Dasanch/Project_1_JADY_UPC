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

	const int r = 31;//radius is 31 pixels (23 distance from the ship to the unit and 8 from the exterior of the unit to the center)
	int x;//x
	int y;//y

	const int rotateSpeed = 1;
};

#endif
#ifndef __ModuleUnit_H__
#define __ModuleUnit_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"

#define PI 3.14159265358979323846264338327950288

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
	void MoveCounterClock(float);//Limit when adding rotation
	void MoveClockWise(float);//Limit when substracting rotation

public:
	Animation unitAnim;
	SDL_Texture* unitTx = nullptr;
	iPoint position;

	//We have an rotation (angular)
	//We'll be incrementing it when we move to a direction and decrement it when we move to another direction
	float currentRotation = 0;
	float targetRotation;
	const float rotateSpeed = PI/20;
	const float radius = 31;
	bool moving = false;
	//const int xOffset = 6;
	//const int yOffset = -2;
	const float angleLeft = PI;
	const float angleRight = 0;
	const float angleUp = PI/2;
	const float angleDown = 3*PI/2;
};

#endif
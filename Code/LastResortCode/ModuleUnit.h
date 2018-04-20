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
	void Orbit(float);

public:
	Animation unitAnim;
	SDL_Texture* unitTx = nullptr;
	iPoint position;

private:
	float currentRotation;//The rotation we currently are. We'll be incrementing it when we move to a direction and decrement it when we move to another direction
	float targetRotation;//The rotation we want to be in
	bool moving;//A bool that indicates if the player is moving (pressing any keys)

	const float radius = 31;
	const float rotateSpeed = 3.141592 / 27;
	const float PI = 3.141592;
	const float angleLeft = PI;
	const float angleRight = 2 * PI;
	const float angleUp = 3 * PI / 2;
	const float angleDown = PI / 2;

};
#endif
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
	update_status Update();//Here we'll check for input, calculate the position of the unit (by calling the Orbit function) and rendering the unit
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void Orbit(float);//This function calculates the position of the unit around the ship
	void MoveClockwise();
	void MoveCounterclock();
	void Rotate(float);//This function calculates the rotatio of the unit

public:
	Animation unitAnim;
	SDL_Texture* unitTx = nullptr;
	iPoint position;

private:
	float currentRotation;//The current rotation of the unit. We'll be incrementing it when we move counterclock and decrementing it when we move clockwise
	float targetRotation;//The rotation we want the unit to be in
	bool moving;//A bool that indicates if the player is moving (pressing any keys)

	const float radius = 31;
	const float rotateSpeed = 3.141592 / 27;//The speed at which the orbit rotates around the player ship
	const float PI = 3.141592;
	const float angleLeft = PI;//The rotation (in radians) in which the unit will be at the left of the ship
	const float angleRight = 2 * PI;//The rotation (in radians) in which the unit will be at the right of the ship
	const float angleUp = 3 * PI / 2;//The rotation (in radians) in which the unit will be above the ship
	const float angleDown = PI / 2;//The rotation (in radians) in which the unit will be bellow the ship

};
#endif
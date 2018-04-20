#ifndef __ModuleUnit_H__
#define __ModuleUnit_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"

#define frames 8

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
	iPoint position;

private:
	//Rotation
	float currentOrbit;//The current rotation of the unit. We'll be incrementing it when we move counterclock and decrementing it when we move clockwise
	float targetOrbit;//The rotation we want the unit to be in
	bool moving;//A bool that indicates if the player is moving (pressing any keys)
	const float radius = 31;
	const float rotateSpeed = 3.141592 / 27;//The speed at which the orbit rotates around the player ship
	const float PI = 3.141592;
	const float angleLeft = PI;//The rotation (in radians) in which the unit will be at the left of the ship
	const float angleRight = 2 * PI;//The rotation (in radians) in which the unit will be at the right of the ship
	const float angleUp = 3 * PI / 2;//The rotation (in radians) in which the unit will be above the ship
	const float angleDown = PI / 2;//The rotation (in radians) in which the unit will be bellow the ship

	//Animations
	//There is an aniumation for each direciton of the ball. s (south), n (north), e (east), w (west)
	SDL_Texture* unitTx = nullptr;
	//Straight
	SDL_Rect nAnim[frames];
	SDL_Rect wAnim[frames];
	SDL_Rect eAnim[frames];
	SDL_Rect sAnim[frames];
	//Diagonals
	SDL_Rect neAnim[frames];
	SDL_Rect nwAnim[frames];
	SDL_Rect seAnim[frames];
	SDL_Rect swAnim[frames];
	//Transition diagonals
	SDL_Rect nneAnim[frames];
	SDL_Rect neeAnim[frames];
	SDL_Rect seeAnim[frames];
	SDL_Rect sseAnim[frames];
	SDL_Rect sswAnim[frames];
	SDL_Rect swwAnim[frames];
	SDL_Rect nwwAnim[frames];
	SDL_Rect nnwAnim[frames];
};
#endif
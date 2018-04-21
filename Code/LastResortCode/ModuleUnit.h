#ifndef __ModuleUnit_H__
#define __ModuleUnit_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModulePlayer.h"

#define frames 8
#define axis 16

struct SDL_Texture;
struct Collider;

enum Angles
{
	//S (south), N (north), E (east), W (west)
	E = 0, ESE, SE, SSE, S, SSW, SW, WSW, W, WNW, NW, NNW, N, NNE, NE, ENE
};

enum UnitType
{
	orange,
	blue
};

struct InternalRotationAnimations
{
	SDL_Rect frame [frames];
};

class ModuleUnit : public Module
{
public:
	ModuleUnit();
	~ModuleUnit();

	bool Start();
	update_status Update();//Here we'll check for input, calculate the position of the unit (by calling the Orbit function) and rendering the unit
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void RotateTo(float, float&, float);//This function calculates the rotation of the orbit and the internal rotation of the unit
	void LimitRotation(float &);
	int SpinToRender();

public:
	iPoint position;

private:
	
	ModulePlayer* playerToFollow = nullptr;//Ship it has to follow
	UnitType type;
	Collider* unitCol = nullptr;
	//Rotation
	const float PI = 3.141592;
	//- Orbit refers to the rotation of the unit around the player's ship
	//- Spin refers to the rotation of the unit to aim at different directions
	//- InternalRotation refers to the rotation of the unit on its own axis
	float targetOrbit;//The rotation we want the unit to be in
	float currentOrbit;//We'll be incrementing it when we move counterclock and decrementing it when we move clockwise
	const float orbitSpeed = 3.141592 / 27;//The speed at which the orbit rotates around the player ship
	float currentSpin;
	const float spinSpeed = orbitSpeed * 2;
	int spinToRender;
	float currentInternalRotation;
	const float internalRotationSpeed = 0.2f;
	bool moving;//A bool that indicates if the player is moving (pressing any keys)
	const float radius = 31;
	float angleValue[axis];//The value of each angle
	const float angleSeparation = PI / 16;//The separation between the angles (helps us calculate which animation we have to play)
	int spriteXDifferences[axis] = { 1, 1, 1, 1, 1, 2, 6, 7, 7, 7, 6, 2, 1, 1, 1, 1 };//Sprite differences in x
	int spriteYDifferences[axis] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 6, 8, 7, 8, 6, 2 };//Sprite differences in y
	int colXDifferences[axis] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	int colYDifferences[axis] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 11, 10, 10, 1, 10, 3 };
	const float unitProjectileSpeed = 5;
	//Animations
	//There is an animation for each direciton of the ball
	SDL_Texture* unitTx = nullptr;
	InternalRotationAnimations internalRotationAnim[axis];
};
#endif
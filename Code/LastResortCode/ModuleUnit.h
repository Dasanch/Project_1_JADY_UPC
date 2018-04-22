#ifndef __ModuleUnit_H__
#define __ModuleUnit_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModulePlayer.h"

#define internalRotationFrames 8
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
	SDL_Rect frame [internalRotationFrames];
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
	ModulePlayer* playerToFollow = nullptr;//Ship it has to follow
	UnitType type;
	Collider* unitCol = nullptr;
	float currentOrbit;//We'll be incrementing it when we move counterclock and decrementing it when we move clockwise
	float currentSpin;
	float angleValue[axis];//The value of each angle

private:
	
	//Rotation
	const float PI = 3.141592;
	//- Orbit refers to the rotation of the unit around the player's ship
	//- Spin refers to the rotation of the unit to aim at different directions
	//- InternalRotation refers to the rotation of the unit on its own axis
	float targetOrbit;//The rotation we want the unit to be in
	const float orbitSpeed = 3.141592 / 27;//The speed at which the orbit rotates around the player ship
	const float spinSpeed = orbitSpeed * 2;
	int spinToRender;
	float currentInternalRotation;
	const float internalRotationSpeed = 0.2f;
	bool orbiting;//A bool that indicates if we can make the unit orbit
	bool spinning;//A bool that indicates if we can make the unit spin
	bool hideUnit = false;
	const float radius = 31;
	const float angleSeparation = PI / 16;//The separation between the angles (helps us calculate which animation we have to play)
                                    //   E, ESE,  SE, SSE,   S, SSW,  SW, WSW,   W, WNW,  NW, NNW,   N, NNE,  NE, ENE
	int spriteXDifferences[axis] =  {    8,   8,   8,   8,   8,   9,  13,  14,  14,  14,  13,   9,   8,   8,   8,   8 };//Sprite differences in x and y, helps us keep the unit centered on its trajectory
	int spriteYDifferences[axis] =  {    8,   8,   8,   8,   8,   8,   8,   8,   8,   9,  13,  15,  14,  15,  13,   9 };
	int shotPosXDifferences[axis] = {   15,  14,  12,   6,   0,  -5, -11, -13, -14, -13, -11,  -6,   0,   6,  11,  14 };//Helps us position the orbit projectile at the top of its antenas
	int shotPosYDifferences[axis] = {    0,   7,  12,  14,  15,  14,  12,   6,   0,  -6, -11, -14, -14, -13, -10,  -6 };
	const float unitProjectileSpeed = 6 + 1;//6= pixels it moves each frame, 1 = speed at which the camera moves backwards
	//The speed is not correctly true because when the particle goes back, it will have + 1 speed, because the camera moves to the back
	//Animations
	//There is an animation for each direciton of the ball
	SDL_Texture* unitTx = nullptr;
	InternalRotationAnimations internalRotationAnim[axis];
};
#endif
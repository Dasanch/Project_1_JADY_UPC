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
	void RotateTo(float, float&, float);//This function calculates the rotation of the orbit and the internal rotation of the unit
	void LimitRotation(float &);

public:
	iPoint position;

private:
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
	float currentInternalRotation;
	const float internalRotationSpeed = 0.2f;
	bool moving;//A bool that indicates if the player is moving (pressing any keys)
	const float radius = 31;

	const float angleW = PI;//The angle in which the player will be at the west of the ship
	const float angleE = 2 * PI;
	const float angleN = 3 * PI / 2;
	const float angleS = PI / 2;
	const float angleNE = 7 * PI / 4;
	const float angleSE = PI / 4;
	const float angleSO = 3 * PI / 4;
	const float angleNO = 5 * PI / 4;
	const float angleNNE = 5 * PI / 3;
	const float angleENE = 11 * PI / 6;
	const float agnleESE = PI / 6;
	const float angleSSE = PI / 3;
	const float angleSSO = 2 * PI / 3;
	const float angleOSO = 5 * PI / 6;
	const float angleONO = 7 * PI / 6;
	const float angleNNO = 4 * PI / 3;

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
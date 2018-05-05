#include "Globals.h"
#include "Application.h"
#include "ModuleUnit.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "Player1.h"
#include <stdio.h>
#include <math.h>

ModuleUnit::ModuleUnit() //Constructor 
{
	//Define the angle values
	angleValue[E] = 2 * PI;
	angleValue[ESE] = PI / 8;
	angleValue[SE] = PI / 4;
	angleValue[SSE] = angleValue[SE] + PI / 8;
	angleValue[S] = PI / 2;
	angleValue[SSW] = angleValue[S] + PI / 8;
	angleValue[SW] = 3 * PI / 4;
	angleValue[WSW] = angleValue[SW] + PI / 8;
	angleValue[W] = PI;
	angleValue[WNW] = angleValue[W] + PI / 8;
	angleValue[NW] = 5 * PI / 4;
	angleValue[NNW] = angleValue[NW] + PI / 8;
	angleValue[N] = 3 * PI / 2;
	angleValue[NNE] = angleValue[N] + PI / 8;
	angleValue[NE] = 7 * PI / 4;
	angleValue[ENE] = angleValue[NE] + PI / 8;
	//Push backs
	//- North
	internalRotationAnim[N].frame[0] = {  48, 61, 16, 22 };
	internalRotationAnim[N].frame[1] = {  32, 61, 16, 22 };
	internalRotationAnim[N].frame[2] = {  16, 61, 16, 22 };
	internalRotationAnim[N].frame[3] = {   0, 61, 16, 22 };
	internalRotationAnim[N].frame[4] = { 226, 38, 16, 22 };
	internalRotationAnim[N].frame[5] = { 210, 38, 16, 22 };
	internalRotationAnim[N].frame[6] = { 194, 38, 16, 22 };
	internalRotationAnim[N].frame[7] = { 178, 38, 16, 22 };
	//- West
	internalRotationAnim[W].frame[0] = { 220, 105, 22, 16 };
	internalRotationAnim[W].frame[1] = { 198, 105, 22, 16 };
	internalRotationAnim[W].frame[2] = { 176, 105, 22, 16 };
	internalRotationAnim[W].frame[3] = { 154, 105, 22, 16 };
	internalRotationAnim[W].frame[4] = { 132, 105, 22, 16 };
	internalRotationAnim[W].frame[5] = { 110, 105, 22, 16 };
	internalRotationAnim[W].frame[6] = {  88, 105, 22, 16 };
	internalRotationAnim[W].frame[7] = {  66, 105 ,22, 16 };
	//- East
	internalRotationAnim[E].frame[0] = { 154, 0, 22, 16 };
	internalRotationAnim[E].frame[1] = { 132, 0, 22, 16 };
	internalRotationAnim[E].frame[2] = { 110, 0, 22, 16 };
	internalRotationAnim[E].frame[3] = {  88, 0, 22, 16 };
	internalRotationAnim[E].frame[4] = {  66, 0, 22, 16 };
	internalRotationAnim[E].frame[5] = {  44, 0, 22, 16 };
	internalRotationAnim[E].frame[6] = {  22, 0, 22, 16 };
	internalRotationAnim[E].frame[7] = {   0, 0, 22, 16 };
	//- South
	internalRotationAnim[S].frame[0] = { 112, 166, 16, 22 };
	internalRotationAnim[S].frame[1] = {  96, 166, 16, 22 };
	internalRotationAnim[S].frame[2] = {  80, 166, 16, 22 };
	internalRotationAnim[S].frame[3] = {  64, 166, 16, 22 };
	internalRotationAnim[S].frame[4] = {  48, 166, 16, 22 };
	internalRotationAnim[S].frame[5] = {  32, 166, 16, 22 };
	internalRotationAnim[S].frame[6] = {  16, 166, 16, 22 };
	internalRotationAnim[S].frame[7] = {   0, 166, 16, 22 };
	//- North east
	internalRotationAnim[NE].frame[0] = {  21, 38, 21, 21 };
	internalRotationAnim[NE].frame[1] = {   0, 38, 21, 21 };
	internalRotationAnim[NE].frame[2] = { 215, 17, 21, 21 };
	internalRotationAnim[NE].frame[3] = { 194, 17, 21, 21 };
	internalRotationAnim[NE].frame[4] = { 173, 17, 21, 21 };
	internalRotationAnim[NE].frame[5] = { 152, 17, 21, 21 };
	internalRotationAnim[NE].frame[6] = { 131, 17, 21, 21 };
	internalRotationAnim[NE].frame[7] = { 110, 17, 21, 21 };
	//- North west
	internalRotationAnim[NW].frame[0] = { 105, 84, 21, 21 };
	internalRotationAnim[NW].frame[1] = {  84, 84, 21, 21 };
	internalRotationAnim[NW].frame[2] = {  63, 84, 21, 21 };
	internalRotationAnim[NW].frame[3] = {  42, 84, 21, 21 };
	internalRotationAnim[NW].frame[4] = {  21, 84, 21, 21 };
	internalRotationAnim[NW].frame[5] = {   0, 84, 21, 21 };
	internalRotationAnim[NW].frame[6] = { 221, 61, 21, 21 };
	internalRotationAnim[NW].frame[7] = { 200, 61, 21, 21 };
	//- South east
	internalRotationAnim[SE].frame[0] = { 164, 189, 21, 21 };
	internalRotationAnim[SE].frame[1] = { 143, 189, 21, 21 };
	internalRotationAnim[SE].frame[2] = { 122, 189, 21, 21 };
	internalRotationAnim[SE].frame[3] = { 101, 189, 21, 21 };
	internalRotationAnim[SE].frame[4] = {  80, 189, 21, 21 };
	internalRotationAnim[SE].frame[5] = {  59, 189, 21, 21 };
	internalRotationAnim[SE].frame[6] = {  38, 189, 21, 21 };
	internalRotationAnim[SE].frame[7] = {  17, 189, 21, 21 };
	//- South west
	internalRotationAnim[SW].frame[0] = {  84, 143, 21, 21 };
	internalRotationAnim[SW].frame[1] = {  63, 143, 21, 21 };
	internalRotationAnim[SW].frame[2] = {  42, 143, 21, 21 };
	internalRotationAnim[SW].frame[3] = {  21, 143, 21, 21 };
	internalRotationAnim[SW].frame[4] = {   0, 143, 21, 21 };
	internalRotationAnim[SW].frame[5] = { 218, 122, 21, 21 };
	internalRotationAnim[SW].frame[6] = { 197, 122, 21, 21 };
	internalRotationAnim[SW].frame[7] = { 176, 122, 21, 21 };
	//- North north east
	internalRotationAnim[NNE].frame[0] = { 161, 38, 17, 23 };
	internalRotationAnim[NNE].frame[1] = { 144, 38, 17, 23 };
	internalRotationAnim[NNE].frame[2] = { 127, 38, 17, 23 };
	internalRotationAnim[NNE].frame[3] = { 110, 38, 17, 23 };
	internalRotationAnim[NNE].frame[4] = {  93, 38, 17, 23 };
	internalRotationAnim[NNE].frame[5] = {  76, 38, 17, 23 };
	internalRotationAnim[NNE].frame[6] = {  59, 38, 17, 23 };
	internalRotationAnim[NNE].frame[7] = {  42, 38, 17, 23 };
	//- North east east
	internalRotationAnim[ENE].frame[0] = {  88, 17, 22, 17 };
	internalRotationAnim[ENE].frame[1] = {  66, 17, 22, 17 };
	internalRotationAnim[ENE].frame[2] = {  44, 17, 22, 17 };
	internalRotationAnim[ENE].frame[3] = {  22, 17, 22, 17 };
	internalRotationAnim[ENE].frame[4] = {   0, 17, 22, 17 };
	internalRotationAnim[ENE].frame[5] = { 220,  0, 22, 17 };
	internalRotationAnim[ENE].frame[6] = { 198,  0, 22, 17 };
	internalRotationAnim[ENE].frame[7] = { 176,  0, 22, 17 };
	//- South east east
	internalRotationAnim[ESE].frame[0] = {  88, 212, 22, 17 };
	internalRotationAnim[ESE].frame[1] = {  66, 212, 22, 17 };
	internalRotationAnim[ESE].frame[2] = {  44, 212, 22, 17 };
	internalRotationAnim[ESE].frame[3] = {  22, 212, 22, 17 };
	internalRotationAnim[ESE].frame[4] = {   0, 212, 22, 17 };
	internalRotationAnim[ESE].frame[5] = { 229, 189, 22, 17 };
	internalRotationAnim[ESE].frame[6] = { 207, 189, 22, 17 };
	internalRotationAnim[ESE].frame[7] = { 185, 189, 22, 17 };
	//- South south east
	internalRotationAnim[SSE].frame[0] = {   0, 189, 17, 23 };
	internalRotationAnim[SSE].frame[1] = { 230, 166, 17, 23 };
	internalRotationAnim[SSE].frame[2] = { 213, 166, 17, 23 };
	internalRotationAnim[SSE].frame[3] = { 196, 166, 17, 23 };
	internalRotationAnim[SSE].frame[4] = { 179, 166, 17, 23 };
	internalRotationAnim[SSE].frame[5] = { 162, 166, 17, 23 };
	internalRotationAnim[SSE].frame[6] = { 145, 166, 17, 23 };
	internalRotationAnim[SSE].frame[7] = { 128, 166, 17, 23 };
	//- South south west
	internalRotationAnim[SSW].frame[0] = { 224, 143, 17, 23 };
	internalRotationAnim[SSW].frame[1] = { 207, 143, 17, 23 };
	internalRotationAnim[SSW].frame[2] = { 190, 143, 17, 23 };
	internalRotationAnim[SSW].frame[3] = { 173, 143, 17, 23 };
	internalRotationAnim[SSW].frame[4] = { 156, 143, 17, 23 };
	internalRotationAnim[SSW].frame[5] = { 139, 143, 17, 23 };
	internalRotationAnim[SSW].frame[6] = { 122, 143, 17, 23 };
	internalRotationAnim[SSW].frame[7] = { 105, 143, 17, 23 };
	//- Shouth west west
	internalRotationAnim[WSW].frame[0] = { 154, 122, 22, 17 };
	internalRotationAnim[WSW].frame[1] = { 132, 122, 22, 17 };
	internalRotationAnim[WSW].frame[2] = { 110, 122, 22, 17 };
	internalRotationAnim[WSW].frame[3] = {  88, 122, 22, 17 };
	internalRotationAnim[WSW].frame[4] = {  66, 122, 22, 17 };
	internalRotationAnim[WSW].frame[5] = {  44, 122, 22, 17 };
	internalRotationAnim[WSW].frame[6] = {  22, 122, 22, 17 };
	internalRotationAnim[WSW].frame[7] = {   0, 122, 22, 17 };
	//- North west west
	internalRotationAnim[WNW].frame[0] = {  44, 105, 22, 17 };
	internalRotationAnim[WNW].frame[1] = {  22, 105, 22, 17 };
	internalRotationAnim[WNW].frame[2] = {   0, 105, 22, 17 };
	internalRotationAnim[WNW].frame[3] = { 214,  84, 22, 17 };
	internalRotationAnim[WNW].frame[4] = { 192,  84, 22, 17 };
	internalRotationAnim[WNW].frame[5] = { 170,  84, 22, 17 };
	internalRotationAnim[WNW].frame[6] = { 148,  84, 22, 17 };
	internalRotationAnim[WNW].frame[7] = { 126,  84, 22, 17 };
	//- North north west
	internalRotationAnim[NNW].frame[0] = { 183, 61, 17, 23 };
	internalRotationAnim[NNW].frame[1] = { 166, 61, 17, 23 };
	internalRotationAnim[NNW].frame[2] = { 149, 61, 17, 23 };
	internalRotationAnim[NNW].frame[3] = { 132, 61, 17, 23 };
	internalRotationAnim[NNW].frame[4] = { 115, 61, 17, 23 };
	internalRotationAnim[NNW].frame[5] = {  98, 61, 17, 23 };
	internalRotationAnim[NNW].frame[6] = {  81, 61, 17, 23 };
	internalRotationAnim[NNW].frame[7] = {  64, 61, 17, 23 };
}

ModuleUnit::~ModuleUnit()
{

}

bool ModuleUnit::Start()
{
	bool ret = true;
	LOG("Loading unit assets");
	//Load assets
	unitTx = App->textures->Load("Assets/OrangeUnitSpritesheet.png");
	currentOrbit = currentSpin = angleValue[E];
	unitCol = App->collision->AddCollider({ position.x, position.y, 16, 16 }, COLLIDER_INDESTRUCTIBLE, this);
	return ret;
}

bool ModuleUnit::CleanUp()
{
	LOG("Unloading unit assets");
	App->textures->Unload(unitTx);
	return true;
}

update_status ModuleUnit::Update()
{
	//Initial set up--------------------------------------------------------------------------------------
	//- We update our moving bool to false, if any key is pressed, it will go to true
	orbiting = false;
	spinning = false;

	//Conditions for movement-----------------------------------------------------------------------------
	if (playerToFollow->MoveLeft() == true)
	{
		orbiting = true;
		spinning = true;
		//- The unit goes to the right (the unit always goes to the opposite direction that we're moving to)
		targetOrbit = angleValue[E];
	}
	if (playerToFollow->MoveRight() == true)
	{
		orbiting = true;
		spinning = true;
		//- The unit goes to the left (the unit always goes to the opposite direction that we're moving to)
		targetOrbit = angleValue[W];
	}
	if (playerToFollow->MoveUp() == true)
	{
		orbiting = true;
		spinning = true;
		//- The unit moves down (the unit always goes to the opposite direction that we're moving to)
		targetOrbit = angleValue[S];
		//- We check if a part from going down, it's also going to one of the sides (for the diagonals)
		if (playerToFollow->MoveLeft() == true) { targetOrbit -= PI / 4; }
		if (playerToFollow->MoveRight() == true) { targetOrbit += PI / 4; }
	}
	if (playerToFollow->MoveDown() == true)
	{
		orbiting = true;
		spinning = true;
		//- The unit goes up (the unit always goes to the opposite direction that we're moving to)
		targetOrbit = angleValue[N];
		//- We check if a part from going up, it's also going to one of the sides (for the diagonals)
		if (playerToFollow->MoveLeft() == true) { targetOrbit += PI / 4; }
		if (playerToFollow->MoveRight() == true) { targetOrbit -= PI / 4; }
	}

	//If the ball is locked it won't rotate around the player ship
	if (playerToFollow->unit_locked == true) { orbiting = false; }

	//Move the orbit to the target rotation---------------------------------------------------------------
	//- Orbit around the player
	if (orbiting == true) { RotateTo(targetOrbit, currentOrbit, orbitSpeed); }
	//- Rotation of the unit itself
	if (spinning == true) { RotateTo(targetOrbit, currentSpin, spinSpeed); }

	//Limit the rotation----------------------------------------------------------------------------------
	//- On the orbit
	if (orbiting == true) { LimitRotation(currentOrbit); }
	//- On the spin
	if (spinning == true) { LimitRotation(currentSpin); }

	//- We grab the spin we need to render--------------------------------------------------------------------
	spinToRender = SpinToRender();

	//Set the position----------------------------------------------------------------------------------------
	position.x = radius * cosf(currentOrbit) + playerToFollow->position.x + 16;//+ 16 and + 6 are to make the unit orbit around the center of the player's ship
	position.y = radius * sinf(currentOrbit) + playerToFollow->position.y + 6;

	//Update the collider position (after having set its position)--------------------------------------------
	unitCol->SetPos(position.x - 8, position.y - 8);//- 8 is because the sphere part of the unit has 8 witdh and 8 height, so since the position.x and position.y are in the center in the trajectory, we just need to substract them from that to get the position of the collider

	//Increase the internal rotation--------------------------------------------------------------------------
	currentInternalRotation += internalRotationSpeed;

	//- Limit the internal rotation
	if (currentInternalRotation >= internalRotationFrames) { currentInternalRotation = 0; }

	//Set the rotation and render (all in the same place)-----------------------------------------------------
	App->render->Blit(unitTx,
		position.x - spriteXDifferences[spinToRender],
		position.y - spriteYDifferences[spinToRender],
		&internalRotationAnim[spinToRender].frame[(int)currentInternalRotation]);

	//Shoot---------------------------------------------------------------------------------------------------
	App->particles->unitShot.speed.x = unitProjectileSpeed * cosf(angleValue[spinToRender]);
	App->particles->unitShot.speed.y = unitProjectileSpeed * sinf(angleValue[spinToRender]);
	if(playerToFollow->Shoot() == true)
	{
		App->particles->AddParticle(
			App->particles->unitShot,
			position.x + shotPosXDifferences[spinToRender],
			position.y + shotPosYDifferences[spinToRender],
			playerToFollow->PlayerTexture,
			playerToFollow->shot_colType,
			0);
	}
	return UPDATE_CONTINUE;
}

//This function has a series of if statatements that do the following
//First if  --> Finds the rotation we want to go to
//Second if --> Determines which distance from the currentRotation to the targetRotation is shorter
//Third if  --> Go to that direction, until we get at it
void ModuleUnit::RotateTo(float targetRotation, float &currentRotation, float speed)
{
	//We create a variable that's going to store the opposite rotation from the targetRotation
	float oppositeRotation;

	//Check if the target rotation is down or one of the lower diagonals
	if (targetRotation == angleValue[S] || targetRotation == angleValue[SE] || targetRotation == angleValue[SW])
	{
		oppositeRotation = targetRotation + PI;
		//Check which way is shorter
		if (currentRotation <= oppositeRotation && currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation < targetRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation > oppositeRotation)
		{
			//Move counterclock
			currentRotation += speed;
		}
	}

	//Check if the target rotation is up or one of the upper diagonals
	else if (targetRotation == angleValue[N] || targetRotation == angleValue[NE] || targetRotation == angleValue[NW])
	{
		oppositeRotation = targetRotation - PI;
		//Check which way is shorter
		if (currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation <= oppositeRotation)
		{
			//Move clockwise
			currentRotation -= speed;
		}
		else if (currentRotation < targetRotation && currentRotation > oppositeRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}

	//Check if the target rotation is left
	else if (targetRotation == angleValue[W])
	{
		//Check which way is shorter
		if (currentRotation == 0 || currentRotation > targetRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation < targetRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}

	//Check if the target rotation is right
	else if (targetRotation == angleValue[E])
	{
		oppositeRotation = angleValue[W];
		//Check which way is shorter
		if (currentRotation <= oppositeRotation)
		{
			//Move clockwise
			//Only add if it hasn't reached its limit
			if (currentRotation > speed) { currentRotation -= speed; }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation > oppositeRotation)
		{
			//Move counterclock
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - speed) { currentRotation += speed; }
			else { currentRotation = targetRotation; }
		}
	}
}

void ModuleUnit::LimitRotation(float &rotation)
{
	//- Limit the rotation to positive numbers (after modifing it)
	if (rotation < 0)
	{
		rotation = 2 * PI + rotation;//We add the rotation because it's negative, so it will efectively substract it
	}
	//- Limit the rotation to one circle
	while (rotation > 2 * PI)
	{
		rotation -= 2 * PI;
	}
}

int ModuleUnit::SpinToRender()
{
	//Start with the exception (E)
	if(currentSpin > angleValue[E] - angleSeparation || currentSpin <= 0 + angleSeparation) { return E; }
	//Then go through all the other cases
	else if (currentSpin >= angleValue[ESE] - angleSeparation && currentSpin < angleValue[ESE] + angleSeparation) { return ESE; }
	else if (currentSpin >= angleValue[SE] - angleSeparation && currentSpin < angleValue[SE] + angleSeparation) { return SE; }
	else if (currentSpin >= angleValue[SSE] - angleSeparation && currentSpin < angleValue[SSE] + angleSeparation) { return SSE; }
	else if (currentSpin >= angleValue[S] - angleSeparation && currentSpin < angleValue[S] + angleSeparation) { return S; }
	else if (currentSpin >= angleValue[SSW] - angleSeparation && currentSpin < angleValue[SSW] + angleSeparation) { return SSW; }
	else if (currentSpin >= angleValue[SW] - angleSeparation && currentSpin < angleValue[SW] + angleSeparation) { return SW; }
	else if (currentSpin >= angleValue[WSW] - angleSeparation && currentSpin < angleValue[WSW] + angleSeparation) { return WSW; }
	else if (currentSpin >= angleValue[W] - angleSeparation && currentSpin < angleValue[W] + angleSeparation) { return W; }
	else if (currentSpin >= angleValue[WNW] - angleSeparation && currentSpin < angleValue[WNW] + angleSeparation) { return WNW; }
	else if (currentSpin >= angleValue[NW] - angleSeparation && currentSpin < angleValue[NW] + angleSeparation) { return NW; }
	else if (currentSpin >= angleValue[NNW] - angleSeparation && currentSpin < angleValue[NNW] + angleSeparation) { return NNW; }
	else if (currentSpin >= angleValue[N] - angleSeparation && currentSpin < angleValue[N] + angleSeparation) { return N; }
	else if (currentSpin >= angleValue[NNE] - angleSeparation && currentSpin < angleValue[NNE] + angleSeparation) { return NNE; }
	else if (currentSpin >= angleValue[NE] - angleSeparation && currentSpin < angleValue[NE] + angleSeparation) { return NE; }
	else if (currentSpin >= angleValue[ENE] - angleSeparation && currentSpin < angleValue[ENE] + angleSeparation) { return ENE; }
	//In case that it didn't return anything before, we'll return the E position, just so that we don't get an errror (this should never execute)
	LOG("Unit spin not found, returning east direction");
	return E;
}

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{

}


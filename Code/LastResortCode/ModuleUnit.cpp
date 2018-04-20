#include "Globals.h"
#include "Application.h"
#include "ModuleUnit.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Player1.h"
#include <stdio.h>
#include <math.h>

ModuleUnit::ModuleUnit() //Constructor 
{
	//Push backs
	//- North
	nAnim[0] = {  48, 61, 16, 22 };
	nAnim[1] = {  32, 61, 16, 22 };
	nAnim[2] = {  16, 61, 16, 22 };
	nAnim[3] = {   0, 61, 16, 22 };
	nAnim[4] = { 226, 38, 16, 22 };
	nAnim[5] = { 210, 38, 16, 22 };
	nAnim[6] = { 194, 38, 16, 22 };
	nAnim[7] = { 178, 38, 16, 22 };
	//- West
	wAnim[0] = { 220, 105, 22, 16 };
	wAnim[1] = { 198, 105, 22, 16 };
	wAnim[2] = { 176, 105, 22, 16 };
	wAnim[3] = { 154, 105, 22, 16 };
	wAnim[4] = { 132, 105, 22, 16 };
	wAnim[5] = { 110, 105, 22, 16 };
	wAnim[6] = {  88, 105, 22, 16 };
	wAnim[7] = {  66, 105 ,22, 16 };
	//- East
	eAnim[0] = { 154, 0, 22, 16 };
	eAnim[1] = { 132, 0, 22, 16 };
	eAnim[2] = { 110, 0, 22, 16 };
	eAnim[3] = {  88, 0, 22, 16 };
	eAnim[4] = {  66, 0, 22, 16 };
	eAnim[5] = {  44, 0, 22, 16 };
	eAnim[6] = {  22, 0, 22, 16 };
	eAnim[7] = {   0, 0, 22, 16 };
	//- South
	sAnim[0] = { 112, 166, 16, 22 };
	sAnim[1] = {  96, 166, 16, 22 };
	sAnim[2] = {  80, 166, 16, 22 };
	sAnim[3] = {  64, 166, 16, 22 };
	sAnim[4] = {  48, 166, 16, 22 };
	sAnim[5] = {  32, 166, 16, 22 };
	sAnim[6] = {  16, 166, 16, 22 };
	sAnim[7] = {   0, 166, 16, 22 };
	//- North east
	neAnim[0] = {  21, 38, 21, 21 };
	neAnim[1] = {   0, 38, 21, 21 };
	neAnim[2] = { 215, 17, 21, 21 };
	neAnim[3] = { 194, 17, 21, 21 };
	neAnim[4] = { 173, 17, 21, 21 };
	neAnim[5] = { 152, 17, 21, 21 };
	neAnim[6] = { 131, 17, 21, 21 };
	neAnim[7] = { 110, 17, 21, 21 };
	//- North west
	nwAnim[0] = { 105, 84, 21, 21 };
	nwAnim[1] = {  84, 84, 21, 21 };
	nwAnim[2] = {  63, 84, 21, 21 };
	nwAnim[3] = {  42, 84, 21, 21 };
	nwAnim[4] = {  21, 84, 21, 21 };
	nwAnim[5] = {   0, 84, 21, 21 };
	nwAnim[6] = { 221, 61, 21, 21 };
	nwAnim[7] = { 200, 61, 21, 21 };
	//- South east
	seAnim[0] = { 164, 189, 21, 21 };
	seAnim[1] = { 143, 189, 21, 21 };
	seAnim[2] = { 122, 189, 21, 21 };
	seAnim[3] = { 101, 189, 21, 21 };
	seAnim[4] = {  80, 189, 21, 21 };
	seAnim[5] = {  59, 189, 21, 21 };
	seAnim[6] = {  38, 189, 21, 21 };
	seAnim[7] = {  17, 189, 21, 21 };
	//- South west
	swAnim[0] = {  84, 143, 21, 21 };
	swAnim[1] = {  63, 143, 21, 21 };
	swAnim[2] = {  42, 143, 21, 21 };
	swAnim[3] = {  21, 143, 21, 21 };
	swAnim[4] = {   0, 143, 21, 21 };
	swAnim[5] = { 218, 122, 21, 21 };
	swAnim[6] = { 197, 122, 21, 21 };
	swAnim[7] = { 176, 122, 21, 21 };
	//- North north east
	nneAnim[0] = { 161, 38, 17, 23 };
	nneAnim[1] = { 144, 38, 17, 23 };
	nneAnim[2] = { 127, 38, 17, 23 };
	nneAnim[3] = { 110, 38, 17, 23 };
	nneAnim[4] = {  93, 38, 17, 23 };
	nneAnim[5] = {  76, 38, 17, 23 };
	nneAnim[6] = {  59, 38, 17, 23 };
	nneAnim[7] = {  42, 38, 17, 23 };
	//- North east east
	neeAnim[0] = {  88, 17, 22, 17 };
	neeAnim[1] = {  66, 17, 22, 17 };
	neeAnim[2] = {  44, 17, 22, 17 };
	neeAnim[3] = {  22, 17, 22, 17 };
	neeAnim[4] = {   0, 17, 22, 17 };
	neeAnim[5] = { 220,  0, 22, 17 };
	neeAnim[6] = { 198,  0, 22, 17 };
	neeAnim[7] = { 176,  0, 22, 17 };
	//- South east east
	seeAnim[0] = {  88, 212, 22, 17 };
	seeAnim[1] = {  66, 212, 22, 17 };
	seeAnim[2] = {  44, 212, 22, 17 };
	seeAnim[3] = {  22, 212, 22, 17 };
	seeAnim[4] = {   0, 212, 22, 17 };
	seeAnim[5] = { 229, 189, 22, 17 };
	seeAnim[6] = { 207, 189, 22, 17 };
	seeAnim[7] = { 185, 189, 22, 17 };
	//- South south east
	sseAnim[0] = {   0, 189, 17, 23 };
	sseAnim[1] = { 230, 166, 17, 23 };
	sseAnim[2] = { 213, 166, 17, 23 };
	sseAnim[3] = { 196, 166, 17, 23 };
	sseAnim[4] = { 179, 166, 17, 23 };
	sseAnim[5] = { 162, 166, 17, 23 };
	sseAnim[6] = { 145, 166, 17, 23 };
	sseAnim[7] = { 128, 166, 17, 23 };
	//- South south west
	sswAnim[0] = { 224, 143, 17, 23 };
	sswAnim[1] = { 207, 143, 17, 23 };
	sswAnim[2] = { 190, 143, 17, 23 };
	sswAnim[3] = { 173, 143, 17, 23 };
	sswAnim[4] = { 156, 143, 17, 23 };
	sswAnim[5] = { 139, 143, 17, 23 };
	sswAnim[6] = { 122, 143, 17, 23 };
	sswAnim[7] = { 105, 143, 17, 23 };
	//- Shouth west west
	swwAnim[0] = { 154, 122, 22, 17 };
	swwAnim[1] = { 132, 122, 22, 17 };
	swwAnim[2] = { 110, 122, 22, 17 };
	swwAnim[3] = {  88, 122, 22, 17 };
	swwAnim[4] = {  66, 122, 22, 17 };
	swwAnim[5] = {  44, 122, 22, 17 };
	swwAnim[6] = {  22, 122, 22, 17 };
	swwAnim[7] = {   0, 122, 22, 17 };
	//- North west west
	nwwAnim[0] = {  44, 105, 22, 17 };
	nwwAnim[1] = {  22, 105, 22, 17 };
	nwwAnim[2] = {   0, 105, 22, 17 };
	nwwAnim[3] = { 214,  84, 22, 17 };
	nwwAnim[4] = { 192,  84, 22, 17 };
	nwwAnim[5] = { 170,  84, 22, 17 };
	nwwAnim[6] = { 148,  84, 22, 17 };
	nwwAnim[7] = { 126,  84, 22, 17 };
	//- North north west
	nnwAnim[0] = { 183, 61, 17, 23 };
	nnwAnim[1] = { 166, 61, 17, 23 };
	nnwAnim[2] = { 149, 61, 17, 23 };
	nnwAnim[3] = { 132, 61, 17, 23 };
	nnwAnim[4] = { 115, 61, 17, 23 };
	nnwAnim[5] = {  98, 61, 17, 23 };
	nnwAnim[6] = {  81, 61, 17, 23 };
	nnwAnim[7] = {  64, 61, 17, 23 };
}

ModuleUnit::~ModuleUnit()
{

}

bool ModuleUnit::Start()
{
	bool ret = true;
	LOG("Loading unit assets");
	unitTx = App->textures->Load("Assets/OrangeUnitSpritesheet.png");
	currentOrbit = currentSpin = angleW;
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
	moving = false;

	//- Check if the ball is locked
	if(App->player1->locked == false)
	{
		//Conditions for movement-----------------------------------------------------------------------------
		if (App->player1->MoveLeft() == true)
		{
			moving = true;
			//- The unit goes to the right (the unit always goes to the opposite direction that we're moving to)
			targetOrbit = angleE;
		}
		if (App->player1->MoveRight() == true)
		{
			moving = true;
			//- The unit goes to the left (the unit always goes to the opposite direction that we're moving to)
			targetOrbit = angleW;
		}
		if (App->player1->MoveUp() == true)
		{
			moving = true;
			//- The unit moves down (the unit always goes to the opposite direction that we're moving to)
			targetOrbit = angleS;
			//- We check if a part from going down, it's also going to one of the sides (for the diagonals)
			if (App->player1->MoveLeft() == true) { targetOrbit -= PI / 4; }
			if (App->player1->MoveRight() == true) { targetOrbit += PI / 4; }
		}
		if (App->player1->MoveDown() == true)
		{
			moving = true;
			//- The unit goes up (the unit always goes to the opposite direction that we're moving to)
			targetOrbit = angleN;
			//- We check if a part from going up, it's also going to one of the sides (for the diagonals)
			if (App->player1->MoveLeft() == true) { targetOrbit += PI / 4; }
			if (App->player1->MoveRight() == true) { targetOrbit -= PI / 4; }
		}

		//Move the orbit to the target rotation---------------------------------------------------------------
		//- Orbit around the player
		if (moving == true) { RotateTo(targetOrbit, currentOrbit, orbitSpeed); }
		//- Rotation of the unit itself
		if (moving == true) { RotateTo(targetOrbit, currentSpin, spinSpeed); }

		//Limit the rotation----------------------------------------------------------------------------------
		//- On the orbit
		LimitRotation(currentOrbit);
		//- On the spin
		LimitRotation(currentSpin);
	}

	//Set the position-------------------------------------------------------------------------------------
	position.x = radius * cosf(currentOrbit) + App->player1->position.x + 5;
	position.y = radius * sinf(currentOrbit) + App->player1->position.y - 1;
	//Increase the internal rotation-----------------------------------------------------------------------
	currentInternalRotation += internalRotationSpeed;
	if (currentInternalRotation >= frames) { currentInternalRotation = 0; }
	//Set the rotation and render--------------------------------------------------------------------------
	//if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}
	//else if (currentSpin) {}

	App->render->Blit(unitTx, position.x, position.y, &eAnim[(int)currentInternalRotation]);

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
	if (targetRotation == angleS || targetRotation == angleS + PI / 4 || targetRotation == angleS - PI / 4)
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

	//Check if the target rotation is up or one ofthe upper diagonals
	else if (targetRotation == angleN || targetRotation == angleN - PI / 4 || targetRotation == angleN + PI / 4)
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
	else if (targetRotation == angleW)
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
	else if (targetRotation == angleE)
	{
		oppositeRotation = angleW;
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

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{

}


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
	unitAnim.PushBack({ 66, 0, 22 , 16 });
}

ModuleUnit::~ModuleUnit()
{

}

bool ModuleUnit::Start()
{
	bool ret = true;
	LOG("Loading unit assets");
	unitTx = App->textures->Load("Assets/OrangeUnitSpritesheet.png");
	currentRotation = angleLeft;
	return ret;
}

bool ModuleUnit::CleanUp()
{
	LOG("Unloading unit assets");
	App->textures->Unload(unitTx);
	return true;
}

void ModuleUnit::Orbit(float targetRotation)
{
	//If we've reached our target rotation

	if (targetRotation == angleRight) {
		{
			if(currentRotation < PI)
				currentRotation -= rotateSpeed;
			else
				currentRotation += rotateSpeed;
		}
	}
	else if (targetRotation == angleLeft) {
		{
			if (currentRotation <= PI)
				currentRotation += rotateSpeed;
			else
				currentRotation -= rotateSpeed;
		}
	}
	else if (targetRotation == angleDown) {
		{
			if (currentRotation > PI/2 && currentRotation < 3*PI/2)
				currentRotation += rotateSpeed;
			else
				currentRotation -= rotateSpeed;
		}
	}
	else if (targetRotation == angleUp) {
		{
			if (currentRotation >= PI / 2 && currentRotation < 3 * PI / 2)
				currentRotation -= rotateSpeed;
			else
				currentRotation += rotateSpeed;
		}
	}
	

	if (currentRotation  > targetRotation - rotateSpeed &&  currentRotation < targetRotation + rotateSpeed )
	{
		lastTarget = targetRotation;
		currentRotation = targetRotation;
	}
}

update_status ModuleUnit::Update()
{
	//Initial set up--------------------------------------------------------------------------------------
	//- We update our moving bool to false, if any key is pressed, it will go to true
	moving = false;

	//Conditions for movement-----------------------------------------------------------------------------
	if (App->player1->MoveLeft() == true)
	{
		moving = true;
		//- The unit goes to the right (the unit always goes to the opposite direction that we're moving to)
		targetRotation = angleRight;
	}
	if (App->player1->MoveRight() == true)
	{
		moving = true;
		//- The unit goes to the left (the unit always goes to the opposite direction that we're moving to)
		targetRotation = angleLeft;
	}
	if (App->player1->MoveUp() == true)
	{
		moving = true;
		//- The unit moves down (the unit always goes to the opposite direction that we're moving to)
		targetRotation = angleDown;
		//- We check if a part from going down, it's also going to one of the sides (for the diagonals)
		if (App->player1->MoveLeft() == true) { targetRotation -= PI / 4; }
		if (App->player1->MoveRight() == true) { targetRotation += PI / 4; }
	}
	if (App->player1->MoveDown() == true)
	{
		moving = true;
		//- The unit goes up (the unit always goes to the opposite direction that we're moving to)
		targetRotation = angleUp;
		//- We check if a part from going up, it's also going to one of the sides (for the diagonals)
		if (App->player1->MoveLeft() == true) { targetRotation += PI / 4; }
		if (App->player1->MoveRight() == true) { targetRotation -= PI / 4; }
	}

	//Move the orbit to the target rotation---------------------------------------------------------------
	//- Orbit around the player
	if (moving == true) { Orbit(targetRotation); }
	//- Rotation of the unit itself

	//Limit the rotation----------------------------------------------------------------------------------
	//- Limit the rotation to positive numbers (after modifing it)
	if (currentRotation < 0)
	{
		currentRotation = angleRight + currentRotation;//We add the rotation because it's negative, so it will efectively substract it
	}
	//- Limit the rotation to one circle
	while (currentRotation > angleRight)
	{
		currentRotation -= angleRight;
	}

	//Set the position-------------------------------------------------------------------------------------
	position.x = radius * cosf(currentRotation) + App->player1->position.x + 5;
	position.y = radius * sinf(currentRotation) + App->player1->position.y - 1;

	//Render-----------------------------------------------------------------------------------------------
	App->render->Blit(unitTx, position.x, position.y, &unitAnim.GetCurrentFrame());

	return UPDATE_CONTINUE;
}

//This function has a series of if statatements that do the following
//First if  --> Finds the rotation we want to go to
//Second if --> Determines which distance from the currentRotation to the targetRotation is shorter
//Third if  --> Go to that direction, until we get at it
void ModuleUnit::Orbit (float targetRotation)
{
	//We create a variable that's going to store the opposite rotation from the targetRotation
	float oppositeRotation;

	//Check if the target rotation is down or one of the lower diagonals
	if(targetRotation == angleDown || targetRotation == angleDown + PI / 4 || targetRotation == angleDown - PI / 4)
	{
		oppositeRotation = targetRotation + PI;
		//Check which way is shorter
		if (currentRotation <= oppositeRotation && currentRotation > targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + rotateSpeed) { MoveClockwise(); }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation < targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - rotateSpeed) { MoveCounterclock(); }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation > oppositeRotation)
		{
			MoveCounterclock();
		}
	}

	//Check if the target rotation is up or one ofthe upper diagonals
	else if (targetRotation == angleUp || targetRotation == angleUp - PI / 4 || targetRotation == angleUp + PI / 4)
	{
		oppositeRotation = targetRotation - PI;
		//Check which way is shorter
		if (currentRotation > targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + rotateSpeed) { MoveClockwise(); }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation <= oppositeRotation)
		{
			MoveClockwise();
		}
		else if (currentRotation < targetRotation && currentRotation > oppositeRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - rotateSpeed) { MoveCounterclock(); }
			else { currentRotation = targetRotation; }
		}
	}

	//Check if the target rotation is left
	else if (targetRotation == angleLeft)
	{
		//Check which way is shorter
		if (currentRotation == 0 || currentRotation > targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + rotateSpeed) { MoveClockwise(); }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation < targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - rotateSpeed) { MoveCounterclock(); }
			else { currentRotation = targetRotation; }
		}
	}

	//Check if the target rotation is right
	else if (targetRotation == angleRight)
	{
		oppositeRotation = angleLeft;
		//Check which way is shorter
		if (currentRotation <= oppositeRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation > rotateSpeed) { MoveClockwise(); }
			else { currentRotation = targetRotation; }
		}
		else if (currentRotation > angleLeft)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - rotateSpeed) { MoveCounterclock(); }
			else { currentRotation = targetRotation; }
		}
	}
}

void ModuleUnit::MoveClockwise() { currentRotation -= rotateSpeed; }
void ModuleUnit::MoveCounterclock() { currentRotation += rotateSpeed; }

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{

}


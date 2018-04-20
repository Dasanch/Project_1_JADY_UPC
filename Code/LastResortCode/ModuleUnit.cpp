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

//This function has a series of if statatements that do the following
//1- Find the rotation we want to go to
//2- Determine which distance to the target is shorter
//3- Go to that direction, until you get at it
void ModuleUnit::Orbit (float targetRotation)
{
	float oppositeRotation;
	if(targetRotation == angleDown || targetRotation == angleDown + PI / 4 || targetRotation == angleDown - PI / 4)
	{
		oppositeRotation = targetRotation + PI;
		//Clockwise
		if (currentRotation <= oppositeRotation && currentRotation > targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + rotateSpeed) { currentRotation -= rotateSpeed; }
			else { currentRotation = targetRotation; }
		}
		//Counterclock
		else if (currentRotation < targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - rotateSpeed) { currentRotation += rotateSpeed; }
			else { currentRotation = targetRotation; }
		}
		//Counterclock too
		else if (currentRotation > oppositeRotation)
		{
			currentRotation += rotateSpeed;
		}
	}
	else if (targetRotation == angleUp || targetRotation == angleUp - PI / 4 || targetRotation == angleUp + PI / 4)
	{
		oppositeRotation = targetRotation - PI;
		//Clockwise
		if (currentRotation > targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + rotateSpeed) { currentRotation -= rotateSpeed; }
			else { currentRotation = targetRotation; }
		}
		//Clockwise too
		else if (currentRotation <= oppositeRotation)
		{
			currentRotation -= rotateSpeed;
		}
		//Counterclock
		else if (currentRotation < targetRotation && currentRotation > oppositeRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - rotateSpeed) { currentRotation += rotateSpeed; }
			else { currentRotation = targetRotation; }
		}
	}
	else if (targetRotation == angleLeft)
	{
		//Clockwise
		if (currentRotation == 0 || currentRotation > targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation > targetRotation + rotateSpeed) { currentRotation -= rotateSpeed; }
			else { currentRotation = targetRotation; }
		}
		//Counterclock
		else if (currentRotation < targetRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - rotateSpeed) { currentRotation += rotateSpeed; }
			else { currentRotation = targetRotation; }
		}
	}
	else if (targetRotation == angleRight)
	{
		oppositeRotation = angleLeft;
		//Clockwise
		if (currentRotation <= oppositeRotation)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation > rotateSpeed) { currentRotation -= rotateSpeed; }
			else { currentRotation = targetRotation; }
		}
		//Counterclock
		else if (currentRotation > angleLeft)
		{
			//Only add if it hasn't reached its limit
			if (currentRotation < targetRotation - rotateSpeed) { currentRotation += rotateSpeed; }
			else { currentRotation = targetRotation; }
		}
	}
}

update_status ModuleUnit::Update()
{
	moving = false;
	//Conditions
	//- We check basic movement first
	if (App->player1->MoveLeft() == true)
	{
		moving = true;
		//The unit goes to the right
		targetRotation = angleRight;
	}
	if (App->player1->MoveRight() == true)
	{
		moving = true;
		//The unit goes to the left
		targetRotation = angleLeft;
	}
	//- Then we check diagonals
	if (App->player1->MoveUp() == true)
	{
		moving = true;
		//The unit moves down
		targetRotation = angleDown;
		if (App->player1->MoveLeft() == true) { targetRotation -= PI / 4; }
		if (App->player1->MoveRight() == true) { targetRotation += PI / 4; }
	}
	if (App->player1->MoveDown() == true)
	{
		moving = true;
		//The unit goes up
		targetRotation = angleUp;
		if (App->player1->MoveLeft() == true) { targetRotation += PI / 4; }
		if (App->player1->MoveRight() == true) { targetRotation -= PI / 4; }
	}
	//Move
	if(moving == true) { Orbit(targetRotation); }
	//Limit the rotation to positive numbers (after modifing it)
	if (currentRotation < 0)
	{
		currentRotation = angleRight + currentRotation;//We add the rotation because it's negative, so it will efectively substract it
	}
	//We limit the rotation to one circle
	while (currentRotation > angleRight)
	{
		currentRotation -= angleRight;
	}
	//Set the position
	position.x = radius * cosf(currentRotation) + App->player1->position.x + 5;
	position.y = radius * sinf(currentRotation) + App->player1->position.y - 1;
	//Render
	App->render->Blit(unitTx, position.x, position.y, &unitAnim.GetCurrentFrame());
	return UPDATE_CONTINUE;
}
//UCM (Uniform Circular Motion):
//rotation = initial rotation + angular speed * time
//angular speed = speed / radius

//Animations
//if(rotation > 90-5 && rotation < 90+5)
//animation = that
//Possible fer una funcio que faci els intervals directament

bool ModuleUnit::CleanUp()
{
	LOG("Unloading unit assets");

	return true;
}

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{

}


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
	return ret;
}

void ModuleUnit::MoveCounterClock(float targetRotation)
{
	//If we've reached our target rotation
	if (fabs(currentRotation - targetRotation) < rotateSpeed)
	{
		currentRotation = targetRotation;
	}
	else
	{
		currentRotation += rotateSpeed;
	}
}

void ModuleUnit::MoveClockWise(float targetRotation)
{
	//If we've reached our target rotation
	if (fabs(currentRotation - targetRotation) < rotateSpeed)
	{
		currentRotation = targetRotation;
	}
	else
	{
		currentRotation -= rotateSpeed;
	}
}

update_status ModuleUnit::Update()
{
	moving = false;
	//Conditions
	if (App->player1->MoveLeft() == true)
	{
		////The unit goes to the right
		//if (currentRotation > PI)
		//{
		//	MoveCounterClock(angleRight);
		//}
		//else
		//{
			MoveClockWise(angleRight);
		//}
	}
	if (App->player1->MoveRight() == true)
	{
		//LOG("Move right");
		//LOG("Current rotation; %f:", currentRotation);
		////The unit goes to the left
		//if (currentRotation < PI)
		//{
		//	MoveCounterClock(angleLeft);
		//}
		//else
		//{
			MoveClockWise(angleLeft);
		//}
	}
	if (App->player1->MoveUp() == true)
	{
		//LOG("Move up");
		//LOG("Current rotation; %f:", currentRotation);
		//if (currentRotation > 3 * PI / 2 || currentRotation < PI)
		//{
		//	MoveCounterClock(angleUp);
		//}
		//else
		//{
			MoveClockWise(angleUp);
		//}
	}
	if (App->player1->MoveDown() == true)
	{
		//LOG("Move down");
		//LOG("Current rotation; %f:", currentRotation);
		//if (currentRotation < 3 * PI / 2 && currentRotation > PI)
		//{
		//	MoveCounterClock(angleDown);
		//}
		//else
		//{
			MoveClockWise(angleDown);
		//}
	}
	//Limit the rotation to positive numbers (after modifing it)
	if (currentRotation < 0)
	{
		currentRotation = 2 * PI + currentRotation;//We add the rotation because it's negative, so it will efectively substract it
	}
	//We limit the rotation to one circle
	while (currentRotation >= 2 * PI)
	{
		currentRotation -= 2 * PI;
	}
	//Set the position
	position.x = radius * cosf(currentRotation) + App->player1->position.x;
	position.y = radius * sinf(currentRotation) + App->player1->position.y;
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

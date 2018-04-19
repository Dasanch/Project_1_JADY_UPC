#include "Globals.h"
#include "Application.h"
#include "ModuleUnit.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Player1.h"
#include <stdio.h>

ModuleUnit::ModuleUnit() //Constructor 
{
	unitAnim.PushBack({ 66, 0, 22 , 16});
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

void ModuleUnit::LimitAddMovement(float targetRotation)
{
	if (fabs(currentRotation - targetRotation) < rotateSpeed)
	{ currentRotation = targetRotation; }
	else
	{ currentRotation += rotateSpeed; }
}

void ModuleUnit::LimitSubMovement(float targetRotation)
{
	if (fabs(currentRotation - targetRotation) < rotateSpeed)
	{ currentRotation = targetRotation; }
	else
	{ currentRotation -= rotateSpeed; }
}

update_status ModuleUnit::Update()
{
	//Conditions
	if(App->player1->MoveLeft() == true)
	{
		//The unit goes to the right (0 or 0)
		//if(fabs(currentRotation - angleRight) <= PI)
		//{ LimitAddMovement(angleRight); }
		//else
		//{ LimitSubMovement(angleRight); }
		//LimitAddMovement(angleRight);
		targetRotation = angleRight;
	}
	if (App->player1->MoveRight() == true)
	{
		//The unit goes to the left (180 or PI)
		//if (fabs(currentRotation - angleLeft) >= PI)
		//{ LimitAddMovement(angleLeft); }
		//else
		//{ LimitSubMovement(angleLeft); }
		//LimitAddMovement(angleLeft);
		targetRotation = angleLeft;
	}
	if (App->player1->MoveUp() == true)
	{
		//The unit goes down (270 or 3*PI/2)
		//if (fabs(currentRotation - angleUp) >= PI)
		//{ LimitAddMovement(angleUp); }
		//else
		//{ LimitSubMovement(angleUp); }
		//LimitAddMovement(angleUp);
		targetRotation = angleUp;
	}
	if (App->player1->MoveDown() == true)
	{
		//The unit goes up (90 or PI/2)
		//if (fabs(currentRotation - angleDown) <= PI)
		//{ LimitAddMovement(angleDown); }
		//else
		//{ LimitSubMovement(angleDown); }
		//LimitAddMovement(angleDown);
		targetRotation = angleDown;
	}
	//Move
	LimitAddMovement(targetRotation);
	//if(fabs(targetRotation - currentRotation) >= PI)
	//{
	//	//Move clockwise
	//	LimitAddMovement(targetRotation);
	//}
	//else
	//{
	//	//Movecounterclock
	//	LimitSubMovement(targetRotation);
	//}
	//Limit the rotation to positive numbers
	if(currentRotation < 0)
	{
		currentRotation = 2 * PI + currentRotation;//We add the rotation because it's negative, so it will efectively substract it
	}
	//Limit the rotation to 2PI (not more than one full circle)
	while(currentRotation >= 2*PI)
	{
		currentRotation -= 2*PI;
	}
	//Debug rotation
	LOG("Rotation: %f", currentRotation);
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
	App->textures->Unload(unitTx);
	return true;
}

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{

}

float ModuleUnit::ToRadian(float degreeRotation)
{
	return degreeRotation * 180 / (2 * PI);
}
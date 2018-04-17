#include "Globals.h"
#include "Application.h"
#include "ModuleUnit.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Player1.h"

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

void ModuleUnit::LimitAddMovement(int targetRotation)
{
	if (fabs(rotation - targetRotation) < rotateSpeed)
	{ rotation = targetRotation; }
	else
	{ rotation += rotateSpeed; }
}

void ModuleUnit::LimitSubMovement(int targetRotation)
{
	if (fabs(rotation - targetRotation) < rotateSpeed)
	{ rotation = targetRotation; }
	else
	{ rotation -= rotateSpeed; }
}

update_status ModuleUnit::Update()
{
	//Conditions
	if(App->player1->MoveLeft() == true)
	{
		//The unit goes to the right (0 or 0)
		if(position.y + yOffset <= App->player1->position.y)
		{ LimitAddMovement(angleRight); }
		else
		{ LimitSubMovement(angleRight); }
	}
	if (App->player1->MoveRight() == true)
	{
		//The unit goes to the left (180 or PI)
		if (position.y + yOffset >= App->player1->position.y)
		{ LimitAddMovement(angleLeft); }
		else
		{ LimitSubMovement(angleLeft); }
	}
	if (App->player1->MoveUp() == true)
	{
		//The unit goes down (270 or 3*PI/2)
		if (position.x + xOffset >= App->player1->position.x)
		{ LimitAddMovement(angleDown); }
		else
		{ LimitSubMovement(angleDown); }
	}
	if (App->player1->MoveDown() == true)
	{
		//The unit goes up (90 or PI/2)
		if (position.x +xOffset <= App->player1->position.x)
		{ LimitAddMovement(angleUp); }
		else
		{ LimitSubMovement(angleUp); }
	}
	//Limit the rotation
	while(rotation > 2*PI)
	{
		rotation -= 2*PI;
	}
	//Set the position
	position.x = radius * cosf(rotation) + App->player1->position.x + xOffset;
	position.y = radius * sinf(rotation) + App->player1->position.y + yOffset;
	//Render
	App->render->Blit(unitTx, position.x, position.y, &unitAnim.GetCurrentFrame());
	return UPDATE_CONTINUE;
}
//UCM (Uniform Circular Motion):
//rotation = initial rotation + angular speed * time
//angular speed = speed / radius

bool ModuleUnit::CleanUp()
{
	LOG("Unloading unit assets");

	return true;
}

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{

}

float ModuleUnit::ToRadian(float degreeRotation)
{
	return degreeRotation * 180 / (2 * PI);
}
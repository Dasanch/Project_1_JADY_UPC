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

update_status ModuleUnit::Update()
{
	//Conditions
	if(App->player1->MoveLeft() == true)
	{
		//The unit goes to the right (0)
		if(rotation > 0)
		{ rotation -= rotateSpeed; }
		else
		{ rotation += rotateSpeed; }
	}
	if (App->player1->MoveRight() == true)
	{
		//The unit goes to the left (180)
		if (rotation > PI)
		{ rotation -= rotateSpeed; }
		else
		{ rotation += rotateSpeed; }
	}
	if (App->player1->MoveUp() == true)
	{
		//The unit goes down (270)
		if (rotation > 3 * PI / 2)
		{ rotation -= rotateSpeed; }
		else
		{ rotation += rotateSpeed; }
	}
	if (App->player1->MoveDown() == true)
	{
		//The unit goes up (90)
		if (rotation > PI / 2)
		{ rotation -= rotateSpeed; }
		else
		{ rotation += rotateSpeed; }
	}
	//Limit the rotation
	if(rotation > 360)
	{
		rotation - 360;
	}
	//Set the position
	position.x = radius * cosf(rotation) + App->player1->position.x;
	position.y = radius * sinf(rotation) + App->player1->position.y;
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
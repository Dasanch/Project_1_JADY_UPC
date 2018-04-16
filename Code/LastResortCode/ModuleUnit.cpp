#include "Globals.h"
#include "Application.h"
#include "ModuleUnit.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"

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
	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT)
	{
		x -= rotateSpeed;
		//Limit the variable
		if(x < -r) { x = -r; }
		//Find the other component
		//-Look at if it's above or bellow 0 (there are two solutions to a square root, we need to get the one we need)
		if (y >= 0) { y =  sqrt(pow(r, 2) - pow(x, 2)); }
		else        { y = -sqrt(pow(r, 2) - pow(x, 2)); }
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT)
	{
		x += rotateSpeed;
		//Limit the variable
		if (x > r) { x = r; }
		//Find the other component
		//-Look at if it's above or bellow 0 (there are two solutions to a square root, we need to get the one we need)
		if(y >= 0) { y =  sqrt(pow(r, 2) - pow(x, 2)); }
		else       { y = -sqrt(pow(r, 2) - pow(x, 2)); }
	}
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT)
	{
		y -= rotateSpeed;
		//Limit the variable
		if (y < -r)	{ y = -r; }
		//Find the other component
		//-Look at if it's above or bellow 0 (there are two solutions to a square root, we need to get the one we need)
		if(x >= 0) { x =  sqrt(pow(r, 2) - pow(y, 2)); }
		else       { x = -sqrt(pow(r, 2) - pow(y, 2)); }
		
	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT)
	{
		y += rotateSpeed;
		//Limit the variable
		if (y > r) { y = r; }
		//Find the other component
		//-Look at if it's above or bellow 0 (there are two solutions to a square root, we need to get the one we need)
		if (x >= 0) { x = sqrt(pow(r, 2) - pow(y, 2)); }
		else { x = -sqrt(pow(r, 2) - pow(y, 2)); }
	}
	//Set the position
	position.x = x + App->player->position.x + 15; //15= offset from the top left. Adding this we get the center of the player
	position.y = y + App->player->position.y +  5; // 5= offset from the top left. Adding this we get the center of the player
	//Render
	App->render->Blit(unitTx, position.x, position.y, &unitAnim.GetCurrentFrame());
	return UPDATE_CONTINUE;
}
//- CIRCLE FORMULA
//(x - a)^2 + (y - b)^2 = r^2
//x = (-(-2 * a) + sqrt((-2 * a) - 4 * (pow(y, 2) + pow(b, 2) + pow(r, 2)))) / 2;
//x = (-(-2 * a) - sqrt((-2 * a) - 4 * (pow(y, 2) + pow(b, 2) + pow(r, 2)))) / 2;
//y = (-(-2 * b) + sqrt((-2 * b) - 4 * (pow(y, 2) + pow(a, 2) + pow(r, 2)))) / 2;
//y = (-(-2 * b) - sqrt((-2 * b) - 4 * (pow(y, 2) + pow(a, 2) + pow(r, 2)))) / 2;
//Square roots can have two possible solutions

bool ModuleUnit::CleanUp()
{
	LOG("Unloading unit assets");

	return true;
}

void ModuleUnit::OnCollision(Collider* collider1, Collider* collider2)
{

}
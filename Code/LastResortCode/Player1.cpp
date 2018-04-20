#include "Globals.h"
#include "Application.h"
#include "Player1.h"
#include "ModuleInput.h"

//MOVEMENT INPTUT
bool Player1::MoveLeft()
{
	return (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT);
}

bool Player1::MoveRight()
{
	return (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && MoveLeft()== false);
}
//We limit MoveRight because if MoveRight and Moveleft are pressed, it goes left

bool Player1::MoveDown()
{
	return (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT);
}

bool Player1::MoveUp()
{
	return (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && MoveDown() == false);
}
//We limit MoveUp because if MoveUp and MoveDown are pressed, it goes down

//SHOOT INPUT
bool Player1::Shoot()
{
	return (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN);
}
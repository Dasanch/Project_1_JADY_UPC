#include "Globals.h"
#include "Application.h"
#include "Player1.h"
#include "ModuleInput.h"

bool Player1::MoveLeft()
{
	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		return true;
	}
	return false;
}

bool Player1::MoveRight()
{
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		return true;
	}
	return false;
}

bool Player1::MoveDown()
{
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		return true;
	}
	return false;
}

bool Player1::MoveUp()
{
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		return true;
	}
	return false;
}

bool Player1::Shoot()
{
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		return true;
	}
	return false;
}
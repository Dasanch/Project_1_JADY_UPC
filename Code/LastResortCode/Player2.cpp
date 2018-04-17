#include "Globals.h"
#include "Application.h"
#include "Player2.h"
#include "ModuleInput.h"

bool Player2::MoveLeft()
{
	if (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT)
	{
		return true;
	}
	return false;
}

bool Player2::MoveRight()
{
	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT)
	{
		return true;
	}
	return false;
}

bool Player2::MoveDown()
{
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT)
	{
		return true;
	}
	return false;
}

bool Player2::MoveUp()
{
	if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_REPEAT)
	{
		return true;
	}
	return false;
}

bool Player2::Shoot()
{
	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		return true;
	}
	return false;
}
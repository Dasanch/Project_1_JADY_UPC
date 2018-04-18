#include "Globals.h"
#include "Application.h"
#include "Player2.h"
#include "ModuleInput.h"

bool Player2::MoveLeft()
{
	return (App->input->keyboard[SDL_SCANCODE_H] == KEY_STATE::KEY_REPEAT);
}

bool Player2::MoveRight()
{
	return (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT);
}

bool Player2::MoveDown()
{
	return (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT);
}

bool Player2::MoveUp()
{
	return (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_REPEAT);
}

bool Player2::Shoot()
{
	return (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN);
}
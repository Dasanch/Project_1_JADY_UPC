#include "Globals.h"
#include "Application.h"
#include "Player1.h"
#include "ModuleInput.h"

bool Player1::MoveLeft()
{
	return (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT);
}

bool Player1::MoveRight()
{
	return (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT);
}

bool Player1::MoveDown()
{
	return (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT);
}

bool Player1::MoveUp()
{
	return (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT);
}

bool Player1::Shoot()
{
	return (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN);
}
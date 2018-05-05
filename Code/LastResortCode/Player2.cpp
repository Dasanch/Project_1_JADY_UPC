#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Player2.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleFadetoBlack.h"
#include "ModuleUnit.h"

Player2::Player2() {
	//Initial position------------------------------------------
	initPosition = { 40,138 };
	shot_colType = COLLIDER_PLAYER_2_SHOT;
	//Movement animation----------------------------------------
	shipAnim.PushBack({ 198, 3, 32, 12 });	//0 = UpShip
	shipAnim.PushBack({ 230, 3, 32, 12 });	//1 = MiddleUpShip
	shipAnim.PushBack({ 262, 3, 32, 12 });	//2 = idle
	shipAnim.PushBack({ 294, 3, 32, 12 });	//3 = MiddleDownShip
	shipAnim.PushBack({ 326, 3, 32, 12 });	//4 = DownShip
	//Initial animation-----------------------------------------
	initAnim.PushBack({ 212, 223, 111, 1 });
	initAnim.PushBack({ 212, 226, 117, 3 });
	initAnim.PushBack({ 212, 228, 66, 4 });
	initAnim.PushBack({ 212, 233, 58, 8 });
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 2; ++j) {
			initAnim.PushBack({ 212 + 64 * i, 159 + 25 * j ,64,25 });
		}
	}
	initAnim.speed = 0.15f;
	//Death animation-------------------------------------------
	deathAnim.PushBack({ 221 ,27,32,12 });
	deathAnim.PushBack({ 218 ,43,35,15 });
	deathAnim.PushBack({ 213,61,40,18 });
	deathAnim.PushBack({ 208 ,83 ,45,19 });
	deathAnim.PushBack({ 202 ,104,51,20 });
	//--------------------------------------
	deathAnim.PushBack({ 253 ,19,63,21 });
	deathAnim.PushBack({ 253 ,40,63,22 });
	deathAnim.PushBack({ 253 ,62,63,24 });
	deathAnim.PushBack({ 253 ,86,63,23 });
	deathAnim.PushBack({ 253 ,109,63,23 });
	//-------------------------------------
	deathAnim.PushBack({ 253 ,132,63,24 });
	deathAnim.PushBack({ 316 ,19,60,25 });
	deathAnim.PushBack({ 316 ,44,60,26 });
	deathAnim.PushBack({ 316 ,71,60,25 });
	deathAnim.PushBack({ 316 ,97,60,28 });
	//------------------------------------
	deathAnim.PushBack({ 316 ,125,60,28 });
	deathAnim.PushBack({ 376 ,19,55,17 });
	deathAnim.PushBack({ 376 ,47,55,28 });
	deathAnim.PushBack({ 376 ,75,55,20 });
	deathAnim.speed = 0.35f;
	//Shot Fire Animation----------------------------------------
	shotFire.PushBack({ 125, 247, 10,9 });
	shotFire.PushBack({ 137, 247, 10,9 });
	shotFire.PushBack({ 125, 258, 13,12 });
	shotFire.speed = 0.2f;
	shotFire.loop = true;

	//Shot fire laser---------------------------------------------
	ShotLaserBasic.PushBack({ 32,305,30,3 });
	ShotLaserBasic.PushBack({ 32,321,32,3 });
	ShotLaserBasic.PushBack({ 32,326,32,3 });
	ShotLaserBasic.PushBack({ 32,314,31,5 });
	ShotLaserBasic.PushBack({ 64,305,30,7 });
	ShotLaserBasic.PushBack({ 64,288,27,9 });
	ShotLaserBasic.PushBack({ 32,288,13,13 });
	ShotLaserBasic.PushBack({ 47,288,15,15 });
	ShotLaserBasic.speed = 0.2f;
	ShotLaserBasic.loop = true;
}

void Player2::PlayerDies() {

	if (App->ui->lives_p2 > 0) {
		App->ui->lives_p2 -= 1;
		Reappear();
		LOG("lives p2 %d", App->ui->lives_p2);
	}
	else {
		App->ui->p2_isDead = true;
		playerCol->to_delete = true;
	}
}

void Player2::Reset_Positions() {
	initPosition = { 40,138 };
	position = initPosition;
}

bool Player2::MoveLeft()
{
	return (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT);
}

bool Player2::MoveRight()
{
	return (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && MoveLeft()== false);
}
//We limit MoveRight because if MoveRight and Moveleft are pressed, it goes left

bool Player2::MoveDown()
{
	return (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT);
}

bool Player2::MoveUp()
{
	return (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && MoveDown() == false);
}
//We limit MoveUp because if MoveUp and MoveDown are pressed, it goes down

bool Player2::Shoot()
{
	return (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN);
}

bool Player2::Lock()
{
	return (App->input->keyboard[SDL_SCANCODE_KP_1] == KEY_STATE::KEY_DOWN);
}

void Player2::Winposition()
{
	if (position.x < App->render->relative_camera.x + 200)
	{
		position.x += SCREEN_SIZE;
	}
	if (position.x > App->render->relative_camera.x + 200)
	{
		position.x -= SCREEN_SIZE;
	}
	if (position.y < App->render->relative_camera.y + 120)
	{
		position.y += SCREEN_SIZE;
	}
	if (position.y > App->render->relative_camera.y + 120)
	{
		position.y -= SCREEN_SIZE;
	}
}


void Player2::KillUnit()
{
	App->unit2->Disable();
	//App->unit2.currentOrbit = App->unit2.currentSpin = angle angleValue[E];
}
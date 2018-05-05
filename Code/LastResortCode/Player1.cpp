#include "Globals.h"
#include "Application.h"
#include "Player1.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleFadetoBlack.h"
#include "ModuleUnit.h"


Player1::Player1() {
	//Initial values------------------------------------------
	initPosition = { 40,74 };
	shot_colType = COLLIDER_PLAYER_1_SHOT;

	//Movement animation----------------------------------------
	shipAnim.PushBack({ 0, 3, 32, 12 });	//0 = UpShip
	shipAnim.PushBack({ 32, 3, 32, 12 });	//1 = MiddleUpShip
	shipAnim.PushBack({ 64, 3, 32, 12 });	//2 = idle
	shipAnim.PushBack({ 96, 3, 32, 12 });	//3 = MiddleDownShip
	shipAnim.PushBack({ 128, 3, 32, 12 });	//4 = DownShip
	//Initial animation-----------------------------------------
	initAnim.PushBack({ 0, 122, 111, 2 });
	initAnim.PushBack({ 0, 124, 117, 3 });
	initAnim.PushBack({ 0, 127, 88, 4 });
	initAnim.PushBack({ 0, 131, 86, 8 });
	//---------------------------------------------------------
	initAnim.PushBack({ 0, 139, 64, 25 });
	initAnim.PushBack({ 0, 164, 64, 25 });
	initAnim.PushBack({ 0, 189, 64, 25 });
	initAnim.PushBack({ 0, 214, 64, 25 });
	initAnim.PushBack({ 64, 139, 64, 25 });
	initAnim.PushBack({ 64, 164, 64, 25 });
	initAnim.PushBack({ 64, 189, 64, 25 });
	initAnim.PushBack({ 64, 214, 64, 25 });
	initAnim.PushBack({ 128, 139, 64, 25 });
	initAnim.PushBack({ 128, 164, 64, 25 });
	initAnim.speed = 0.2f;
	//Death animation-------------------------------------------
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 6; ++j) {
			deathAnim.PushBack({ 55 * i,19 + 17 * j ,55,17 });
		}
	}
	deathAnim.speed = 0.3f;
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

void Player1::PlayerDies() {
	if (App->ui->lives_p1 > 0) {
		App->ui->lives_p1 -= 1;
		Reappear();
		LOG("lives p2 %d", App->ui->lives_p1);
	}
	else {
		App->ui->p1_isDead = true;
		playerCol->to_delete = true;
	}
}

void Player1::Reset_Positions() {
	initPosition = { 40,74 };
	position = initPosition;
}
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

bool Player1::Lock()
{
	return (App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_DOWN);
}


void Player1::Winposition()
{
	if (position.x < App->render->relative_camera.x + 70)
	{
		position.x += SCREEN_SIZE;
	}
	if (position.x > App->render->relative_camera.x + 70)
	{
		position.x -= SCREEN_SIZE;
	}
	if (position.y < App->render->relative_camera.y+120)
	{
		position.y += SCREEN_SIZE;
	}
	if (position.y > App->render->relative_camera.y + 120)
	{
		position.y -= SCREEN_SIZE;
	}

}

void Player1::KillUnit()
{
	App->unit1->Disable();
	//App->unit1.currentOrbit = App->unit1.currentSpin = angle angleValue[E];
}
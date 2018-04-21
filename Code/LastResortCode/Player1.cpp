#include "Globals.h"
#include "Application.h"
#include "Player1.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadetoBlack.h"


Player1::Player1() {
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


void Player1::ShipAnimation() {

	switch (shipAnimations) {
	case Initial:
		current_animation = &initAnim.GetFrameEx();
		if (initAnim.finished == true) {
			shipAnimations = ShipAnimations::Movment;
			initAnim.Reset();
			canMove = true;
			canShoot = true;
			break;
		}
		//Draw ship---------------------------------------------------
		if (initAnim.current_frame > 4) {
			App->render->Blit(PlayerTexture, initAnim_p.x - (current_animation->w / 2), initAnim_p.y - (current_animation->h / 2), current_animation);
		}
		else {
			App->render->Blit(PlayerTexture, position.x - 40, initAnim_p.y - (current_animation->h / 2), current_animation);
		}
		//------------------------------------------------------------
		break;
	case Movment: 
		//Idle--------------------------------------------------------
		if (yAxis > -transitionLimit && yAxis < transitionLimit) {
			currentFrame = Idle;
		}
		//Transitions-------------------------------------------------
		if (yAxis >= transitionLimit && yAxis < MaxLimit) {
			currentFrame = TransitionDown;
		}
		if (yAxis <= -transitionLimit && yAxis > -MaxLimit) {
			currentFrame = TransitionUp;
		}
		//Maximums---------------------------------------------------
		if (yAxis >= MaxLimit) {
			currentFrame = MaxDown;
		}
		if (yAxis <= -MaxLimit) {
			currentFrame = MaxUp;
		}
		//Draw ship--------------------------------------------------
		current_animation = &shipAnim.frames[currentFrame]; //It set the animation frame 
		App->render->Blit(PlayerTexture, position.x, position.y, current_animation);
		//-----------------------------------------------------------
		break;
	case Death:

		if (deathAnim.finished == true) {
			colType = COLLIDER_PLAYER;
			playerCol->type = COLLIDER_PLAYER;

			if (lives > 0) {
				--lives;
				App->fade->FadeToBlack((Module*)App->stage01, (Module*)App->readyScene, 0.0f); //change to restart player
			}
			else {
				App->fade->FadeToBlack((Module*)App->stage01, (Module*)App->titleScene, 0.0f);
			}
		}

		else if (isDying) {
			colType = COLLIDER_NONE;
			playerCol->type = COLLIDER_NONE;
			current_animation = &deathAnim.GetFrameEx();
			App->render->Blit(PlayerTexture, position.x - 23, position.y - 4, current_animation);
		}
		break;
	}
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
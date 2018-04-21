#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Player2.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadetoBlack.h"

Player2::Player2() {
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
	
}


bool Player2::MoveLeft()
{
	return (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT);
}

bool Player2::MoveRight()
{
	return (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT);
}

bool Player2::MoveDown()
{
	return (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT);
}

bool Player2::MoveUp()
{
	return (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT);
}

bool Player2::Shoot()
{
	return (App->input->keyboard[SDL_SCANCODE_KP_0] == KEY_STATE::KEY_DOWN);
}

bool Player2::Lock()
{
	return (App->input->keyboard[SDL_SCANCODE_KP_1] == KEY_STATE::KEY_DOWN);
}

void Player2::ShipAnimation() {

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

			if (Lives > 0) {
				--Lives;
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
			App->render->Blit(PlayerTexture, position.x + 32 - current_animation->w , position.y + 6 - current_animation->h/2, current_animation);
		}
		break;
	}
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
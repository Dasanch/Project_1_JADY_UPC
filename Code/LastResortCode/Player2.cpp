#include "Globals.h"
#include "Application.h"
#include "Player2.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadetoBlack.h"

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

bool Player2::Lock()
{
	return (App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_STATE::KEY_DOWN);
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
		current_animation = &shipPlayer1.frames[currentFrame]; //It set the animation frame 
		App->render->Blit(PlayerTexture, position.x, position.y, current_animation);
		//-----------------------------------------------------------
		break;
	case Death:

		if (deathAnim.finished == true && Lives > 0) {
			--Lives;
			App->fade->FadeToBlack((Module*)App->stage01, (Module*)App->readyScene, 0.0f);

		}
		if (deathAnim.finished == true && Lives <= 0) {
			App->fade->FadeToBlack((Module*)App->stage01, (Module*)App->titleScene, 0.0f);

		}
		else if (isDying) {
			current_animation = &deathAnim.GetFrameEx();
			App->render->Blit(PlayerTexture, position.x - 23, position.y - 4, current_animation);
		}
		break;
	}
}
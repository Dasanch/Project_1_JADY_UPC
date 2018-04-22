#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleAudio.h"
#include "ModulePowerups.h"
#include "ModuleUI.h"


Enemy::Enemy(int x, int y, powerupType pu_t) : position(x, y), powerUp_drop(pu_t)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{

	if (collider != nullptr)
		collider->SetPos(position.x, position.y + App->render->relative_camera.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y + App->render->relative_camera.y , &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{

	//Explosion type REMEMBER: Improve it for 1.0-----------------------
	App->particles->AddParticle(App->particles->g_explosion02, position.x, position.y + App->render->relative_camera.y, App->particles->g_explosion02.texture, COLLIDER_NONE, 0);
	//Points------------------------------------------------------------
	if (collider->type == COLLIDER_PLAYER_1_SHOT) {
		App->ui->score_p1 += points;
	}
	else if (collider->type == COLLIDER_PLAYER_2_SHOT) {
		App->ui->score_p2 += points;
	}
	//Dropp-------------------------------------------------------------
	if (powerUp_drop != NOPOWERUP) {
          App->powerups->AddPowerup(position.x, position.y, powerUp_drop);
	}

	//Sfx REMEMBER: Improve it for 1.0----------------------------------
	if (SDL_GetTicks() % 2)
		App->audio->ControlSFX(App->particles->g_explosion01_1sfx, PLAY_AUDIO);
	else
		App->audio->ControlSFX(App->particles->g_explosion02_1sfx, PLAY_AUDIO);
}
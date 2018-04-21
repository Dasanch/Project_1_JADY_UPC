#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleAudio.h"


Enemy::Enemy(int x, int y) : position(x, y)
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
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->g_explosion02, position.x, position.y, App->particles->g_explosion02.texture, COLLIDER_NONE, 0); 
	if (SDL_GetTicks() % 2)
		App->audio->ControlSFX(App->particles->g_explosion01_1sfx, PLAY_AUDIO);
	else
		App->audio->ControlSFX(App->particles->g_explosion02_1sfx, PLAY_AUDIO);
}
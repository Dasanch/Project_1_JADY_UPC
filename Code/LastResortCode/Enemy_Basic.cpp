#include "Application.h"
#include "Enemy_Basic.h"
#include "ModuleCollision.h"

Enemy_Basic::Enemy_Basic(int x, int y) : Enemy(x, y)
{
	/*fly.PushBack({ 5,6,24,24 });
	fly.PushBack({ 38, 6, 24, 24 });
	fly.PushBack({ 71, 6, 24, 24 });
	fly.PushBack({ 104, 6, 24, 24 });
	fly.PushBack({ 137, 6, 24, 24 });
	fly.PushBack({ 170, 6, 24, 24 });
	fly.PushBack({ 203, 6, 24, 24 });
	fly.PushBack({ 236, 6, 24, 24 });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;*/
}

void Enemy_Basic::Move()
{

}

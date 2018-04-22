#include "Application.h"
#include "Enemy_Basic.h"
#include "ModuleCollision.h"

Enemy_Basic::Enemy_Basic(int x, int y, powerupType pu_t) : Enemy(x, y, pu_t)
{
	for (int i=0;i<=96;i+=32)
	{
		basicenemy.PushBack({ i,200,32,16 });
	}
	basicenemy.speed = 0.12f;

	animation = &basicenemy;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	
}

void Enemy_Basic::Move()
{

	position.x -= 1;
	
}


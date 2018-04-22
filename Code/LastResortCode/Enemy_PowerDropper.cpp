#include "Application.h"
#include "Enemy_PowerDropper.h"
#include "ModuleCollision.h"

Enemy_PowerDropper::Enemy_PowerDropper(int x, int y, powerupType pu_t) : Enemy(x, y,  pu_t)
{
		dropper.PushBack({ 0,218,32,26 });
		dropper.PushBack({ 32,218,30,26 });
		dropper.PushBack({ 32,218,30,26 });
		dropper.PushBack({ 62,218,32,26 });
		dropper.PushBack({ 94,218,32,26 });
		dropper.speed = 0.2f;
	animation = &dropper;

	collider = App->collision->AddCollider({ 0, 0, 32, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;
}

void Enemy_PowerDropper::Move()
{
	
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.07f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.07f;
	}

	position.y = int(float(original_y) + (20.0f * sinf(wave)));
	position.x -= 1;
	

}
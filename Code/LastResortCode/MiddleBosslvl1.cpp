#include "Application.h"
#include "MiddleBosslvl1.h"
#include "ModuleCollision.h"

Enemy_MetalCraw_Torso::Enemy_MetalCraw_Torso(int x, int y) : Enemy(x, y)
{
	dropper.PushBack({ 138,372,42,59 });
	dropper.PushBack({ 180,373,42,57 });
	dropper.speed = 0.0f;
	animation = &dropper;

	collider = App->collision->AddCollider({ 0, 6, 42, 42 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;
}

void Enemy_MetalCraw_Torso::Move()
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
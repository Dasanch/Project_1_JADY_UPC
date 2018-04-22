#include "Application.h"
#include "Enemy_Oscilator.h"
#include "ModuleCollision.h"

Enemy_Oscilator::Enemy_Oscilator(int x, int y, powerupType pu_t) : Enemy(x, y, pu_t)
{
	Oscilator.PushBack({ 0,0,50,48 });
	Oscilator.speed = 0.2F;
	animation = &Oscilator;
	collider = App->collision->AddCollider({ 0, 0, 50, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_y = y;

}

void Enemy_Oscilator::Move()
{
	
	if (going_up)
	{
	if (wave > 200.0f)
	going_up = false;
	else
	wave += 0.05f;
	}
	else
	{
	if (wave < -200.0f)
	going_up = true;
	else
	wave -= 0.05f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;
	
}
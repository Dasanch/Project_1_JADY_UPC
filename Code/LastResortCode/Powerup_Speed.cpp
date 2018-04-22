#include "Application.h"
#include "Powerup_Speed.h"
#include "ModuleCollision.h"

Powerup_Speed::Powerup_Speed(int x, int y) : Powerup(x, y)
{
	//Push backs
	speedAnim.PushBack({0, 64, 18, 21});
	//We set the animation of the base class to be this animation
	animation = &speedAnim;

	collider = App->collision->AddCollider({ 0, 0, 18, 21 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}
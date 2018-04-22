#include "Application.h"
#include "Powerup_Laser.h"
#include "ModuleCollision.h"

Powerup_Laser::Powerup_Laser(int x, int y) : Powerup(x, y)
{
	//Push backs
	laserAnim.PushBack({ 18, 80, 31, 16 });
	laserAnim.PushBack({ 49, 80, 31, 16 });
	laserAnim.speed = 0.2f;
	laserAnim.loop = true;
	//We set the animation of the base class to be this animation
	animation = &laserAnim;

	collider = App->collision->AddCollider({ 0, 0, 31, 16 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}
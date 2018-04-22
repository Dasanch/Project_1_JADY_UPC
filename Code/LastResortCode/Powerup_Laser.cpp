#include "Application.h"
#include "Powerup_Laser.h"
#include "ModuleCollision.h"
#include "Player1.h"
#include "Player2.h"
#include "Globals.h"

Powerup_Laser::Powerup_Laser(int x, int y) : Powerup(x, y)
{
	//Push backs
	laserAnim.PushBack({ 18, 80, 31, 16 });
	laserAnim.PushBack({ 49, 80, 31, 16 });
	laserAnim.speed = 0.05f;
	laserAnim.loop = true;
	//We set the animation of the base class to be this animation
	animation = &laserAnim;

	collider = App->collision->AddCollider({ 0, 0, 31, 16 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}

void Powerup_Laser::OnCollision(Collider* col)
{
	LOG("You touched a powerup!!!");
	//We find which player got this powerup
	if(col == App->player1->playerCol)
	{
		LOG("You obtained its power!!!");
		//We give it this powerup
		if ( App->player1->powerup_upgrades < 3) { App->player1->powerup_upgrades++; }
		App->player2->powerup_type = powerupType::LASER;
	}
	else if(col == App->player2->playerCol)
	{
		//We give it this powerup
		if ( App->player2->powerup_upgrades < 3) { App->player1->powerup_upgrades++; }
		App->player2->powerup_type = powerupType::LASER;
	}
}
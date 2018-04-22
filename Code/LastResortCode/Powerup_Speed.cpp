#include "Application.h"
#include "Powerup_Speed.h"
#include "ModuleCollision.h"
#include "Player1.h"
#include "Player2.h"
#include "Globals.h"

Powerup_Speed::Powerup_Speed(int x, int y) : Powerup(x, y)
{
	//Push backs
	speedAnim.PushBack({0, 64, 18, 21});
	//We set the animation of the base class to be this animation
	animation = &speedAnim;

	collider = App->collision->AddCollider({ 0, 0, 18, 21 }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->powerups);
}

void Powerup_Speed::OnCollision(Collider* col)
{
	LOG("You touched a powerup!!!");
	//We find which player got this powerup
	if (col == App->player1->playerCol)
	{
		LOG("You obtained its power!!!");
		//We give it this powerup
		App->player1->movementSpeed += 0.5f;//Test value. We should check what is the speed increase in the game.
	}
	else if (col == App->player2->playerCol)
	{
		//We give it this powerup
		App->player1->movementSpeed += 0.5f;//Test value. We should check what is the speed increase in the game.
	}
}
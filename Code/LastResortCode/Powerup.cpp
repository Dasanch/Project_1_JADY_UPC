#include "Application.h"
#include "Powerup.h"
#include "ModuleCollision.h"

Powerup::Powerup(int x, int y) : position(x, y)
{

}

Powerup::~Powerup()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Powerup::GetCollider() const
{
	return collider;
}

void Powerup::OnCollision(Collider* collider)
{

}
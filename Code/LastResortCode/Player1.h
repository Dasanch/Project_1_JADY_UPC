#ifndef __Player1_H__
#define __Player1_H__

#include "ModulePlayer.h"

class Player1 : public ModulePlayer
{
public:
	Player1();
	//void LoadSprites();
	bool MoveUp();
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();
	bool Shoot();
	bool Lock();
	void Winposition() override;
	void Reset_Positions();
	void PlayerDies();
	void KillUnit();
};
#endif
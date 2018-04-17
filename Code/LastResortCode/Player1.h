#ifndef __Player1_H__
#define __Player1_H__

#include "ModulePlayer.h"

class Player1 : public ModulePlayer
{
public:
	Player1(){}
	//void LoadSprites() override;
	bool MoveUp();
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();
};
#endif
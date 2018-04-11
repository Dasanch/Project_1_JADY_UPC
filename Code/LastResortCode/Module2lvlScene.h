
#ifndef __MODULE2LVLSCENE_H__
#define __MODULE2LVLSCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL\include\SDL.h"




class Module2lvlScene : public Module
{
public:
	Module2lvlScene();
	~Module2lvlScene() {

	};

	bool Start();
	update_status Update();
	bool CleanUp();
public:
	SDL_Texture * lvl2Text;
	SDL_Texture * lvl2ground;

};

#endif
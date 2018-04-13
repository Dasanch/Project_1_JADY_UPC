
#ifndef __MODULE2LVLSCENE_H__
#define __MODULE2LVLSCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL\include\SDL.h"
typedef struct _Mix_Music Mix_Music;
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
	SDL_Texture* BckSpam;

	SDL_Rect  BckSpamRect;
	SDL_Rect  BckSpamRect2;
	Mix_Music* lvl2Music = nullptr;

};

#endif
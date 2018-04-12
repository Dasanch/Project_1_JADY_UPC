<<<<<<< HEAD
#ifndef __ModuleContinue_H__
#define __ModuleContinue_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
=======
#ifndef _ModuleContinue_H_
#define _ModuleGameOver_H_
#include "Module.h"
#include "Globals.h"
struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;
>>>>>>> e76574445e14842f0932ccecef5ce952dd97c6d2

class ModuleContinue : public Module
{
public:
	ModuleContinue();
	~ModuleContinue();

	bool Start();
	update_status Update();
	bool CleanUp();
<<<<<<< HEAD

public:
	
	//Textures
	SDL_Texture* backgroundCont = nullptr;


	//Rectangles
	SDL_Rect BGroundCont;
	SDL_Rect BBlack;
	
};

#endif
=======
};
#endif // !_ModuleContinue_H_
>>>>>>> e76574445e14842f0932ccecef5ce952dd97c6d2

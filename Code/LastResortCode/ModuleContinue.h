#ifndef _ModuleContinue_H_
#define _ModuleGameOver_H_
#include "Module.h"
#include "Globals.h"
struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;

class ModuleContinue : public Module
{
public:
	ModuleContinue();
	~ModuleContinue();

	bool Start();
	update_status Update();
	bool CleanUp();
};
#endif // !_ModuleContinue_H_

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
private:
	int current_time = 0;
	int start_time = 0;

	Animation numbersAnim;
	Animation fireAnim;

	SDL_Texture* backgroundTex = nullptr;
	SDL_Texture* continueTex = nullptr;
	
};
#endif // !_ModuleContinue_H_

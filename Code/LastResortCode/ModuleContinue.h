#ifndef _ModuleContinue_H_
#define _ModuleContinue_H_
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
	bool time_finished = false;
	bool rest_bgAlpha = true;
	int number = NULL;
	float bgAlpha = NULL;
	SDL_Rect background_rect;
	SDL_Rect continue_rect;
	Animation numbersAnim;
	Animation fireAnim[8];
	SDL_Texture* backgroundTex = nullptr;
	SDL_Texture* continueTex = nullptr;
public:
	Mix_Music* continue_and_go; 
	//needs to be public because in case that music is not stopped here, we stop it in game over
};
#endif // !_ModuleContinue_H_

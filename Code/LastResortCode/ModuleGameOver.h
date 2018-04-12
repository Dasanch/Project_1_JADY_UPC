#ifndef _ModuleGameOver_H_
#define _ModuleGameOver_H_
#include "Module.h"
#include "Globals.h"
#include "Animation.h"
struct SDL_Texture;
typedef struct _Mix_Music Mix_Music;

class ModuleGameOver : public Module
{
public:
	ModuleGameOver();
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();
private:
	int current_time = 0;
	int start_time = 0;
	float whiteAlpha;
	float blackAlpha;
	float black_go_Alpha;
	SDL_Texture* goTex = nullptr;
	SDL_Rect white_rect;
	SDL_Rect black_rect;
	SDL_Rect metal_go_rect;
	SDL_Rect black_metal_go_rect;
	SDL_Rect white_go_rect;
	SDL_Rect go_rect;

};
#endif // !_ModuleGameOver_H_


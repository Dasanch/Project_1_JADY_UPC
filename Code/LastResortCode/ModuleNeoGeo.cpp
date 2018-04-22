#include "Globals.h"
#include "Application.h"
#include "ModuleNeoGeo.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Player1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStage01.h"
#include "ModuleAudio.h"
#include "ModuleGameTitle.h"
#include "ModuleGameOver.h"
#include "ModuleStageClear.h"
#include "SDL/include/SDL.h"


ModuleNeoGeo::ModuleNeoGeo()
{

}

ModuleNeoGeo::~ModuleNeoGeo()
{

}

bool ModuleNeoGeo::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	neogeoTx = App->textures->Load("Assets/NeoGeo/NeoGeoLogo.png");
	proGearSpecTx = App->textures->Load("Assets/NeoGeo/Max330ProGearSpec.png");
	snkTx = App->textures->Load("Assets/NeoGeo/SNK.png");

	for(int i = 0; i < neogeoWidth * 2; i += neogeoWidth)
	{
		for(int j = 0; j < neogeoHeight * 25; j += neogeoHeight)
		{
			if (i == neogeoWidth * 1 && j == neogeoHeight * 22) { break; }
			neogeoAnim.PushBack({i,j,neogeoWidth,neogeoHeight });
		}
	}
	neogeoAnim.loop = false;
	neogeoAnim.speed = neogeoAnimSpeed;

	//ProGearSpec
	proGearSpecRect.x =   0;
	proGearSpecRect.y =   0;
	proGearSpecRect.w = proGearSpecWidth;
	proGearSpecRect.h =  30;
	blackCoverRect.x = 0;
	blackCoverRect.y = 32;
	blackCoverRect.w = proGearSpecWidth;
	blackCoverRect.h = 14;

	//SNK LOGO
	for(int i = 0; i < snkHeight*6; i += snkHeight)
	{
		for(int j = 0; j < snkWidth*3; j += snkWidth)
		{
			snkAnim.PushBack({ j, i, snkWidth, snkHeight});
			//If we reach the last snk logo, we exit the loop
			if(i == snkHeight*5 && j == 0)
			{
				break;
			}
		}
	}
	snkAnim.loop = false;
	snkAnim.speed = 0.5f;


	neogeoMusic = App->audio->LoadMUS("Assets/NeoGeo/NeoGeoSong.ogg");
	App->audio->ControlMUS(neogeoMusic, PLAY_AUDIO);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}
update_status ModuleNeoGeo::Update()
{	

	// Win/Lose button
	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN) //win
	{
		App->fade->FadeToBlack(this, App->stageclearScene, 0.5f);
	}

	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_DOWN) //lose
	{
		App->fade->FadeToBlack(this, App->gameoverScene, 0.5f);
	}


	//We change the scene if the player presses space
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->titleScene, 0.5f);
	}

	//We check the conditions to change animation
	//- If we've reached the last frame (46) of the title animation
	if(currentAnimation == NeoGeo && neogeoAnim.current_frame >= 46)
	{
		currentFrame = 0;
		currentAnimation = Max330ProGearSpecLine1;
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, 255);
	}
	//- If the first rect doesn't hide Max330ProGear spec anymore
	else if(currentAnimation == Max330ProGearSpecLine1 && cover01PosX >= proGearSpecPosX + proGearSpecWidth)
	{
		currentFrame = 0;
		currentAnimation = Max330ProGearSpecLine2;
	}
	//- If the second rect doesn't hide Max330ProGear spec anymore
	else if(currentAnimation == Max330ProGearSpecLine2 && cover02PosX >= proGearSpecPosX + proGearSpecWidth)
	{
		currentAnimation = SNK;
	}
	//- If the SNL logo has finished its animation (15 = last frame)
	else if (currentAnimation == SNK && snkAnim.current_frame >= 15)
	{
		startTime = SDL_GetTicks();
		currentAnimation = Finish;
	}

	//We animate what needs to be animated
	switch(currentAnimation)
	{
	case NeoGeo:
		//Fade background to white
		if (neogeoAnim.current_frame >= 15 && currentFade != 0)
		{
			currentFade -= 255 / (46 - 15)*neogeoAnimSpeed;//RGB max / number of frames * speed of each frame
			if (currentFade < 0)
			{
				currentFade = 0;
			}
		}
		SDL_SetRenderDrawColor(App->render->renderer, currentFade, currentFade, currentFade, 255);
		SDL_RenderFillRect(App->render->renderer, NULL);
		//Animate the logo
		App->render->Blit(neogeoTx, 40, 52, &neogeoAnim.GetCurrentFrame(), 0.0f);
		//40, 52 positions calculated from the original game
		//Keep in mind that neogeoAnim.current_frame is called before GetCurrent frame, so we'll get the frame before
		break;
	case Max330ProGearSpecLine1:
		//Move the fist rectangle
		//- Limit how much it moves
		if (currentFrame >= frameLimit)
		{
			cover01PosX += coverSpeed;
			currentFrame = 0;
		}
		else
		{
			currentFrame++;
		}
		//Render
		App->render->Blit(neogeoTx, 40, 52, &neogeoAnim.GetCurrentFrame(), 0.0f);//40, 52 positions calculated from the original game
		App->render->Blit(proGearSpecTx, proGearSpecPosX, 113, &proGearSpecRect, 0.0f);//89, 133 positions calculated from the original game
		App->render->Blit(proGearSpecTx, cover01PosX, 113, &blackCoverRect, 0.0f);
		App->render->Blit(proGearSpecTx, cover02PosX, 130, &blackCoverRect, 0.0f);
		break;
	case Max330ProGearSpecLine2:
		//Move the second rectangle
		//- Limit how much it moves
		if (currentFrame >= frameLimit)
		{
			cover02PosX += coverSpeed;
			currentFrame = 0;
		}
		else
		{
			currentFrame++;
		}
		//Render
		App->render->Blit(neogeoTx, 40, 52, &neogeoAnim.GetCurrentFrame(), 0.0f);//40, 52 positions calculated from the original game
		App->render->Blit(proGearSpecTx, proGearSpecPosX, 113, &proGearSpecRect, 0.0f);//89, 133 positions calculated from the original game
		App->render->Blit(proGearSpecTx, cover02PosX, 130, &blackCoverRect, 0.0f);
		break;
	case SNK:
		//Animate the SNK Logo
		//Render
		App->render->Blit(neogeoTx, 40, 52, &neogeoAnim.GetCurrentFrame(), 0.0f);//40, 52 positions calculated from the original game
		App->render->Blit(proGearSpecTx, proGearSpecPosX, 113, &proGearSpecRect, 0.0f);//89, 133 positions calculated from the original game
		App->render->Blit(snkTx, 116, 162, &snkAnim.GetCurrentFrame(), 0.0f);
		break;
	case Finish:
		//Fade to black
		currentTime = SDL_GetTicks();
		if(currentTime > startTime + 1750)//1750 = time to go to the Title screen after all the animations have finished
		{
			App->fade->FadeToBlack(this, App->titleScene, 0.5f);
		}
		App->render->Blit(neogeoTx, 40, 52, &neogeoAnim.GetCurrentFrame(), 0.0f);//40, 52 positions calculated from the original game
		App->render->Blit(proGearSpecTx, proGearSpecPosX, 113, &proGearSpecRect, 0.0f);//89, 133 positions calculated from the original game
		App->render->Blit(snkTx, 116, 162, &snkAnim.GetCurrentFrame(), 0.0f);
		break;
	}
	return UPDATE_CONTINUE;
}
bool ModuleNeoGeo::CleanUp() {
	LOG("Unloading NeoGeo scene");

	App->textures->Unload(neogeoTx);
	App->textures->Unload(snkTx);
	App->textures->Unload(proGearSpecTx);
	App->audio->ControlMUS(neogeoMusic, STOP_AUDIO);
	App->audio->UnloadMUS(neogeoMusic);

	return true;
}
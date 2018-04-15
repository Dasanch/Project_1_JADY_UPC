#include "Globals.h"
#include "Application.h"
#include "ModuleNeoGeo.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBackground.h"
#include "ModuleAudio.h"
#include "ModuleGameTitle.h"


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

	neogeoAnim.PushBack({ 0,1415,227,40 });
	neogeoAnim.PushBack({ 0,1371,227,40 });
	neogeoAnim.PushBack({ 0,1328,227,40 });
	neogeoAnim.PushBack({ 0,1285,227,40 });
	neogeoAnim.PushBack({ 0,1243,227,40 });
	neogeoAnim.PushBack({ 0,1200,227,40 });
	neogeoAnim.PushBack({ 0,1158,227,40 });
	neogeoAnim.PushBack({ 0,1115,227,40 });
	neogeoAnim.PushBack({ 0,1072,227,40 });
	neogeoAnim.PushBack({ 0,1030,227,40 });
	neogeoAnim.PushBack({ 0,987,227,40 });
	neogeoAnim.PushBack({ 0,944,227,40 });
	neogeoAnim.PushBack({ 0,899,227,40 });
	neogeoAnim.PushBack({ 0,855,227,40 });
	neogeoAnim.PushBack({ 0,810,227,40 });
	neogeoAnim.PushBack({ 0,767,227,40 });//This is when size starts to reduce
	neogeoAnim.PushBack({ 0,725,227,38 });
	neogeoAnim.PushBack({ 0,686,227,35 });
	neogeoAnim.PushBack({ 0,650,227,32 });
	neogeoAnim.PushBack({ 0,617,227,30 });
	neogeoAnim.PushBack({ 0,587,227,28 });
	neogeoAnim.PushBack({ 0,559,227,25 });
	neogeoAnim.PushBack({ 0,531,227,22 });
	neogeoAnim.PushBack({ 0,508,227,20 });
	neogeoAnim.PushBack({ 0,484,227,18 });
	neogeoAnim.PushBack({ 0,466,227,15 });
	neogeoAnim.PushBack({ 0,451,227,12 });
	neogeoAnim.PushBack({ 0,438,227,10 });
	neogeoAnim.PushBack({ 0,425,227,8 });
	neogeoAnim.PushBack({ 0,414,227,5 });
	neogeoAnim.PushBack({ 0,408,227,2 });
	neogeoAnim.PushBack({ 0,401,227,2 });
	neogeoAnim.PushBack({ 0,393,227,5 });
	neogeoAnim.PushBack({ 0,381,227,8 });
	neogeoAnim.PushBack({ 0,365,227,10 });
	neogeoAnim.PushBack({ 0,348,227,12 });
	neogeoAnim.PushBack({ 0,330,227,15 });
	neogeoAnim.PushBack({ 0,310,227,18 });
	neogeoAnim.PushBack({ 0,286,227,20 });
	neogeoAnim.PushBack({ 0,262,227,22 });
	neogeoAnim.PushBack({ 0,235,227,25 });
	neogeoAnim.PushBack({ 0,203,227,28 });
	neogeoAnim.PushBack({ 0,168,227,30 });
	neogeoAnim.PushBack({ 0,129,227,32 });
	neogeoAnim.PushBack({ 0,88,227,35 });
	neogeoAnim.PushBack({ 0,44,227,38 });
	neogeoAnim.PushBack({ 0,0,227,40 });
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

	return ret;
}
update_status ModuleNeoGeo::Update()
{	
	//We change the scene if the player presses space
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App-> GameTitle, 0.5f);
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
		//Animate the logo
		App->render->Blit(neogeoTx, 40, 52, &neogeoAnim.GetCurrentFrame(), 0.0f);//40, 52 positions calculated from the original game
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
		App->fade->FadeToBlack(this, App->GameTitle, 0.5f);
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
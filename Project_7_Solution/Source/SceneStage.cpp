#include "SceneStage.h"
#include "getScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneStage::SceneStage(bool startEnabled) : Module(startEnabled)
{

}

SceneStage::~SceneStage()
{

}

// Load assets
bool SceneStage::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	Texture1 = App->textures->Load("Assets/Stage1.png");
	Texture2 = App->textures->Load("Assets/Stage1-2.png");
	Texture3 = App->textures->Load("Assets/Stage1-3.png");
	Texture4 = App->textures->Load("Assets/Stage1-4.png");
	Texture5 = App->textures->Load("Assets/Stage1-5.png");
	Texture6 = App->textures->Load("Assets/Stage1-6.png");
	Texture7 = App->textures->Load("Assets/Stage1-7.png");
	Texture8 = App->textures->Load("Assets/Stage1-8.png");
	Texture9 = App->textures->Load("Assets/Stage2.png");
	Texture10 = App->textures->Load("Assets/Stage2-2.png");
	Texture11 = App->textures->Load("Assets/Stage2-3.png");
	Texture12 = App->textures->Load("Assets/Stage2-4.png");
	Texture13 = App->textures->Load("Assets/Stage2-5.png");
	Texture14 = App->textures->Load("Assets/Stage2-6.png");
	Texture15 = App->textures->Load("Assets/Stage2-7.png");
	Texture16 = App->textures->Load("Assets/Stage2-8.png");
	
	App->audio->PlayMusic("Assets/StageSelect.ogg", 1.0f);
	enter = App->audio->LoadFx("Assets/SelectSound.wav");

	App->render->ResetCamera();

	bgTexture = Texture1; 
	bgTexture2 = Texture9;
	cd = 0;
	return ret;
}

update_status SceneStage::Update()
{
	GamePad& pad = App->input->pads[0];

	if (!changeTex)
	{

		cd++;

		if (cd >= 10)
		{
			if (bgTexture == Texture1)
			{
				bgTexture = Texture2;
			}
			else if(bgTexture == Texture2)
			{
				bgTexture = Texture3;
			}
			else if (bgTexture == Texture3)
			{
				bgTexture = Texture4;
			}
			else if (bgTexture == Texture4)
			{
				bgTexture = Texture5;
			}
			else if (bgTexture == Texture5)
			{
				bgTexture = Texture6;
			}
			else if (bgTexture == Texture6)
			{
				bgTexture = Texture7;
			}
			else if (bgTexture == Texture7)
			{
				bgTexture = Texture8;
			}
			else if (bgTexture == Texture8)
			{
				bgTexture = Texture1;
			}

			cd = 0;
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
		{
			App->audio->PlayFx(enter);
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		}
	}
	else
	{
		cd++;

		if (cd >= 10)
		{
			if (bgTexture2 == Texture9)
			{
				bgTexture2 = Texture10;
			}
			else if (bgTexture2 == Texture10)
			{
				bgTexture2 = Texture11;
			}
			else if (bgTexture2 == Texture11)
			{
				bgTexture2 = Texture12;
			}
			else if (bgTexture2 == Texture12)
			{
				bgTexture2 = Texture13;
			}
			else if (bgTexture2 == Texture13)
			{
				bgTexture2 = Texture14;
			}
			else if (bgTexture2 == Texture14)
			{
				bgTexture2 = Texture15;
			}
			else if (bgTexture2 == Texture15)
			{
				bgTexture2 = Texture16;
			}
			else if (bgTexture2 == Texture16)
			{
				bgTexture2 = Texture9;
			}

			cd = 0;
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
		{
			App->audio->PlayFx(enter);
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 90);
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status SceneStage::PostUpdate()
{
	// Draw everything
	if (!changeTex)
	{
		App->render->Blit(bgTexture, 0, 0, NULL);
	}
	else
	{
		App->render->Blit(bgTexture2, 0, 0, NULL);
	}

	return update_status::UPDATE_CONTINUE;
}
#include "SceneIntro.h"
#include "getScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollisions.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	SegaLogo = App->textures->Load("Assets/IntroSegaLogo.png");
	SegaCreditos = App->textures->Load("Assets/IntroSegaLogo2.png");
	nameTexture = App->textures->Load("Assets/NameScreen.png");
	Texture1 = App->textures->Load("Assets/Main_Menu.png");
	Texture2 = App->textures->Load("Assets/Battle_Game.png");
	Texture3 = App->textures->Load("Assets/Password.png");
	Texture4 = App->textures->Load("Assets/Area1.png");
	Texture5 = App->textures->Load("Assets/Area2.png");
	App->audio->PlayMusic("Assets/TitleScreen.ogg", 1.0f);
	arrow = App->audio->LoadFx("Assets/ChangeOptionSound.wav");
	enter = App->audio->LoadFx("Assets/SelectSound.wav");

	App->render->ResetCamera();

	intro = nameTexture;
	bgTexture = Texture1;

	changeTex = false;
	changeTex2 = false;
	cd = 0;

	return ret;
}

update_status SceneIntro::PreUpdate()
{
	if (!changeTex && !changeTex2)
	{
		cd++;
		if (intro == nameTexture && cd >= 150 )
		{
			intro = SegaLogo;
			cd = 0;
		}
		else if (intro == SegaLogo && cd >= 150)
		{
			intro = SegaCreditos;
			cd = 0;
		}
		else if (intro == SegaCreditos && cd >= 150)
		{
			changeTex = true;
			cd = 0;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];

	if (pad.up == true)
	{
		App->input->keys[SDL_SCANCODE_W] = KEY_STATE::KEY_DOWN;
	}
	else if (pad.down == true)
	{
		App->input->keys[SDL_SCANCODE_S] = KEY_STATE::KEY_DOWN;
	}
	if (pad.a == true)
	{
		App->input->keys[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_DOWN;
	}

	if (changeTex)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN/* || pad.a == true*/)
		{
			App->audio->PlayFx(enter);
			changeTex2 = true;
			changeTex = false;
		}

		// images
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN/* || pad.down == true*/)
		{
			if (bgTexture == Texture1)
			{
				App->audio->PlayFx(arrow);
				bgTexture = Texture2;
			}
			else if (bgTexture == Texture2)
			{
				App->audio->PlayFx(arrow);
				bgTexture = Texture3;
			}
		}
		else if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN/* || pad.up == true*/)
		{
			if (bgTexture == Texture2)
			{
				App->audio->PlayFx(arrow);
				bgTexture = Texture1;
			}
			else if (bgTexture == Texture3)
			{
				App->audio->PlayFx(arrow);
				bgTexture = Texture2;
			}
		}
	}
	else if (changeTex2)
	{
		cd++;

		if (cd >= 75)
		{
			if (bgTexture == Texture4)
			{
				bgTexture = Texture5;
			}
			else
			{
				bgTexture = Texture4;
			}
			
			cd = 0;
		}

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN/* || pad.a == true*/)
		{
			App->audio->PlayFx(enter);
			App->fade->FadeToBlack(this, (Module*)App->sceneStage, 90);
		}
	}

	// level selection
	if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 0);
	}
	else if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_2, 0);
	}
	else if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_3, 0);
	}

	return update_status::UPDATE_CONTINUE;
}

update_status SceneIntro::PostUpdate()
{
	// Draw everything
	if (changeTex || changeTex2)
	{
		App->render->Blit(bgTexture, 0, 0, NULL);
	}
	else
	{
		App->render->Blit(intro, 0, 0, NULL);
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->getScene->Enable();

	return true;
}
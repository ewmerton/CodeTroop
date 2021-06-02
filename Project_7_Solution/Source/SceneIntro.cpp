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

	nameTexture = App->textures->Load("Assets/NameScreen.png");
	Texture1 = App->textures->Load("Assets/Main_Menu.png");
	Texture2 = App->textures->Load("Assets/.png");
	App->audio->PlayMusic("Assets/TitleScreen.ogg", 1.0f);

	App->render->ResetCamera();

	bgTexture = Texture1;

	changeTex = false;
	cd = 0;

	return ret;
}

update_status SceneIntro::PreUpdate()
{
	if (!changeTex)
	{
		cd++;
	}

	if (cd >= 400)
	{
		changeTex = true;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status SceneIntro::Update()
{
	if (changeTex)
	{
		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		}

		// images
		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_DOWN)
		{
			bgTexture = Texture2;
		}
		else if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN)
		{
			bgTexture = Texture1;
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
	if (changeTex)
	{
		App->render->Blit(bgTexture, 0, 0, NULL);
	}
	else
	{
		App->render->Blit(nameTexture, 0, 0, NULL);
	}
	
	return update_status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->getScene->Enable();

	return true;
}
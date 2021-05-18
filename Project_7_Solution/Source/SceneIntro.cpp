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
	bgTexture = App->textures->Load("Assets/Main_Menu.png");
	App->audio->PlayMusic("Assets/TitleScreen.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	changeTex = false;
	cd = 0;

	App->getScene->Disable();
	App->collisions->Disable();

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
	App->collisions->Enable();

	return true;
}
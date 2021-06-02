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
	Texture2 = App->textures->Load("Assets/Stage2.png");
	App->audio->PlayMusic("Assets/StageSelect.ogg", 1.0f);
	enter = App->audio->LoadFx("Assets/SelectSound.wav");

	App->render->ResetCamera();

	bgTexture = nullptr;

	return ret;
}

update_status SceneStage::Update()
{
	GamePad& pad = App->input->pads[0];

	if (!changeTex)
	{
		bgTexture = Texture1;

		if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
		{
			App->audio->PlayFx(enter);
			App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
		}
	}
	else
	{
		bgTexture = Texture2;

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
	App->render->Blit(bgTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}
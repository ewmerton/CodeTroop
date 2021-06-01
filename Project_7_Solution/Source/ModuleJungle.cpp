#include "ModuleJungle.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleCT.h"

#include "SceneLevel1.h"
#include "SceneLevel2.h"

ModuleJungle::ModuleJungle(bool startEnabled) : Module(startEnabled)
{

}

ModuleJungle::~ModuleJungle()
{

}

// Load assets
bool ModuleJungle::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	jungleTextureL = App->textures->Load("Assets/JungleL.png");
	jungleTextureR = App->textures->Load("Assets/JungleR.png");

	position.x = 24;  //Esquina arriba izq
	position.y = 41;  //primera fila

	return ret;
}

update_status ModuleJungle::Update()
{
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleJungle::PostUpdate()
{
	// Draw everything --------------------------------------
	if (App->sceneLevel_1->IsEnabled() == true)
	{
		App->render->Blit(jungleTextureL,position.x, position.y, NULL);
		App->render->Blit(jungleTextureR, position.x, position.y, NULL);
	}
	else if (App->sceneLevel_2->IsEnabled() == true)
	{
		App->render->Blit(jungleTextureL, position.x, position.y, NULL);
		App->render->Blit(jungleTextureR, position.x, position.y, NULL);
	}

	return update_status::UPDATE_CONTINUE;
}


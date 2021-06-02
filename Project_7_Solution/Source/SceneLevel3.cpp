#include "SceneLevel3.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleMonkey.h"
#include "ModuleRock.h"
#include "ModuleLittleTower.h"
#include "ModuleFlower.h"
#include "ModuleRedFlower.h"
#include "ModuleCT.h"

SceneLevel3::SceneLevel3(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel3::~SceneLevel3()
{

}

// Load assets
bool SceneLevel3::Start()
{	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/BossMap.png");
	hudTexture = App->textures->Load("Assets/HUD.png");

	App->audio->PlayMusic("Assets/BossTheme.ogg", 1.0f);

	//Border colliders
	App->collisions->AddCollider({ 0, 25, 256, 16 }, Collider::Type::WALL); //up
	App->collisions->AddCollider({ 0, 217, 256, 16 }, Collider::Type::WALL); //down
	App->collisions->AddCollider({ 8, 25, 16, 208 }, Collider::Type::WALL); //left
	App->collisions->AddCollider({ 232, 25, 16, 208 }, Collider::Type::WALL); //right

	for (int i = 0; i < 32 * 6; i += 32)
	{
		for (int j = 0; j < 32 * 5; j += 32)
		{
			App->collisions->AddCollider({ 40 + i, 57 + j, 16, 16 }, Collider::Type::ROCK, this);
		}
	}

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::BANANA, 90, -3);

	App->render->ResetCamera();

	// Enables
	App->bomb->Enable();
	App->player->Enable();
	App->monkey->Enable();
	App->enemies->Enable();
	App->rock->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel3::Update()
{
	App->render->camera.x += 0;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel3::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(hudTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel3::CleanUp()
{
	App->bomb->Disable();
	App->player->Disable();
	App->monkey->Disable();
	App->enemies->Disable();
	App->rock->Disable();
	App->collisions->Disable();

	return true;
}
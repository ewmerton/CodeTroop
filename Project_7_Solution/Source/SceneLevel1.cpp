#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRock.h"
#include "ModuleLittleTower.h"
#include "ModuleFlower.h"
#include "ModuleRedFlower.h"
#include "ModuleCT.h"
#include "ModuleJungle.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Map.png");
	hudTexture = App->textures->Load("Assets/HUD.png");

	App->audio->PlayMusic("Assets/Jumming_Jungle.ogg", 1.0f);

	//Border colliders
	App->collisions->AddCollider({ 0, 25, 256, 16 }, Collider::Type::WALL); //up
	App->collisions->AddCollider({ 0, 217, 256, 16 }, Collider::Type::WALL); //down
	App->collisions->AddCollider({ 8, 25, 16, 208 }, Collider::Type::WALL); //left
	App->collisions->AddCollider({ 232, 25, 16, 208 }, Collider::Type::WALL); //right

	for (int i = 0; i < 32 * 6; i += 32)
	{
		for (int j = 0; j < 32 * 5; j += 32)
		{
			if ((i == 32 * 2 || i == 32 * 3) && (j == 32 * 1 || j == 32 * 2))
			{

			}
			else {
				App->collisions->AddCollider({ 40 + i, 57 + j, 16, 16 }, Collider::Type::ROCK, this);
			}
		}
	}
	
	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::ROBOT, 53, 169);
	App->enemies->AddEnemy(ENEMY_TYPE::ROBOT2, 181, 57);

	App->render->ResetCamera();

	// Enables
	App->bomb->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->rock->Enable();
	App->little_tower->Enable();
	App->flower->Enable();
	App->red_flower->Enable();
	App->tower->Enable();
	App->jungle->Enable();
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel1::Update()
{
	App->render->camera.x += 0;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(hudTexture, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->bomb->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->rock->Disable();
	App->little_tower->Disable();
	App->flower->Disable();
	App->red_flower->Disable();
	App->tower->Disable();
	App->jungle->Disable();
	App->collisions->Disable();

	return true;
}
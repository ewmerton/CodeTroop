#include "SceneLevel1.h"
#include "getScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRock.h"
#include "ModuleFlower.h"
#include "ModuleCT.h"

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
	App->collisions->AddCollider({ 0, 25, 24, 208 }, Collider::Type::WALL); //left
	App->collisions->AddCollider({ 232, 25, 24, 208 }, Collider::Type::WALL); //right
	
	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::ROBOT, 53, 155);
	App->enemies->AddEnemy(ENEMY_TYPE::SNAIL, 181, 125);

	// Rocks
	for (uint i = 0; i < 32 * 6; i += 32)
	{
		for (uint j = 0; j < 32 * 5; j += 32)
		{
			if ((i == 32 * 2 || i == 32 * 3) && (j == 32 * 1 || j == 32 * 2))
			{

			}
			else {
				App->rock->AddRock(i + 40, j + 57);
				//App->flower->AddFlower(40 + 16+i, 57+j);

			}
		}
	}

	// Flowers
	/*for (uint i = 0; i < 32 * 6; i += 32)
	{
		for (uint j = 0; j < 32 * 5; j += 32)
		{
			App->flower->AddFlower(40+16+i,57+j);
		}
	}
	*/
	//App->flower->AddFlower(40+16,57);
	
	App->player->Enable();
	App->enemies->Enable();
	App->rock->Enable();
	App->flower->Enable();
	App->tower->Enable();

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
	App->render->Blit(hudTexture, 0, 1);



	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->rock->Disable();
	App->flower->Disable();
	App->tower->Disable();

	return true;
}
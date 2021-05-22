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

	// Enables
	App->player->Enable();
	App->enemies->Enable();
	App->rock->Enable();
	App->little_tower->Enable();
	App->flower->Enable();
	App->red_flower->Enable();
	App->tower->Enable();
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
	App->render->Blit(hudTexture, 0, 1, NULL);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->rock->Disable();
	App->little_tower->Disable();
	App->flower->Disable();
	App->red_flower->Disable();
	App->tower->Disable();
	App->collisions->Disable();

	return true;
}
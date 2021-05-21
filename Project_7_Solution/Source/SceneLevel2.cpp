#include "SceneLevel2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleRock.h"
#include "ModuleFlower.h"
#include "ModuleRedFlower.h"
#include "ModuleCT.h"

SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/MapLevel2.png");
	brTexture = App->textures->Load("Assets/Barandilla.png");
	hudTexture = App->textures->Load("Assets/HUD.png");

	App->audio->PlayMusic("Assets/Jumming_Jungle.ogg", 1.0f);

	//Border colliders
	App->collisions->AddCollider({ 0, 25, 512, 16 }, Collider::Type::WALL); //up
	App->collisions->AddCollider({ 0, 217, 512, 16 }, Collider::Type::WALL); //down
	App->collisions->AddCollider({ 0, 25, 16, 208 }, Collider::Type::WALL); //left
	App->collisions->AddCollider({ 496, 25, 16, 208 }, Collider::Type::WALL); //right
	App->collisions->AddCollider({ 168, 25, 240, 48 }, Collider::Type::WALL); //top
	App->collisions->AddCollider({ 168, 185, 240, 48 }, Collider::Type::WALL); //bottom
	App->collisions->AddCollider({ 264, 57, 48, 64 }, Collider::Type::WALL); //river top
	App->collisions->AddCollider({ 264, 137, 48, 64 }, Collider::Type::WALL); //river bottom


	// Enemies ---
	//App->enemies->AddEnemy(ENEMY_TYPE::ROBOT, 53, 155);
	//App->enemies->AddEnemy(ENEMY_TYPE::SNAIL, 181, 125);

	// Enables
	App->player->Enable();
	App->enemies->Enable();
	App->rock->Enable();
	App->flower->Enable();
	App->red_flower->Enable();
	App->tower->Enable();

	return ret;
}

update_status SceneLevel2::Update()
{
	App->render->camera.x += 0;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(brTexture, 260, 127, NULL);
	App->render->Blit(hudTexture, 0, 1);



	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel2::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->rock->Disable();
	App->flower->Disable();
	App->red_flower->Disable();
	App->tower->Disable();

	return true;
}
#include "SceneLevel2.h"

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
	App->collisions->AddCollider({ 8, 25, 16, 208 }, Collider::Type::WALL); //left
	App->collisions->AddCollider({ 488, 25, 16, 208 }, Collider::Type::WALL); //right
	App->collisions->AddCollider({ 168, 25, 240, 48 }, Collider::Type::WALL); //top
	App->collisions->AddCollider({ 168, 185, 240, 48 }, Collider::Type::WALL); //bottom
	App->collisions->AddCollider({ 264, 57, 48, 56 }, Collider::Type::WALL); //river top
	App->collisions->AddCollider({ 264, 142, 48, 60 }, Collider::Type::WALL); //river bottom

	//Rock colliders
	/*App->collisions->AddCollider({ 40, 57, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 72, 57, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 104, 57, 48, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 136, 57, 16, 48 }, Collider::Type::ROCK);

	App->collisions->AddCollider({ 40, 89, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 72, 89, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 104, 89, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 168, 89, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 200, 89, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 232, 89, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 328, 89, 48, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 392, 89, 16, 16 }, Collider::Type::ROCK);

	App->collisions->AddCollider({ 40, 121, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 72, 121, 48, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 136, 121, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 168, 121, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 200, 121, 16, 48 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 232, 121, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 328, 121, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 360, 121, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 392, 121, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 424, 121, 16, 48 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 456, 121, 16, 16 }, Collider::Type::ROCK);

	App->collisions->AddCollider({ 40, 153, 16, 48 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 72, 153, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 104, 153, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 136, 153, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 168, 153, 48, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 232, 153, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 328, 153, 48, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 392, 153, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 424, 153, 48, 16 }, Collider::Type::ROCK);

	App->collisions->AddCollider({ 40, 185, 48, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 104, 185, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 136, 185, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 424, 185, 16, 16 }, Collider::Type::ROCK);
	App->collisions->AddCollider({ 456, 185, 16, 16 }, Collider::Type::ROCK);*/

	// Enemies ---
	//App->enemies->AddEnemy(ENEMY_TYPE::ROBOT, 53, 155);
	//App->enemies->AddEnemy(ENEMY_TYPE::SNAIL, 181, 125);

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
	App->collisions->Enable();

	return ret;
}

update_status SceneLevel2::Update()
{
	iPoint p = App->player->GetPlayerPos();
	App->render->MoveCamera({ p.x, 0 });

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(brTexture, 260, 127, NULL);
	App->render->Blit(hudTexture, App->render->camera.x/SCREEN_SIZE, 0);

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel2::CleanUp()
{
	App->bomb->Disable();
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
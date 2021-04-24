#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
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
	
	

	return ret;
}

update_status ModuleScene::Update()
{
	App->render->camera.x += 0;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(hudTexture, 0, 1);



	return update_status::UPDATE_CONTINUE;
}
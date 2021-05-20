#include "ModuleCT.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"

ModuleCT::ModuleCT(bool startEnabled) : Module(startEnabled)
{
	// idle
	idleAnim.PushBack({ 0, 0, 48, 54 });
	idleAnim.PushBack({ 64, 0, 48, 54 });
	idleAnim.PushBack({ 128, 0, 48, 54 });
	idleAnim.PushBack({ 192, 0, 48, 54 });
	idleAnim.speed = 0.05f;

	// object reclaimed
	outAnim.PushBack({ 0, 56, 48, 54 });
	outAnim.PushBack({ 64, 56, 48, 54 });
	outAnim.PushBack({ 128, 56, 48, 54 });
	outAnim.speed = 0.03f;
}

ModuleCT::~ModuleCT()
{

}

// Load assets
bool ModuleCT::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	texture = App->textures->Load("Assets/centralTower.png");

	currentAnimation = &idleAnim;

	//Object colliders
	position.x = 105;
	position.y = 82;

	if (App->sceneLevel_1->IsEnabled() == true)
	{
		// Up
		collider[0] = App->collisions->AddCollider({ position.x, position.y + 10, 48, 10 }, Collider::Type::ROCK, this);
		// Left
		collider[1] = App->collisions->AddCollider({ position.x, position.y + 20, 16, 34 }, Collider::Type::ROCK, this);
		// Right
		collider[2] = App->collisions->AddCollider({ position.x + 32, position.y + 20, 16, 34 }, Collider::Type::ROCK, this);
		// Moon
		moon = App->collisions->AddCollider({ position.x + 16, position.y + 20, 16, 8 }, Collider::Type::MOON, this);

	}

	return ret;
}

update_status ModuleCT::Update()
{
	currentAnimation->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleCT::PostUpdate()
{
	// Draw everything --------------------------------------
	if (App->sceneLevel_1->IsEnabled() == true)
	{
		App->render->Blit(texture, position.x, position.y, &(currentAnimation->GetCurrentFrame()));
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleCT::MoonColected()
{
	currentAnimation = &outAnim;
}
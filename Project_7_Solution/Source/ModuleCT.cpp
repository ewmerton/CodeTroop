#include "ModuleCT.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"
#include "SceneLevel2.h"

ModuleCT::ModuleCT(bool startEnabled) : Module(startEnabled)
{
	// covert
	covertAnim.PushBack({ 0, 180, 48, 64 });
	covertAnim.PushBack({ 64, 180, 48, 64 });
	covertAnim.PushBack({ 128, 180, 48, 64 });
	covertAnim.PushBack({ 192, 180, 48, 64 });
	covertAnim.speed = 0.05f;

	// idle
	idleAnim.PushBack({ 0, 0, 48, 64 });
	idleAnim.PushBack({ 64, 0, 48, 64 });
	idleAnim.PushBack({ 128, 0, 48, 64 });
	idleAnim.PushBack({ 192, 0, 48, 64 });
	idleAnim.speed = 0.05f;

	// object reclaimed
	outAnim.PushBack({ 0, 90, 48, 64 });
	outAnim.PushBack({ 64, 90, 48, 64 });
	outAnim.PushBack({ 128, 90, 48, 64 });
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

	currentAnimation = &covertAnim;	

	if (App->sceneLevel_1->IsEnabled() == true)
	{
		position.x = 104;
		position.y = 72;

		collider[0] = App->collisions->AddCollider({ position.x, position.y + 17, 16, 16 }, Collider::Type::ROCK, this);
		collider[1] = App->collisions->AddCollider({ position.x + 16, position.y + 17, 16, 16 }, Collider::Type::ROCK, this);
		collider[2] = App->collisions->AddCollider({ position.x + 32, position.y + 17, 16, 16 }, Collider::Type::ROCK, this);
		collider[3] = App->collisions->AddCollider({ position.x, position.y + 33, 16, 16 }, Collider::Type::ROCK, this);
		collider[4] = App->collisions->AddCollider({ position.x + 32, position.y + 33, 16, 16 }, Collider::Type::ROCK, this);
		collider[5] = App->collisions->AddCollider({ position.x, position.y + 49, 16, 16 }, Collider::Type::ROCK, this);
		collider[6] = App->collisions->AddCollider({ position.x + 32, position.y + 49, 16, 16 }, Collider::Type::ROCK, this);
		// Moon
		moon = App->collisions->AddCollider({ position.x + 16, position.y + 30, 16, 8 }, Collider::Type::MOON, this);
		barrier = App->collisions->AddCollider({ position.x + 16, position.y + 38, 16, 8 }, Collider::Type::WALL, this);

	}
	else if (App->sceneLevel_2->IsEnabled() == true)
	{
		position.x = 424;
		position.y = 40;

		collider[0] = App->collisions->AddCollider({ position.x, position.y + 17, 16, 16 }, Collider::Type::ROCK, this);
		collider[1] = App->collisions->AddCollider({ position.x + 16, position.y + 17, 16, 16 }, Collider::Type::ROCK, this);
		collider[2] = App->collisions->AddCollider({ position.x + 32, position.y + 17, 16, 16 }, Collider::Type::ROCK, this);
		collider[3] = App->collisions->AddCollider({ position.x, position.y + 33, 16, 16 }, Collider::Type::ROCK, this);
		collider[4] = App->collisions->AddCollider({ position.x + 32, position.y + 33, 16, 16 }, Collider::Type::ROCK, this);
		collider[5] = App->collisions->AddCollider({ position.x, position.y + 49, 16, 16 }, Collider::Type::ROCK, this);
		collider[6] = App->collisions->AddCollider({ position.x + 32, position.y + 49, 16, 16 }, Collider::Type::ROCK, this);
		// Moon
		moon = App->collisions->AddCollider({ position.x + 16, position.y + 30, 16, 8 }, Collider::Type::MOON, this);
		barrier = App->collisions->AddCollider({ position.x + 16, position.y + 38, 16, 8 }, Collider::Type::WALL, this);

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
	else if (App->sceneLevel_2->IsEnabled() == true)
	{
		App->render->Blit(texture, position.x, position.y, &(currentAnimation->GetCurrentFrame()));
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleCT::TowerDestroyed()
{
	currentAnimation = &idleAnim;
	barrier->pendingToDelete = true;
}

void ModuleCT::MoonColected()
{
	currentAnimation = &outAnim;
}
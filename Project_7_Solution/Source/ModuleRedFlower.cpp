#include "ModuleRedFlower.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"
#include "SceneLevel2.h"

ModuleRedFlower::ModuleRedFlower(bool startEnabled) : Module(startEnabled)
{
	for (int i = 0; i < NUM_RED_FLOWERS; i++)
	{
		// Idle
		idle.PushBack({ 0, 0, 16, 16 });

		// walk Up
		dead.PushBack({ 16, 0, 16, 16 });
		dead.PushBack({ 32, 0, 16, 16 });
		dead.PushBack({ 48, 0, 16, 16 });
		dead.PushBack({ 64, 0, 16, 16 });
		dead.PushBack({ 80, 0, 16, 16 });
		dead.speed = 0.05f;
		dead.loop = false;
	}
}

ModuleRedFlower::~ModuleRedFlower()
{

}

// Load assets
bool ModuleRedFlower::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	flowerTexture = App->textures->Load("Assets/RedFlower_Destroy.png");  

	position.x = 24;
	position.y = 41;

	for (int i = 0; i < NUM_RED_FLOWERS; i++)
	{
		currentAnimation[i] = &idle;
	}

	if (App->sceneLevel_1->IsEnabled() == true)
	{
		red_flowers[0] = CreateRedFlower(position.x+64, position.y+32, flowerTexture);
		red_flowers[1] = CreateRedFlower(position.x + 128, position.y + 32, flowerTexture);
		
		red_flowers[2] = CreateRedFlower(position.x + 64, position.y + 128, flowerTexture);
		red_flowers[3] = CreateRedFlower(position.x + 128, position.y + 128, flowerTexture);

	}
	if (App->sceneLevel_2->IsEnabled() == true)
	{
		red_flowers[0] = CreateRedFlower(position.x, position.y, flowerTexture);
		red_flowers[1] = CreateRedFlower(position.x + 16, position.y + 16, flowerTexture);
	}


	return ret;
}

update_status ModuleRedFlower::Update()
{
	for (int i = 0; i < NUM_RED_FLOWERS; i++)
	{
		currentAnimation[i]->Update();


		if (red_flowers[i].isDestroyed)
		{
			red_flowers[i].dCount++;
			if (red_flowers[i].dCount >= 115)
			{
				red_flowers[i].destroyed = true;
			}
			if (red_flowers[i].destroyed)
			{
				red_flowers[i].colliderT->pendingToDelete = true;
			}
		}
	}
	return update_status::UPDATE_CONTINUE;
}


// Update: draw background
update_status ModuleRedFlower::PostUpdate()
{
	// Draw everything --------------------------------------
	for (int i = 0; i < NUM_RED_FLOWERS; i++)
	{
		if (App->sceneLevel_1->IsEnabled() == true && !red_flowers[i].destroyed)
		{
			App->render->Blit(red_flowers[i].flowerT, red_flowers[i].x, red_flowers[i].y, &(currentAnimation[i]->GetCurrentFrame()));
		}
		
		if (App->sceneLevel_2->IsEnabled() == true && !red_flowers[i].destroyed)
		{
			App->render->Blit(red_flowers[i].flowerT, red_flowers[i].x, red_flowers[i].y, &(currentAnimation[i]->GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}



void ModuleRedFlower::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < NUM_RED_FLOWERS; ++i)
	{
		if (red_flowers[i].colliderT == c1 && !red_flowers[i].isDestroyed)
		{
			switch (c2->type)
			{
			case Collider::Type::PLAYER_SHOT:
			{
				red_flowers[i].isDestroyed = true;
				currentAnimation[i] = &dead;
			} break;

			default:
				break;
			}
			break;
		}
	}
}

RedFlower ModuleRedFlower::CreateRedFlower(int x, int y, SDL_Texture* t)
{
	RedFlower f;

	f.colliderT = App->collisions->AddCollider({ x, y, 16, 16 }, Collider::Type::RED_FLOWER, this);
	f.flowerT = t;
	f.x = x;
	f.y = y;
	f.isDestroyed = false;

	return f;
}


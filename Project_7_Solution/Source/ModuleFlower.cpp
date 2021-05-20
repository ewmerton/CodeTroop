#include "ModuleFlower.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"

ModuleFlower::ModuleFlower(bool startEnabled) : Module(startEnabled)
{

}

ModuleFlower::~ModuleFlower()
{

}

// Load assets
bool ModuleFlower::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	flowerTexture = App->textures->Load("Assets/YellowFlower.png");
	
	position.x = 56;
	position.y = 57;

	if (App->sceneLevel_1->IsEnabled() == true)
	{
		flowers[0] = CreateFlower(position.x, position.y, flowerTexture);
		flowers[1] = CreateFlower(position.x + 16, position.y + 16, flowerTexture);
	}

	return ret;
}

// Update: draw background
update_status ModuleFlower::PostUpdate()
{
	// Draw everything --------------------------------------
	for (int i = 0; i < NUM_FLOWERS; i++)
	{
		if (App->sceneLevel_1->IsEnabled() == true && !flowers[i].isDestroyed)
		{
			App->render->Blit(flowers[i].flowerT, flowers[i].x, flowers[i].y, NULL);
		}
	}
	

	for (int i = 0; i < NUM_FLOWERS; i++)
	{
		if (flowers[i].isDestroyed == true)
		{
			flowers[i].colliderT->pendingToDelete = true;
		}
	}
	
	return update_status::UPDATE_CONTINUE;
}

void ModuleFlower::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < NUM_FLOWERS; ++i)
	{
		if (flowers[i].colliderT == c1 && !flowers[i].isDestroyed)
		{
			switch (c2->type)
			{
			case Collider::Type::PLAYER_SHOT:
			{
				flowers[i].isDestroyed = true;
			} break;

			default:
				break;
			}
			break;
		}
	}
}

Flower ModuleFlower::CreateFlower(int x, int y, SDL_Texture* t)
{
	Flower f;

	f.colliderT = App->collisions->AddCollider({ x, y, 16, 16 }, Collider::Type::FLOWER, this);
	f.flowerT = t;
	f.x = x;
	f.y = y;
	f.isDestroyed = false;

	return f;
}
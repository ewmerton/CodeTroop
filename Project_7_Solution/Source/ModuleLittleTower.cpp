#include "ModuleLittleTower.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"
#include "SceneLevel2.h"

ModuleLittleTower::ModuleLittleTower(bool startEnabled) : Module(startEnabled)
{

}

ModuleLittleTower::~ModuleLittleTower()
{

}

// Load assets
bool ModuleLittleTower::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	little_towerTexture = App->textures->Load("Assets/Button.png");

	position.x = 24;  //Esquina arriba izq
	position.y = 41;  //primera fila

	if (App->sceneLevel_1->IsEnabled() == true)
	{
		little_towers[0] = CreateLittleTower(position.x + 80, position.y + 16, little_towerTexture);
		little_towers[1] = CreateLittleTower(position.x + 144, position.y + 16, little_towerTexture);

	}
	else if (App->sceneLevel_2->IsEnabled() == true)
	{
		//flowers[0] = CreateFlower(position.x, position.y, flowerTexture);
		//flowers[1] = CreateFlower(position.x + 16, position.y + 16, flowerTexture);

		for (int i = 0; i < NUM_LITTLE_TOWERS; i++)
		{
			// i = numero de torres de este nivel
			little_towers[i].little_towerT = nullptr;
		}
	}

	return ret;
}

// Update: draw background
update_status ModuleLittleTower::PostUpdate()
{
	// Draw everything --------------------------------------
	for (int i = 0; i < NUM_LITTLE_TOWERS; i++)
	{
		if (App->sceneLevel_1->IsEnabled() == true && !little_towers[i].isDestroyed)
		{
			App->render->Blit(little_towers[i].little_towerT, little_towers[i].x, little_towers[i].y, NULL);
		}
		else if (App->sceneLevel_2->IsEnabled() == true && !little_towers[i].isDestroyed)
		{
			App->render->Blit(little_towers[i].little_towerT, little_towers[i].x, little_towers[i].y, NULL);
		}
	}


	for (int i = 0; i < NUM_LITTLE_TOWERS; i++)
	{
		if (little_towers[i].isDestroyed == true)
		{
			little_towers[i].colliderT->pendingToDelete = true;
		}
	}

	return update_status::UPDATE_CONTINUE;
}



void ModuleLittleTower::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < NUM_LITTLE_TOWERS; ++i)
	{
		if (little_towers[i].colliderT == c1 && !little_towers[i].isDestroyed)
		{
			switch (c2->type)
			{
			case Collider::Type::PLAYER_SHOT:
			{
				little_towers[i].isDestroyed = true;
			} break;

			default:
				break;
			}
			break;
		}
	}
}

Little_tower ModuleLittleTower::CreateLittleTower(int x, int y, SDL_Texture* t)
{
	Little_tower f;

	f.colliderT = App->collisions->AddCollider({ x, y + 16, 16, 16 }, Collider::Type::FLOWER, this);
	f.little_towerT = t;
	f.x = x;
	f.y = y;
	f.isDestroyed = false;

	return f;
}
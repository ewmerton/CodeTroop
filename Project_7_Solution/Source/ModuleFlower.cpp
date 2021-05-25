#include "ModuleFlower.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"
#include "SceneLevel2.h"

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
	
	position.x = 24;  //Esquina arriba izq
	position.y = 41;  //primera fila

	if (App->sceneLevel_1->IsEnabled() == true)
	{
		flowers[0] = CreateFlower(position.x + 80, position.y, flowerTexture);
		flowers[1] = CreateFlower(position.x + 144, position.y, flowerTexture);
		flowers[2] = CreateFlower(position.x + 160, position.y, flowerTexture);

		flowers[3] = CreateFlower(position.x + 64, position.y + 16, flowerTexture);
		flowers[4] = CreateFlower(position.x + 128, position.y + 16, flowerTexture);
		flowers[5] = CreateFlower(position.x + 192, position.y + 16, flowerTexture);

		flowers[6] = CreateFlower(position.x + 16, position.y + 32, flowerTexture);
		flowers[7] = CreateFlower(position.x + 48, position.y + 32, flowerTexture);
		flowers[8] = CreateFlower(position.x + 176, position.y + 32, flowerTexture);
		flowers[9] = CreateFlower(position.x + 192, position.y + 32, flowerTexture);

		flowers[10] = CreateFlower(position.x + 64, position.y + 48, flowerTexture);
		flowers[11] = CreateFlower(position.x + 192, position.y + 48, flowerTexture);

		flowers[12] = CreateFlower(position.x + 48, position.y + 64, flowerTexture);
		flowers[13] = CreateFlower(position.x + 128, position.y + 64, flowerTexture);
		flowers[14] = CreateFlower(position.x + 192, position.y + 64, flowerTexture);

		flowers[15] = CreateFlower(position.x + 32, position.y + 80, flowerTexture);
		flowers[16] = CreateFlower(position.x + 64, position.y + 80, flowerTexture);
		flowers[17] = CreateFlower(position.x + 128, position.y + 80, flowerTexture);
		flowers[18] = CreateFlower(position.x + 160, position.y + 80, flowerTexture);

		/*flowers[19] = CreateFlower(position.x + 16, position.y + 96, flowerTexture);
		flowers[20] = CreateFlower(position.x + 32, position.y + 96, flowerTexture);
		flowers[21] = CreateFlower(position.x + 48, position.y + 96, flowerTexture);
		flowers[22] = CreateFlower(position.x + 80, position.y + 96, flowerTexture);
		flowers[23] = CreateFlower(position.x + 96, position.y + 96, flowerTexture);
		flowers[24] = CreateFlower(position.x + 176, position.y + 96, flowerTexture);*/
		
		flowers[25] = CreateFlower(position.x, position.y + 112, flowerTexture);
		flowers[26] = CreateFlower(position.x + 32, position.y + 112, flowerTexture);
		flowers[27] = CreateFlower(position.x + 64, position.y + 112, flowerTexture);
		flowers[28] = CreateFlower(position.x + 128, position.y + 112, flowerTexture);

		flowers[29] = CreateFlower(position.x, position.y + 128, flowerTexture);
		flowers[30] = CreateFlower(position.x + 16, position.y + 128, flowerTexture);
		flowers[31] = CreateFlower(position.x + 80, position.y + 128, flowerTexture);
		flowers[32] = CreateFlower(position.x + 160, position.y + 128, flowerTexture);
		flowers[33] = CreateFlower(position.x + 176, position.y + 128, flowerTexture);

		flowers[34] = CreateFlower(position.x + 64, position.y + 144, flowerTexture);
		flowers[35] = CreateFlower(position.x + 192, position.y + 144, flowerTexture);

		flowers[36] = CreateFlower(position.x + 48, position.y + 160, flowerTexture);
		flowers[37] = CreateFlower(position.x + 128, position.y + 160, flowerTexture);
		flowers[38] = CreateFlower(position.x + 144, position.y + 160, flowerTexture);

		flowers[39] = CreateFlower(position.x + 48, position.y, flowerTexture);
	}
	else if (App->sceneLevel_2->IsEnabled() == true)
	{

		//LEFT OF THE BRIDGE

		flowers[0] = CreateFlower(position.x + 96, position.y, flowerTexture);

		flowers[1] = CreateFlower(position.x + 64, position.y + 16, flowerTexture);

		flowers[2] = CreateFlower(position.x + 160, position.y + 32, flowerTexture);
		flowers[3] = CreateFlower(position.x + 176, position.y + 32, flowerTexture);
		flowers[4] = CreateFlower(position.x + 192, position.y + 32, flowerTexture);
		
		flowers[5] = CreateFlower(position.x, position.y + 48, flowerTexture);
		flowers[6] = CreateFlower(position.x + 64, position.y + 48, flowerTexture);
		flowers[7] = CreateFlower(position.x + 96, position.y + 48, flowerTexture);
		flowers[8] = CreateFlower(position.x + 128, position.y + 48, flowerTexture);
		flowers[9] = CreateFlower(position.x + 224, position.y + 48, flowerTexture);

		flowers[10] = CreateFlower(position.x, position.y + 64, flowerTexture);
		flowers[11] = CreateFlower(position.x + 32, position.y + 64, flowerTexture);
		flowers[12] = CreateFlower(position.x + 48, position.y + 64, flowerTexture);
		flowers[13] = CreateFlower(position.x + 112, position.y + 64, flowerTexture);
		flowers[14] = CreateFlower(position.x + 208, position.y + 64, flowerTexture);
		flowers[15] = CreateFlower(position.x + 224, position.y + 64, flowerTexture);

		flowers[16] = CreateFlower(position.x, position.y + 80, flowerTexture);
		flowers[17] = CreateFlower(position.x + 32, position.y + 80, flowerTexture);
		flowers[18] = CreateFlower(position.x + 160, position.y + 80, flowerTexture);
		flowers[19] = CreateFlower(position.x + 192, position.y + 80, flowerTexture);

		flowers[20] = CreateFlower(position.x, position.y + 96, flowerTexture);
		flowers[21] = CreateFlower(position.x + 16, position.y + 96, flowerTexture);
		flowers[22] = CreateFlower(position.x + 80, position.y + 96, flowerTexture);
		flowers[23] = CreateFlower(position.x + 112, position.y + 96, flowerTexture);
		flowers[24] = CreateFlower(position.x + 128, position.y + 96, flowerTexture);
		
		flowers[25] = CreateFlower(position.x + 192, position.y + 112, flowerTexture);
		flowers[26] = CreateFlower(position.x + 224, position.y + 112, flowerTexture);

		flowers[27] = CreateFlower(position.x + 48, position.y + 128, flowerTexture);
		flowers[28] = CreateFlower(position.x + 192, position.y + 128, flowerTexture);

		flowers[29] = CreateFlower(position.x, position.y + 160, flowerTexture);
		flowers[30] = CreateFlower(position.x + 32, position.y + 160, flowerTexture);
		flowers[31] = CreateFlower(position.x + 64, position.y + 160, flowerTexture);
		flowers[32] = CreateFlower(position.x + 80, position.y + 160, flowerTexture);

		//RIGHT OF THE BRIDGE
		flowers[33] = CreateFlower(position.x + 320, position.y + 32, flowerTexture);
		flowers[34] = CreateFlower(position.x + 384, position.y + 32, flowerTexture);

		flowers[36] = CreateFlower(position.x + 288, position.y + 48, flowerTexture);
		flowers[37] = CreateFlower(position.x + 352, position.y + 48, flowerTexture);
		flowers[38] = CreateFlower(position.x + 384, position.y + 48, flowerTexture);

		flowers[39] = CreateFlower(position.x + 320, position.y + 64, flowerTexture);
		flowers[40] = CreateFlower(position.x + 368, position.y + 64, flowerTexture);
		flowers[41] = CreateFlower(position.x + 384, position.y + 64, flowerTexture);

		flowers[42] = CreateFlower(position.x + 304, position.y + 96, flowerTexture);
		flowers[43] = CreateFlower(position.x + 336, position.y + 96, flowerTexture);
		flowers[44] = CreateFlower(position.x + 384, position.y + 96, flowerTexture);
		flowers[45] = CreateFlower(position.x + 432, position.y + 96, flowerTexture);

		flowers[46] = CreateFlower(position.x + 384, position.y + 128, flowerTexture);

		flowers[47] = CreateFlower(position.x + 384, position.y + 144, flowerTexture);
		flowers[48] = CreateFlower(position.x + 416, position.y + 144, flowerTexture);
		flowers[49] = CreateFlower(position.x + 448, position.y + 144, flowerTexture);

		/*
		for (int i = 30; i < NUM_FLOWERS; i++)
		{
			// i = numero de flores de este nivel
			flowers[i].flowerT = nullptr;
		}
		*/
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
		else if (App->sceneLevel_2->IsEnabled() == true && !flowers[i].isDestroyed)
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
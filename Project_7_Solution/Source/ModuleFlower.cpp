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

	return ret;
}

// Update: draw background
update_status ModuleFlower::PostUpdate()
{
	// Draw everything --------------------------------------
	if (App->sceneLevel_1->IsEnabled() == true)
	{
		for (uint i = 0; i < 32 * 6; i += 32)
		{
			for (uint j = 0; j < 32 * 5; j += 32)
			{
				App->render->Blit(flowerTexture, position.x+i,position.y+j,NULL);
			}
		}
	}
	//App->render->Blit(flowerTexture, 56, 57, NULL);
	return update_status::UPDATE_CONTINUE;
}

void ModuleFlower::AddFlower(int x, int y)
{
	bool ret = true;
	App->collisions->AddCollider({ x, y, 16, 16 }, Collider::Type::FLOWER);

	//App->render->Blit(rockTexture, x, y, NULL);
}
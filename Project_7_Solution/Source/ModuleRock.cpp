#include "ModuleRock.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"


ModuleRock::ModuleRock(bool startEnabled) : Module(startEnabled)
{

}

ModuleRock::~ModuleRock()
{

}

// Load assets
bool ModuleRock::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	rockTexture = App->textures->Load("Assets/roca.png");

	//Object colliders
	int n = 0;
	position.x = 40;
	position.y = 57;

	if (App->sceneLevel_1->IsEnabled() == true)
	{
		
	}

	if (App->sceneLevel_2->IsEnabled() == true)
	{
		
	}
	
	
	if (App->sceneLevel_3->IsEnabled() == true)
	{
		
	}

	return ret;
}

// Update: draw background
update_status ModuleRock::PostUpdate()
{
	// Draw everything --------------------------------------
	if (App->sceneLevel_1->IsEnabled() == true)
	{
		for (int i = 0; i < 32 * 6; i += 32)
		{
			for (int j = 0; j < 32 * 5; j += 32)
			{
				if ((i == 32 * 2 || i == 32 * 3) && (j == 32 * 1 || j == 32 * 2))
				{

				}
				else {
					App->render->Blit(rockTexture, position.x + i, position.y + j, NULL);
				}
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}


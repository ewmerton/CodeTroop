#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "Enemy.h"
#include "Enemy_Robot.h"
#include "Enemy_Robot2.h"
#include "Enemy_Snail.h"
#include "Enemy_Banana.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	enemyTexture = App->textures->Load("Assets/enemies.png");

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != ENEMY_TYPE::NO_TYPE)
		{
			LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

			SpawnEnemy(spawnQueue[i]);
			spawnQueue[i].type = ENEMY_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
		}
	}

	return true;
}

update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->Update();

			if (enemies[i]->isDead)
			{
				if (enemies[i]->cooldown >= 100)
				{
					delete enemies[i];
					enemies[i] = nullptr;
				}
				else
				{
					enemies[i]->cooldown++;
				}
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPE type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == ENEMY_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case ENEMY_TYPE::ROBOT:
					enemies[i] = new Enemy_Robot(info.x, info.y);
					break;
				case ENEMY_TYPE::ROBOT2:
					enemies[i] = new Enemy_Robot2(info.x, info.y);
					break;
				case ENEMY_TYPE::SNAIL:
					enemies[i] = new Enemy_Snail(info.x, info.y);
					break;
				case ENEMY_TYPE::BANANA:
					enemies[i] = new Enemy_Banana(info.x, info.y);
					break;
			}
			enemies[i]->texture = enemyTexture;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			switch (c2->type)
			{
			case Collider::Type::PLAYER_SHOT:
				if (enemies[i]->isDead == false && enemies[i]->type != EnemyType::BANANA)
				{
					switch (enemies[i]->type)
					{
					case EnemyType::ROBOT:
						App->player->score += 400;
						break;
					case EnemyType::SNAIL:
						App->player->score += 300;
						break;
					default:
						break;
					}
					enemies[i]->isDead = true;
				}
				break;
			default:
				break;
			}
			break;
		}
	}
}
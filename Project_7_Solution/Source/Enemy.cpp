#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
	{
		collider->pendingToDelete = true;
	}
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
	{
		if (type == EnemyType::BANANA)
		{
			collider->SetPos(position.x + 30, position.y + 60);
		}
		else if (type == EnemyType::GAS)
		{
			collider->SetPos(position.x + 5, position.y + 11);
		}
		else
		{
			collider->SetPos(position.x + 3, position.y + 16);
		}
	}
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	
}
#include "Enemy_Snail.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Snail::Enemy_Snail(int x, int y) : Enemy(x, y)
{
	// Idle
	walkIdle.PushBack({ 0, 37, 22, 28 });

	// walk Up
	walkUP.PushBack({ 0, 0, 22, 32 });
	walkUP.PushBack({ 32, 0, 22, 32 });
	walkUP.PushBack({ 64, 0, 22, 32 });
	walkUP.speed = 0.02f;

	// walk Down
	walkDOWN.PushBack({ 0, 37, 22, 28 });
	walkDOWN.PushBack({ 32, 37, 22, 28 });
	walkDOWN.PushBack({ 64, 37, 22, 28 });
	walkDOWN.speed = 0.02f;

	// walk Left
	walkLEFT.PushBack({ 94, 0, 27, 30 });
	walkLEFT.PushBack({ 126, 0, 28, 30 });
	walkLEFT.PushBack({ 159, 0, 26, 30 });
	walkLEFT.speed = 0.02f;

	// walk Right
	walkRIGHT.PushBack({ 94, 41, 27, 30 });
	walkRIGHT.PushBack({ 125, 41, 28, 30 });
	walkRIGHT.PushBack({ 158, 41, 26, 30 });
	walkRIGHT.speed = 0.02f;

	// dead Animation
	dead.PushBack({ 0, 72, 22, 28 });
	dead.PushBack({ 32, 72, 22, 28 });
	dead.speed = 0.02f;

	currentAnim = &walkIdle;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ 0.0f, -0.2f },80 * 6, &walkUP);
	path.PushBack({ 0.0f, 0.0f }, 80, &walkIdle);
	path.PushBack({ -0.2f, 0.0f }, 80 * 4, &walkLEFT);
	path.PushBack({ 0.0f, 0.2f }, 80 * 2, &walkDOWN);
	path.PushBack({ 0.0f, 0.0f }, 80, &walkIdle);
	path.PushBack({ 0.2f, 0.0f }, 80 * 6, &walkRIGHT);
	path.PushBack({ 0.0f, -0.2f }, 80 * 2, &walkUP);
	path.PushBack({ -0.2f, 0.0f }, 80 * 2, &walkLEFT);
	path.PushBack({ 0.0f, 0.2f }, 80 * 4, &walkDOWN);
	path.PushBack({ 0.0f, 0.0f }, 80, &walkIdle);
	path.PushBack({ -0.2f, 0.0f }, 80 * 2, &walkLEFT);
	path.PushBack({ 0.0f, 0.0f }, 80, &walkIdle);
	path.PushBack({ 0.0f, 0.2f }, 80 * 4, &walkDOWN);
	path.PushBack({ 0.0f, -0.2f }, 80 * 2, &walkUP);
	path.PushBack({ 0.0f, 0.0f }, 80, &walkIdle);
	path.PushBack({ 0.2f, 0.0f }, 80 * 2, &walkRIGHT);
	

	collider = App->collisions->AddCollider({ 0, 0, 19, 19 }, Collider::Type::ENEMY, (Module*)App->enemies);

	type = EnemyType::SNAIL;
}

void Enemy_Snail::Update()
{
	if (isDead)
	{
		currentAnim = &dead;
	}
	else
	{
		path.Update();
		position = spawnPos + path.GetRelativePosition();
		currentAnim = path.GetCurrentAnimation();
	}

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
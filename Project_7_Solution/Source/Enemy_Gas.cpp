#include "Enemy_Gas.h"

#include "Application.h"
#include "ModuleCollisions.h"

#include <stdlib.h>
#include <time.h>

Enemy_Gas::Enemy_Gas(int x, int y) : Enemy(x, y)
{
	// Idle
	idle.PushBack({ 0, 133, 23, 32 });
	idle.PushBack({ 0, 133, 23, 32 });

	// dead Animation
	dead.PushBack({ 126, 135, 23, 30 });

	currentAnim = &idle;

	srand(time(NULL));
	int n = rand() % 2;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	if (n == 0)
	{
		path.PushBack({ -0.2f, 0.0f }, 80 * 7, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 1, &idle);
		
		path.PushBack({ 0.0f, -0.2f }, 80 * 4, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 6, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 4, &idle);
		path.PushBack({ -0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 3, &idle);
		path.PushBack({ -0.2f, 0.0f }, 80 * 1, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 4, &idle);
		path.PushBack({ -0.2f, 0.0f }, 80 * 6, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 4, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 1, &idle);
	}
	else
	{
		path.PushBack({ 0.0f, 0.2f }, 80 * 1, &idle);
		path.PushBack({ -0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 4, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 12, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 2, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 3, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 1, &idle);
		path.PushBack({ -0.2f, 0.0f }, 80 * 12, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 4, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 1, &idle);
	}

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);

	type = EnemyType::ROBOT;
}

void Enemy_Gas::Update()
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
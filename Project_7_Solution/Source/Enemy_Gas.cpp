#include "Enemy_Gas.h"

#include "Application.h"
#include "ModuleCollisions.h"

#include <stdlib.h>
#include <time.h>

Enemy_Gas::Enemy_Gas(int x, int y) : Enemy(x, y)
{
	// Idle
	idle.PushBack({ 212, 0, 26, 27 });
	idle.PushBack({ 245, 0, 26, 27 });
	idle.speed = 0.125f;

	// dead Animation
	dead.PushBack({ 278, 0, 26, 27 });
	dead.PushBack({ 311, 0, 26, 27 });
	dead.speed = 0.02f;

	currentAnim = &idle;

	srand(time(NULL));
	int n = rand() % 2;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	if (n == 0)
	{
		path.PushBack({ -0.2f, 0.0f }, 80 * 7, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 2, &idle);
		path.PushBack({ -0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 3, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 1, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 4, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 2, &idle);
		path.PushBack({ -0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 2, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 5, &idle);
	}
	else
	{
		path.PushBack({ -0.2f, 0.0f }, 80 * 5, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 4, &idle);
		path.PushBack({ -0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 2, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 6, &idle);
		path.PushBack({ 0.2f, 0.f }, 80 * 2, &idle);
		path.PushBack({ 0.0f, -0.2f }, 80 * 3, &idle);
		path.PushBack({ 0.0f, 0.2f }, 80 * 1, &idle);
		path.PushBack({ 0.2f, 0.0f }, 80 * 3, &idle);
	}

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);

	type = EnemyType::GAS;
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
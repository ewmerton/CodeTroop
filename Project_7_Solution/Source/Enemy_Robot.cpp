#include "Enemy_Robot.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Robot::Enemy_Robot(int x, int y) : Enemy(x, y)
{
	// Idle
	walkIdle.PushBack({ 0, 135, 23, 30 });

	// walk Up
	walkUP.PushBack({ 0, 103, 23, 28 });
	walkUP.PushBack({ 32, 102, 23, 28 });
	walkUP.PushBack({ 0, 103, 23, 28 });
	walkUP.PushBack({ 96, 102, 23, 28 });
	walkUP.speed = 0.05f;

	// walk Down
	walkDOWN.PushBack({ 0, 135, 23, 30 });
	walkDOWN.PushBack({ 32, 134, 23, 30 });
	walkDOWN.PushBack({ 0, 135, 23, 30 });
	walkDOWN.PushBack({ 96, 134, 23, 30 });
	walkDOWN.speed = 0.05f;

	// walk Left
	walkLEFT.PushBack({ 0, 169, 24, 28 });
	walkLEFT.PushBack({ 32, 168, 24, 28 });
	walkLEFT.PushBack({ 64, 168, 24, 28 });
	walkLEFT.speed = 0.05f;

	// walk Right
	walkRIGHT.PushBack({ 97, 170, 24, 28 });
	walkRIGHT.PushBack({ 129, 169, 24, 28 });
	walkRIGHT.PushBack({ 161, 169, 24, 28 });
	walkRIGHT.speed = 0.05f;

	// dead Animation
	dead.PushBack({ 126, 135, 23, 30 });

	currentAnim = &walkIdle;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ 0.4f, 0.0f }, 40*6, &walkRIGHT);
	path.PushBack({ 0.0f, 0.0f }, 40*2, &walkIdle);
	path.PushBack({ 0.0f, 0.4f }, 40*2, &walkDOWN);
	path.PushBack({ 0.0f, 0.0f }, 40*2, &walkIdle);
	path.PushBack({ -0.4f, 0.0f }, 40*6, &walkLEFT);
	path.PushBack({ 0.0f, 0.0f }, 40*2, &walkIdle);
	path.PushBack({ 0.0f, -0.4f }, 40*2, &walkUP);
	path.PushBack({ 0.0f, 0.0f }, 40*2, &walkIdle);

	collider = App->collisions->AddCollider({ 0, 0, 19, 19 }, Collider::Type::ENEMY, (Module*)App->enemies);

	type = EnemyType::ROBOT;
}

void Enemy_Robot::Update()
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
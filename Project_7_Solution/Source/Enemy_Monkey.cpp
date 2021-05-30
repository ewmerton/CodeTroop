#include "Enemy_Monkey.h"

#include "Application.h"
#include "ModuleCollisions.h"

#include <stdlib.h>
#include <time.h>

Enemy_Monkey::Enemy_Monkey(int x, int y) : Enemy(x, y)
{
	// Idle
	walkIdle.PushBack({ 0, 133, 23, 32 });

	// walk Up
	walkUP.PushBack({ 2, 369, 76, 89 });
	walkUP.PushBack({ 65, 369, 76, 89 });
	walkUP.PushBack({ 133, 369, 76, 89 });
	walkUP.PushBack({ 197, 369, 76, 89 });
	walkUP.PushBack({ 264, 369, 76, 89 });
	walkUP.PushBack({ 344, 369, 76, 89 });
	walkUP.PushBack({ 421, 349, 76, 89 });
	walkUP.speed = 0.05f;

	// walk Down
	walkDOWN.PushBack({ 4, 201, 76, 89 });
	walkDOWN.PushBack({ 88, 201, 76, 89 });
	walkDOWN.PushBack({ 180, 201, 76, 89 });
	walkDOWN.PushBack({ 265, 201, 76, 89 });

	walkDOWN.PushBack({ 194, 5, 76, 89 });
	walkDOWN.PushBack({ 274, 5, 76, 89 });
	walkDOWN.PushBack({ 358, 5, 76, 89 });
	walkDOWN.PushBack({ 436, 5, 76, 89 });
	walkDOWN.speed = 0.05f;

	// walk Left
	walkLEFT.PushBack({ 7, 285, 76, 89 });
	walkLEFT.PushBack({ 89, 285, 76, 89 });
	walkLEFT.PushBack({ 178, 285, 76, 89 });
	walkLEFT.PushBack({ 264, 285, 76, 89 });

	walkLEFT.PushBack({ 195, 97, 76, 89 });
	walkLEFT.PushBack({ 273, 97, 76, 89 });
	walkLEFT.PushBack({ 358, 97, 76, 89 });
	walkLEFT.PushBack({ 436, 97, 76, 89 });
	walkLEFT.speed = 0.05f;

	// walk Right
	walkRIGHT.PushBack({ 97, 170, 24, 28 });
	walkRIGHT.PushBack({ 129, 169, 24, 28 });
	walkRIGHT.PushBack({ 161, 169, 24, 28 });
	walkRIGHT.speed = 0.05f;

	// dead Animation
	dead.PushBack({ 5, 446, 76, 89 });
	dead.PushBack({ 82, 446, 76, 89 });
	dead.PushBack({ 161, 446, 76, 89 });
	dead.PushBack({ 240, 446, 76, 89 });
	dead.PushBack({ 318, 446, 76, 89 });
	dead.PushBack({ 400, 446, 76, 89 });

	dead.PushBack({ 3, 538, 76, 89 });
	dead.PushBack({ 82, 538, 76, 89 });
	dead.PushBack({ 161, 538, 76, 89 });
	dead.PushBack({ 241, 538, 76, 89 });
	dead.PushBack({ 320, 538, 76, 89 });
	dead.PushBack({ 399, 538, 76, 89 });

	dead.PushBack({ 4, 630, 76, 89 });
	dead.PushBack({ 82, 630, 76, 89 });
	dead.PushBack({ 161, 630, 76, 89 });
	dead.PushBack({ 239, 630, 76, 89 });
	dead.PushBack({ 319, 630, 76, 89 });
	dead.PushBack({ 396, 630, 76, 89 });

	dead.PushBack({ 4, 720, 76, 89 });
	dead.PushBack({ 83, 720, 76, 89 });
	dead.PushBack({ 163, 720, 76, 89 });
	dead.PushBack({ 242, 720, 76, 89 });

	currentAnim = &walkIdle;

	srand(time(NULL));
	int n = rand() % 2;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	if (n == 0)
	{
		path.PushBack({ 0.0f, 0.2f }, 80 * 1, &walkDOWN);
		path.PushBack({ -0.2f, 0.0f }, 80 * 2, &walkLEFT);
		path.PushBack({ 0.0f, -0.2f }, 80 * 4, &walkUP);
		path.PushBack({ 0.2f, 0.0f }, 80 * 6, &walkRIGHT);
		path.PushBack({ 0.0f, 0.2f }, 80 * 4, &walkDOWN);
		path.PushBack({ -0.2f, 0.0f }, 80 * 2, &walkLEFT);
		path.PushBack({ 0.2f, 0.0f }, 80 * 3, &walkRIGHT);
		path.PushBack({ -0.2f, 0.0f }, 80 * 1, &walkLEFT);
		path.PushBack({ 0.0f, -0.2f }, 80 * 4, &walkUP);
		path.PushBack({ -0.2f, 0.0f }, 80 * 6, &walkLEFT);
		path.PushBack({ 0.0f, 0.2f }, 80 * 4, &walkDOWN);
		path.PushBack({ 0.2f, 0.0f }, 80 * 2, &walkRIGHT);
		path.PushBack({ 0.0f, -0.2f }, 80 * 1, &walkUP);
	}
	else
	{
		path.PushBack({ 0.0f, 0.2f }, 80 * 1, &walkDOWN);
		path.PushBack({ -0.2f, 0.0f }, 80 * 2, &walkLEFT);
		path.PushBack({ 0.0f, -0.2f }, 80 * 4, &walkUP);
		path.PushBack({ 0.2f, 0.0f }, 80 * 12, &walkRIGHT);
		path.PushBack({ 0.0f, 0.2f }, 80 * 2, &walkDOWN);
		path.PushBack({ 0.0f, -0.2f }, 80 * 3, &walkUP);
		path.PushBack({ 0.0f, 0.2f }, 80 * 1, &walkDOWN);
		path.PushBack({ -0.2f, 0.0f }, 80 * 12, &walkLEFT);
		path.PushBack({ 0.0f, 0.2f }, 80 * 4, &walkDOWN);
		path.PushBack({ 0.2f, 0.0f }, 80 * 2, &walkRIGHT);
		path.PushBack({ 0.0f, -0.2f }, 80 * 1, &walkUP);
	}


	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);


	type = EnemyType::MONKEY;
}

void Enemy_Monkey::Update()
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
#include "Enemy_Banana.h"

#include "Application.h"
#include "ModuleCollisions.h"

#include <stdlib.h>
#include <time.h>

Enemy_Banana::Enemy_Banana(int x, int y) : Enemy(x, y)
{
	// Idle
	walkIdle.PushBack({ 0, 133, 23, 32 });

	// walk Up
	walkUP.PushBack({ 2, 349, 76, 89 });
	walkUP.PushBack({ 65, 349, 76, 89 });
	walkUP.PushBack({ 133, 349, 76, 89 });
	walkUP.PushBack({ 197, 349, 76, 89});
	walkUP.PushBack({ 264, 349, 76, 89 });
	walkUP.PushBack({ 344, 349, 76, 89});
	walkUP.PushBack({ 421, 349, 76, 89 });
	walkUP.speed = 0.05f;

	// walk Down
	walkDOWN.PushBack({ 7, 248, 76, 89 });
	walkDOWN.PushBack({ 89, 248, 76, 89 });
	walkDOWN.PushBack({ 179, 248, 76, 89 });
	walkDOWN.PushBack({ 265, 248, 76, 89 });
	walkDOWN.PushBack({ 361, 248, 76, 89 });
	walkDOWN.PushBack({ 443, 248, 76, 89 });
	walkDOWN.PushBack({ 527, 248, 76, 89 });
	walkDOWN.PushBack({ 606, 248, 76, 89 });
	walkDOWN.speed = 0.05f;

	// walk Left
	walkLEFT.PushBack({ 12, 902, 76, 89 });
	walkLEFT.PushBack({ 95, 902, 76, 89 });
	walkLEFT.PushBack({ 186, 902, 76, 89 });
	walkLEFT.PushBack({ 270, 902, 76, 89 });
	walkLEFT.PushBack({ 347, 902, 76, 89 });
	walkLEFT.PushBack({ 428, 902, 76, 89 });
	walkLEFT.PushBack({ 514, 902, 76, 89 });
	walkLEFT.PushBack({ 593, 902, 76, 89 });
	walkLEFT.speed = 0.05f;

	// walk Right
	walkRIGHT.PushBack({ 17, 814, 24, 28 });
	walkRIGHT.PushBack({ 97, 814, 24, 28 });
	walkRIGHT.PushBack({ 180, 814, 24, 28 });
	walkRIGHT.PushBack({ 261, 814, 24, 28 });
	walkRIGHT.PushBack({ 341, 814, 24, 28 });
	walkRIGHT.PushBack({ 427, 814, 24, 28 });
	walkRIGHT.PushBack({ 515, 814, 24, 28 });
	walkRIGHT.PushBack({ 601, 814, 24, 28 });
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


	type = EnemyType::BANANA;
}

void Enemy_Banana::Update()
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
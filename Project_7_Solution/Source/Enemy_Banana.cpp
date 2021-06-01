#include "Enemy_Banana.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleMonkey.h"

Enemy_Banana::Enemy_Banana(int x, int y) : Enemy(x, y)
{
	// Idle
	walkIdle.PushBack({ 179, 248, 76, 89 });

	// walk Up
	walkUP.PushBack({ 0, 349, 76, 89 });
	walkUP.PushBack({ 65, 349, 76, 89 });
	walkUP.PushBack({ 135, 349, 76, 89 });
	walkUP.PushBack({ 199, 349, 76, 89});
	walkUP.PushBack({ 266, 349, 76, 89 });
	walkUP.PushBack({ 343, 349, 76, 89});
	walkUP.PushBack({ 421, 349, 76, 89 });
	walkUP.speed = 0.05f;

	// walk Down
	walkDOWN.PushBack({ 6, 248, 76, 89 });
	walkDOWN.PushBack({ 90, 248, 76, 89 });
	walkDOWN.PushBack({ 179, 248, 76, 89 });
	walkDOWN.PushBack({ 265, 248, 76, 89 });
	walkDOWN.PushBack({ 342, 248, 76, 89 });
	walkDOWN.PushBack({ 424, 248, 76, 89 });
	walkDOWN.PushBack({ 509, 248, 76, 89 });
	walkDOWN.PushBack({ 591, 248, 76, 89 });
	walkDOWN.speed = 0.05f;

	// walk Left
	walkLEFT.PushBack({ 11, 902, 76, 89 });
	walkLEFT.PushBack({ 94, 902, 76, 89 });
	walkLEFT.PushBack({ 183, 902, 76, 89 });
	walkLEFT.PushBack({ 271, 902, 76, 89 });
	walkLEFT.PushBack({ 358, 902, 76, 89 });
	walkLEFT.PushBack({ 428, 902, 76, 89 });
	walkLEFT.PushBack({ 514, 902, 76, 89 });
	walkLEFT.PushBack({ 593, 902, 76, 89 });
	walkLEFT.speed = 0.05f;

	// walk Right
	walkRIGHT.PushBack({ 15, 814, 76, 89 });
	walkRIGHT.PushBack({ 95, 814, 76, 89 });
	walkRIGHT.PushBack({ 179, 814, 76, 89 });
	walkRIGHT.PushBack({ 258, 814, 76, 89 });
	walkRIGHT.PushBack({ 345, 814, 76, 89 });
	walkRIGHT.PushBack({ 440, 814, 76, 89 });
	walkRIGHT.PushBack({ 525, 814, 76, 89 });
	walkRIGHT.PushBack({ 605, 814, 76, 89 });
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
	dead.speed = 0.07f;
	currentAnim = &walkIdle;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	
	path.PushBack({ 0.0f, 0.4f }, 80 * 0.5, &walkDOWN); //Down
	path.PushBack({ -0.4f, 0.0f }, 80 * 3, &walkLEFT); //Left
	path.PushBack({ 0.0f, 0.4f }, 80 * 2, &walkDOWN); //Down
	path.PushBack({ 0.0f, -0.4f }, 80 * 1, &walkUP); //Up
	path.PushBack({ 0.4f, 0.0f }, 80 * 6, &walkRIGHT); //Right
	path.PushBack({ 0.0f, -0.4f }, 80 * 2, &walkUP); //Up
	path.PushBack({ -0.4f, 0.0f }, 80 * 4, &walkLEFT); //Left
	path.PushBack({ 0.4f, 0.0f }, 80 * 3, &walkRIGHT); //Right
	path.PushBack({ 0.0f, 0.4f }, 80 * 5, &walkDOWN); //Down
	path.PushBack({ -0.4f, 0.0f }, 80 * 5, &walkLEFT); //Left
	path.PushBack({ 0.0f, -0.4f }, 80 * 1, &walkUP); //Up
	path.PushBack({ 0.4f, 0.0f }, 80 * 2, &walkRIGHT); //Right
	path.PushBack({ 0.0f, -0.4f }, 80 * 1, &walkUP); //Up
	path.PushBack({ 0.4f, 0.0f }, 80 * 2, &walkRIGHT); //Right
	path.PushBack({ 0.0f, -0.4f }, 80 * 1, &walkUP); //Up
	path.PushBack({ -0.4f, 0.0f }, 80 * 4, &walkLEFT); //Left
	path.PushBack({ 0.0f, -0.4f }, 80 * 2, &walkUP); //Up
	path.PushBack({ 0.4f, 0.0f }, 80 * 3, &walkRIGHT); //Right
	path.PushBack({ 0.0f, 0.4f }, 80 * 0.5, &walkDOWN); //Down

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ENEMY, (Module*)App->enemies);

	type = EnemyType::BANANA;
}

void Enemy_Banana::Update()
{
	if (!App->monkey->isAlive())
	{
		isDead = true;
	}

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
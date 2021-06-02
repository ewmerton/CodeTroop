#include "Bomb.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

ModuleBomb::ModuleBomb(bool startEnabled) : Module(startEnabled)
{

}

ModuleBomb::~ModuleBomb()
{

}

bool ModuleBomb::Start()
{
	bool ret = true;

	position.x = 0;
	position.y = 0;
	
	continueUp = true;
	continueDown = true;
	continueLeft = true;
	continueRight = true;
	continueUpX = true;
	continueDownX = true;
	continueLeftX = true;
	continueRightX = true;
	placed = false;

	collider = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::ROCK, this);
	cUp = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	cDown = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	cLeft = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	cRight = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	cUpX = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	cDownX = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	cLeftX = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	cRightX = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	extraUp = App->collisions->AddCollider({ 100, 0, 16, 16 }, Collider::Type::PLAYER_SHOT);
	extraDown = App->collisions->AddCollider({ 100, 0, 16, 16 }, Collider::Type::PLAYER_SHOT);
	extraLeft = App->collisions->AddCollider({ 100, 0, 16, 16 }, Collider::Type::PLAYER_SHOT);
	extraRight = App->collisions->AddCollider({ 100, 0, 16, 16 }, Collider::Type::PLAYER_SHOT);

	placeBomb = App->audio->LoadFx("Assets/PutBombSound.wav");
	explote = App->audio->LoadFx("Assets/ExplosionSound.wav");

	return ret;
}

update_status ModuleBomb::PreUpdate()
{
	continueUp = true;
	continueDown = true;
	continueLeft = true;
	continueRight = true;
	continueUpX = true;
	continueDownX = true;
	continueLeftX = true;
	continueRightX = true;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBomb::Update()
{
	if (Cooldown)
	{
		count++;
	}

	cUp->SetPos(position.x, position.y - 16);
	cDown->SetPos(position.x, position.y + 16);
	cLeft->SetPos(position.x - 16, position.y);
	cRight->SetPos(position.x + 16, position.y);
	cUpX->SetPos(position.x, position.y - 32);
	cDownX->SetPos(position.x, position.y + 32);
	cLeftX->SetPos(position.x - 32, position.y);
	cRightX->SetPos(position.x + 32, position.y);

	extraUp->SetPos(100, 0);
	extraDown->SetPos(100, 0);
	extraLeft->SetPos(100, 0);
	extraRight->SetPos(100, 0);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleBomb::PostUpdate()
{
	if (count >= 300)
	{
		BombExplosion(position);
		collider->SetPos(0, 0);
		Cooldown = false;
		count = 0;
		a_bombs++;
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleBomb::OnCollision(Collider* c1, Collider* c2)
{
	// first round
	if (c1 == cUp && placed)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			continueUp = false; break;

		case Collider::Type::ROCK:
			continueUp = false; break;

		case Collider::Type::FLOWER:
			continueUp = false; break;
		default:
			break;
		}
	}

	if (c1 == cDown && placed)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			continueDown = false; break;

		case Collider::Type::ROCK:
			continueDown = false; break;

		case Collider::Type::FLOWER:
			continueDown = false; break;
		default:
			break;
		}
	}

	if (c1 == cLeft && placed)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			continueLeft = false; break;

		case Collider::Type::ROCK:
			continueLeft = false; break;

		case Collider::Type::FLOWER:
			continueLeft = false; break;
		default:
			break;
		}
	}

	if (c1 == cRight && placed)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			continueRight = false; break;

		case Collider::Type::ROCK:
			continueRight = false; break;

		case Collider::Type::FLOWER:
			continueRight = false; break;
		default:
			break;
		}
	}

	// second round
	if (c1 == cUpX && placed)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			continueUpX = false; break;

		case Collider::Type::ROCK:
			continueUpX = false; break;

		case Collider::Type::FLOWER:
			continueUpX = false; break;
		default:
			break;
		}
	}

	if (c1 == cDownX && placed)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			continueDownX = false; break;

		case Collider::Type::ROCK:
			continueDownX = false; break;

		case Collider::Type::FLOWER:
			continueDownX = false; break;
		default:
			break;
		}
	}

	if (c1 == cLeftX && placed)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			continueLeftX = false; break;

		case Collider::Type::ROCK:
			continueLeftX = false; break;

		case Collider::Type::FLOWER:
			continueLeftX = false; break;
		default:
			break;
		}
	}

	if (c1 == cRight && placed)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			continueRightX = false; break;

		case Collider::Type::ROCK:
			continueRightX = false; break;

		case Collider::Type::FLOWER:
			continueRightX = false; break;
		default:
			break;
		}
	}
}

void ModuleBomb::PlaceBomb(iPoint p)
{
	if (!Cooldown && a_bombs > 0)
	{
		SpawnBomb(p);
		position.x = p.x;
		position.y = p.y;
		Cooldown = true;
		placed = true;
		a_bombs--;
	}
}

void ModuleBomb::SpawnBomb(iPoint p)
{
	App->audio->PlayFx(placeBomb);
	App->particles->AddParticle(App->particles->bomb, p.x, p.y, Collider::Type::NONE, 0);
	collider->SetPos(p.x, p.y);
}

void ModuleBomb::BombExplosion(iPoint p)
{
	App->audio->PlayFx(explote);
	// Center
	App->particles->AddParticle(App->particles->explosionCenter, p.x, p.y, Collider::Type::PLAYER_SHOT, 0);

	if (continueUp)
	{
		// Down
		App->particles->AddParticle(App->particles->exV, p.x, p.y - 16, Collider::Type::PLAYER_SHOT, 0);
		if (continueUpX)
		{
			App->particles->AddParticle(App->particles->exUp, p.x, p.y - 32, Collider::Type::PLAYER_SHOT, 0);
		}
		else
		{
			extraUp->SetPos(p.x, p.y - 32);
		}
	}
	else
	{
		extraUp->SetPos(p.x, p.y - 16);
	}

	if (continueDown)
	{
		// Down
		App->particles->AddParticle(App->particles->exV, p.x, p.y + 16, Collider::Type::PLAYER_SHOT, 0);
		if (continueDownX)
		{
			App->particles->AddParticle(App->particles->exDown, p.x, p.y + 32, Collider::Type::PLAYER_SHOT, 0);
		}
		else
		{
			extraDown->SetPos(p.x, p.y + 32);
		}
	}
	else
	{
		extraDown->SetPos(p.x, p.y + 16);
	}

	if (continueLeft)
	{
		// Left
		App->particles->AddParticle(App->particles->exH, p.x - 16, p.y, Collider::Type::PLAYER_SHOT, 0);
		if (continueLeftX)
		{
			App->particles->AddParticle(App->particles->exLeft, p.x - 32, p.y, Collider::Type::PLAYER_SHOT, 0);
		}
		else
		{
			extraLeft->SetPos(p.x - 32, p.y);
		}
	}
	else
	{
		extraLeft->SetPos(p.x - 16, p.y);
	}

	if (continueRight)
	{
		// Right
		App->particles->AddParticle(App->particles->exH, p.x + 16, p.y, Collider::Type::PLAYER_SHOT, 0);
		if (continueRightX)
		{
			App->particles->AddParticle(App->particles->exRight, p.x + 32, p.y, Collider::Type::PLAYER_SHOT, 0);
		}
		else
		{
			extraRight->SetPos(p.x + 32, p.y);
		}
	}
	else
	{
		extraRight->SetPos(p.x + 16, p.y);
	}

	placed = false;
}
#include "Bomb.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
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

	placeBomb = App->audio->LoadFx("Assets/PutBombSound.wav");
	explote = App->audio->LoadFx("Assets/ExplosionSound.wav");

	n = 0;

	return ret;
}

update_status ModuleBomb::Update()
{
	for (int i = 0; i < n_bombs; i++)
	{
		if (bombs[i].Cooldown)
		{
			bombs[i].count++;
		}

		if (bombs[i].count >= 300)
		{
			BombExplosion(bombs[i].aP);
			bombs[i].collider->pendingToDelete = true;
			bombs[i].Cooldown = false;
			bombs[i].count = 0;
			a_bombs++;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleBomb::NewBomb()
{
	if (n_bombs < MAX_BOMBS)
	{
		n_bombs++;
		a_bombs++;
	}
}

void ModuleBomb::PlaceBomb(iPoint p)
{
	p.y += 7;

	for (int i = 0; i < MAX_BOMBS; i++)
	{
		if (!bombs[i].Cooldown && a_bombs > 0)
		{
			SpawnBomb(p, i);
			bombs[i].aP = SavePosition(p, i);
			bombs[i].Cooldown = true;
			a_bombs--;
			break;
		}
		else if (n_bombs - 1 > n)
		{
			n++;
		}
	}
}

void ModuleBomb::SpawnBomb(iPoint p, int i)
{
	App->particles->AddParticle(App->particles->bomb, p.x, p.y, Collider::Type::NONE, 0);
	bombs[i].collider = App->collisions->AddCollider({ p.x, p.y, 16, 16 }, Collider::Type::ROCK);
}

iPoint ModuleBomb::SavePosition(iPoint p, int n)
{
	bombs[n].position.x = p.x;
	bombs[n].position.y = p.y;

	return bombs[n].position;
}

void ModuleBomb::BombExplosion(iPoint p)
{
	App->audio->PlayFx(explote);
	// Center
	App->particles->AddParticle(App->particles->explosionCenter, p.x, p.y, Collider::Type::PLAYER_SHOT, 0);
	// Up
	App->particles->AddParticle(App->particles->exV, p.x, p.y - 16, Collider::Type::PLAYER_SHOT, 0);
	App->particles->AddParticle(App->particles->exUp, p.x, p.y - 32, Collider::Type::PLAYER_SHOT, 0);
	// Down
	App->particles->AddParticle(App->particles->exV, p.x, p.y + 16, Collider::Type::PLAYER_SHOT, 0);
	App->particles->AddParticle(App->particles->exDown, p.x, p.y + 32, Collider::Type::PLAYER_SHOT, 0);
	// Left
	App->particles->AddParticle(App->particles->exH, p.x - 16, p.y, Collider::Type::PLAYER_SHOT, 0);
	App->particles->AddParticle(App->particles->exLeft, p.x - 32, p.y, Collider::Type::PLAYER_SHOT, 0);
	// Right
	App->particles->AddParticle(App->particles->exH, p.x + 16, p.y, Collider::Type::PLAYER_SHOT, 0);
	App->particles->AddParticle(App->particles->exRight, p.x + 32, p.y, Collider::Type::PLAYER_SHOT, 0);
}
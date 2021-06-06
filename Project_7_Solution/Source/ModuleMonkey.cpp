#include "ModuleMonkey.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "GetScene.h"


ModuleMonkey::ModuleMonkey(bool startEnabled) : Module(startEnabled)
{
	idleDOWN.PushBack({ 526, 0, 24, 19 });
	idleDOWN.PushBack({ 553, 0, 24, 19 });
	idleDOWN.PushBack({ 580, 0, 24, 19 });
	idleDOWN.PushBack({ 607, 0, 24, 19 });
	idleDOWN.PushBack({ 526, 22, 24, 19 });
	idleDOWN.PushBack({ 553, 22, 24, 19 });
	idleDOWN.PushBack({ 580, 22, 24, 19 });
	idleDOWN.PushBack({ 607, 22, 24, 19 });
	idleDOWN.speed = 0.05f;

	idleUP.PushBack({ 552, 91, 24, 19 });
	idleLEFT.PushBack({ 552, 117, 24, 19 });
	idleRIGHT.PushBack({ 552, 68, 24, 19 });

	// walk Up
	walkUP.PushBack({ 525, 91, 24, 19 });
	walkUP.PushBack({ 552, 91, 24, 19 });
	walkUP.speed = 0.05f;

	// walk Down
	walkDOWN.PushBack({ 525, 45, 24, 19 });
	walkDOWN.PushBack({ 552, 45, 24, 19 });
	walkDOWN.speed = 0.05f;

	// walk Left
	walkLEFT.PushBack({ 525, 117, 24, 19 });
	walkLEFT.PushBack({ 552, 117, 24, 19 });
	walkLEFT.speed = 0.05f;

	// walk Right
	walkRIGHT.PushBack({ 525, 68,  24, 19 });
	walkRIGHT.PushBack({ 552, 68, 24, 19 });
	walkRIGHT.speed = 0.05f;

	tp.PushBack({ 578, 43, 24, 19 });
	tp.PushBack({ 587, 43, 24, 19 });
	tp.speed = 0.05f;

	// Dead Animation
	deadAnim.PushBack({ 583, 68, 24, 19 });
}

ModuleMonkey::~ModuleMonkey()
{

}

bool ModuleMonkey::Start()
{
	bool ret = true;

	texture = App->textures->Load("Assets/enemies.png");

	currentAnimation = &idleDOWN;

	position.x = 118;
	position.y = 101;

	lifes = 3;
	dead = false;
	dCount = 0;
	destroyed = false;
	destroyedCountdown = 200;
	deadAnim.Reset();

	collider = App->collisions->AddCollider({ position.x + 2, position.y + 4, 16, 16 }, Collider::Type::FLOWER, this);
	b_collider[0] = App->collisions->AddCollider({ position.x + 2, position.y - 12, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	b_collider[1] = App->collisions->AddCollider({ position.x + 2, position.y + 20, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	b_collider[2] = App->collisions->AddCollider({ position.x - 14, position.y + 4, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	b_collider[3] = App->collisions->AddCollider({ position.x + 18, position.y + 4, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	b_collider[4] = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	b_collider[5] = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	b_collider[6] = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	b_collider[7] = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	colliderFace = App->collisions->AddCollider({ 0, 0, 16, 16 }, Collider::Type::PLAYER_NXT, this);

	delayUp = 15;
	delayDown = 15;
	delayLeft = 15;
	delayRight = 15;
	dUp = false;
	dDown = false;
	dLeft = false;
	dRight = false;
	u = 0;
	d = 0;
	l = 0;
	r = 0;

	delayTP = 30;
	dTP = false;

	return ret;
}

update_status ModuleMonkey::PreUpdate()
{

	return update_status::UPDATE_CONTINUE;	
}

update_status ModuleMonkey::Update()
{	
	if (dUp)
	{
		delayUp--;
		currentAnimation = &walkUP;

		if (delayUp < 0)
		{
			position.y -= 16;
			u++;
			delayUp = 15;
		}
		else if (u == 2)
		{
			dUp = false;
			delayUp = 15;
			u = 0;
			currentAnimation = &idleDOWN;
		}
	}
	if (dDown)
	{
		delayDown--;
		currentAnimation = &walkDOWN;

		if (delayDown < 0)
		{
			position.y += 16;
			d++;
			delayDown = 15;
		}
		if (d == 2)
		{
			dDown = false;
			delayDown = 15;
			d = 0;
			currentAnimation = &idleUP;
		}
	}
	if (dLeft)
	{
		delayLeft--;
		currentAnimation = &walkLEFT;

		if (delayLeft < 0)
		{
			position.x -= 16;
			l++;
			delayLeft = 15;
		}
		if (l == 2)
		{
			dLeft = false;
			delayLeft = 15;
			l = 0;
			currentAnimation = &idleRIGHT;
		}
	}
	if (dRight)
	{
		delayRight--;
		currentAnimation = &walkRIGHT;

		if (delayRight < 0)
		{
			position.x += 16;
			r++;
			delayRight = 15;
		}
		if (r == 2)
		{
			dRight = false;
			delayRight = 15;
			r = 0;
			currentAnimation = &idleLEFT;
		}
	}
	if (dTP)
	{
		delayTP--;
		currentAnimation = &tp;

		if (delayTP < 0)
		{
			position = { 118, 101 };

			if (delayTP < -15)
			{
				dTP = false;
				delayTP = 15;

				if (App->player->GetPlayerPos().x > position.x)
				{
					currentAnimation = &idleRIGHT;
				}
				else if (App->player->GetPlayerPos().x < position.x)
				{
					currentAnimation = &idleLEFT;
				}
				else if (App->player->GetPlayerPos().y > position.y)
				{
					currentAnimation = &idleDOWN;
				}
				else if (App->player->GetPlayerPos().y < position.y)
				{
					currentAnimation = &idleUP;
				}
			}
		}
	}

	collider->SetPos(position.x + 2, position.y + 4);
	b_collider[0]->SetPos(position.x + 2, position.y - 12);
	b_collider[1]->SetPos(position.x + 2, position.y + 20);
	b_collider[2]->SetPos(position.x - 14, position.y + 4);
	b_collider[3]->SetPos(position.x + 18, position.y + 4);

	if (currentAnimation == &idleUP)
	{
		b_collider[4]->SetPos(position.x + 2, position.y - 28);
		b_collider[5]->SetPos(0, 0);
		b_collider[6]->SetPos(position.x - 30, position.y + 4);
		b_collider[7]->SetPos(position.x + 34, position.y + 4);
		colliderFace->SetPos(position.x + 2, position.y - 44);
	}
	else if (currentAnimation == &idleDOWN)
	{
		b_collider[4]->SetPos(0, 0);
		b_collider[5]->SetPos(position.x + 2, position.y + 36);
		b_collider[6]->SetPos(position.x - 30, position.y + 4);
		b_collider[7]->SetPos(position.x + 34, position.y + 4);
		colliderFace->SetPos(position.x + 2, position.y + 52);
	}
	else if (currentAnimation == &idleLEFT)
	{
		b_collider[4]->SetPos(position.x + 2, position.y - 28);
		b_collider[5]->SetPos(position.x + 2, position.y + 36);
		b_collider[6]->SetPos(position.x - 30, position.y + 4);
		b_collider[7]->SetPos(0, 0);
		colliderFace->SetPos(position.x - 46, position.y + 4);
	}
	else if (currentAnimation == &idleRIGHT)
	{
		b_collider[4]->SetPos(position.x + 2, position.y - 28);
		b_collider[5]->SetPos(position.x + 2, position.y + 36);
		b_collider[6]->SetPos(0, 0);
		b_collider[7]->SetPos(position.x + 34, position.y + 4);
		colliderFace->SetPos(position.x + 50, position.y + 4);
	}
	
	currentAnimation->Update();

	if (dead)
	{
		dCount++;
		if (dCount >= 115)
		{
			destroyed = true;
		}
		if (destroyed)
		{
			destroyedCountdown--;
			if (destroyedCountdown <= 0)
			{
				App->fade->FadeToBlack(App->getScene->GetActualScene(), (Module*)App->sceneIntro, 60);
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleMonkey::PostUpdate()
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	App->render->Blit(texture, position.x, position.y, &rect);
	
	return update_status::UPDATE_CONTINUE;
}

void ModuleMonkey::OnCollision(Collider * c1, Collider * c2)
{
	if (c1 == collider && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER_SHOT:
			if (lifes > 1)
			{
				lifes--;
				dTP = true;
			}
			else
			{
				currentAnimation = &deadAnim;
				dead = true;
			} break;

		default:
			break;
		}
	}

	if (c1 == b_collider[0] && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			dDown = true;
			break;
		case Collider::Type::WALL:
			dDown = false;
			dTP = true;
			break;

		default:
			break;
		}
	}

	if (c1 == b_collider[1] && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			dUp = true;
			break;
		case Collider::Type::WALL:
			dUp = false;
			dTP = true;
			break;

		default:
			break;
		}
	}

	if (c1 == b_collider[2] && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			dRight = true;
			break;
		case Collider::Type::WALL:
			dRight = false;
			dTP = true;
			break;

		default:
			break;
		}
	}

	if (c1 == b_collider[3] && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			dLeft = true;
			break;
		case Collider::Type::WALL:
			dLeft = false;
			dTP = true;
			break;

		default:
			break;
		}
	}

	if (c1 == b_collider[4] && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			dDown = true;
			break;

		default:
			break;
		}
	}

	if (c1 == b_collider[5] && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			dUp = true;
			break;

		default:
			break;
		}
	}

	if (c1 == b_collider[6] && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			dRight = true;
			break;

		default:
			break;
		}
	}

	if (c1 == b_collider[7] && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			dLeft = true;
			break;

		default:
			break;
		}
	}

	if (c1 == colliderFace && dead == false) // Normal collision
	{
		switch (c2->type)
		{
		case Collider::Type::PLAYER:
			if (currentAnimation == &idleUP)
			{
				dDown = true;
			}
			else if (currentAnimation == &idleDOWN)
			{
				dUp = true;
			}
			else if (currentAnimation == &idleLEFT)
			{
				dRight = true;
			}
			else if (currentAnimation == &idleRIGHT)
			{
				dLeft = true;
			}
			break;

		default:
			break;
		}
	}
}

bool ModuleMonkey::isAlive()
{
	return !dead;
}
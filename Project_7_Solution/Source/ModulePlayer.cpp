#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFonts.h"
#include "ModuleCT.h"
#include "ModuleFadeToBlack.h"
#include "GetScene.h"

#include <stdio.h>
#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 17, 1, 15, 22 });

	// move upwards
	upAnim.PushBack({ 49, 1, 15, 22 });
	upAnim.PushBack({ 65, 1, 15, 22 });
	upAnim.PushBack({ 80, 1, 15, 22 });
	upAnim.PushBack({ 65, 1, 15, 22 });
	upAnim.speed = 0.05f;

	// Move down
	downAnim.PushBack({ 1, 1, 14, 22 });
	downAnim.PushBack({ 17, 1, 15, 22 });
	downAnim.PushBack({ 33, 1, 15, 22 });
	downAnim.PushBack({ 17, 1, 15, 22 });
	downAnim.speed = 0.05f;

	// Move left
	leftAnim.PushBack({ 0, 25, 15, 22 });
	leftAnim.PushBack({ 16, 25, 16, 22 });
	leftAnim.PushBack({ 32, 25, 15, 22 });
	leftAnim.PushBack({ 16, 25, 16, 22 });
	leftAnim.speed = 0.05f;

	// Move right
	rightAnim.PushBack({ 48, 25, 15, 22 });
	rightAnim.PushBack({ 64, 25, 16, 22 });
	rightAnim.PushBack({ 81, 25, 15, 22 });
	rightAnim.PushBack({ 64, 25, 16, 22 });
	rightAnim.speed = 0.05f;

	// Win Pose
	winAnim.PushBack({ 129, 46, 15, 23 });

	// Dead Animation
	deadAnim.PushBack({ 4, 74, 15, 21 });
	deadAnim.PushBack({ 28, 74, 15, 21 });
	deadAnim.PushBack({ 52, 74, 15, 21 });
	deadAnim.PushBack({ 76, 74, 17, 21 });
	deadAnim.PushBack({ 102, 74, 19, 21 });
	deadAnim.PushBack({ 128, 74, 20, 21 });
	deadAnim.speed = 0.05f;
	deadAnim.loop = false;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Char.png");
	placeBomb = App->audio->LoadFx("Assets/PutBombSound.wav");
	explote = App->audio->LoadFx("Assets/ExplosionSound.wav");
	deadFx = App->audio->LoadFx("Assets/GameOverSound.wav");

	currentAnimation = &idleAnim;

	position.x = 24;
	position.y = 41;

	// Standard values
	lifes = 1;
	score = 0;
	stime = 0;
	mtime = 0;

	dead = false;
	dCount = 0;
	destroyed = false;
	lvlComplete = false;
	deadAnim.Reset();

	destroyedCountdown = 60;
	freeze = false;

	collider = App->collisions->AddCollider({ position.x, position.y + 7, 15, 15 }, Collider::Type::PLAYER, this);


	char lookupTable[] = { "0123456789" };
	nFont = App->fonts->Load("Assets/hud_font.png", lookupTable, 1);

	return ret;
}

update_status ModulePlayer::Update()
{
	if (lvlComplete || dead)
	{
		freeze = true;
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !freeze)
	{
		position.x -= speed;
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !freeze)
	{
		position.x += speed;
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !freeze)
	{
		position.y += speed;
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && !freeze)
	{
		position.y -= speed;
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	// Bomb system
	uint num = 0;
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && !freeze)
	{
		for (uint i = 0; i < n_bombs && a_bombs != 0; i++)
		{
			if (!isCounting[num])
			{
				SpawnBomb(num);
				break;
			}
			else
			{
				if (n_bombs - 1 > num)
				{
					num++;
				}
			}
		}
	}
	for (uint i = 0; i < n_bombs; i++)
	{
		if (isCounting[i])
		{
			count[i]++;
		}
	}
	for (uint i = 0; i < n_bombs; i++)
	{
		if (count[i] >= 300)
		{
			BombExplosion(i);
		}
	}
	// Provisional
	if (App->input->keys[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN && !freeze)
	{
		NewBomb();
	}

	// GodMode
	if (App->input->keys[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		if (!godMode)
		{
			godMode = true;
		}
		else
		{
			godMode = false;
		}
	}

	// Menu Game
	if (App->input->keys[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(App->getScene->GetActualScene(), (Module*)App->sceneIntro, 60);
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& !freeze)
		currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y + 7);

	currentAnimation->Update();

	if (App->input->keys[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
	{
		return update_status::UPDATE_STOP;
	}

	// Jump next level
	if (lvlComplete)
	{
		App->fade->FadeToBlack(App->getScene->GetActualScene(), App->getScene->GetNextScene(), 60);
	}

	// Try Again
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

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);

		sprintf_s(lifesText, 2, "%1d", lifes);
		App->fonts->BlitText(231, 9, nFont, lifesText);

		sprintf_s(scoreText, 6, "%5d", score);
		App->fonts->BlitText(160, 9, nFont, scoreText);

		/*sprintf_s(stimeText,2, "%7d", stime);
		App->fonts->BlitText(16, 9, nFont, stimeText);

		sprintf_s(mtimeText, 1, "%9d", mtime);
		App->fonts->BlitText(30, 9, nFont, mtimeText);*/
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL: 
			if (c1->rect.y < c2->rect.y) //coming from up
			{
				position.y -= speed;
			}
			else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) //coming from down
			{
				position.y += speed;
			}
			if (c1->rect.x < c2->rect.x) //coming from left
			{
				position.x -= speed;
			}
			else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) //coming from right
			{
				position.x += speed;
			}; break;

		case Collider::Type::ROCK:
			if (c1->rect.y < c2->rect.y && c1->rect.y + c1->rect.h - 2 < c2->rect.y) //coming from up
			{
				position.y -= speed;
			}
			else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) //coming from down
			{
				position.y += speed;
			}
			if (c1->rect.x < c2->rect.x && c1->rect.x + c1->rect.w - 2 < c2->rect.x) //coming from left
			{
				position.x -= speed;
			}
			else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) //coming from right
			{
				position.x += speed;
			}; break;

		case Collider::Type::FLOWER:
			if (c1->rect.y < c2->rect.y && c1->rect.y + c1->rect.h - 2 < c2->rect.y) //coming from up
			{
				position.y -= speed;
			}
			else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) //coming from down
			{
				position.y += speed;
			}
			if (c1->rect.x < c2->rect.x && c1->rect.x + c1->rect.w - 2 < c2->rect.x) //coming from left
			{
				position.x -= speed;
			}
			else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) //coming from right
			{
				position.x += speed;
			}; break;

		case Collider::Type::RED_FLOWER:
			if (c1->rect.y < c2->rect.y && c1->rect.y + c1->rect.h - 2 < c2->rect.y) //coming from up
			{
				position.y -= speed;
			}
			else if (c1->rect.y + 2 > c2->rect.y + c2->rect.h) //coming from down
			{
				position.y += speed;
			}
			if (c1->rect.x < c2->rect.x && c1->rect.x + c1->rect.w - 2 < c2->rect.x) //coming from left
			{
				position.x -= speed;
			}
			else if (c1->rect.x + 2 > c2->rect.x + c2->rect.w) //coming from right
			{
				position.x += speed;
			}; break;

		case Collider::Type::MOON:
			currentAnimation = &winAnim;
			App->tower->MoonColected();
			lvlComplete = true; break;

		case Collider::Type::ENEMY:
			if (!godMode)
			{
				LOG("enemy");
				currentAnimation = &deadAnim;
				App->audio->PlayFx(deadFx);
				dead = true;
			} break;

		case Collider::Type::PLAYER_SHOT:
			if (!godMode)
			{
				LOG("shot");
				currentAnimation = &deadAnim;
				App->audio->PlayFx(deadFx);
				dead = true;
			} break;

		default:
			break;
		}
	}
}

void ModulePlayer::SpawnBomb(int n)
{
	App->particles->AddParticle(App->particles->bomb, position.x, position.y + 6, Collider::Type::NONE, 0);
	App->audio->PlayFx(placeBomb);
	SaveBombPos(position.x, position.y, n);
	isCounting[n] = true;
	a_bombs--;
}

void ModulePlayer::BombExplosion(int n)
{
	App->audio->PlayFx(explote);
	// Center
	App->particles->AddParticle(App->particles->explosionCenter, bx[n], by[n] + 6, Collider::Type::PLAYER_SHOT, 0);
	// Up
	App->particles->AddParticle(App->particles->exV, bx[n], by[n] - 10, Collider::Type::PLAYER_SHOT, 0);
	App->particles->AddParticle(App->particles->exUp, bx[n], by[n] - 26, Collider::Type::PLAYER_SHOT, 0);
	// Down
	App->particles->AddParticle(App->particles->exV, bx[n], by[n] + 22, Collider::Type::PLAYER_SHOT, 0);
	App->particles->AddParticle(App->particles->exDown, bx[n], by[n] + 38, Collider::Type::PLAYER_SHOT, 0);
	// Left
	App->particles->AddParticle(App->particles->exH, bx[n] - 16, by[n] + 6, Collider::Type::PLAYER_SHOT, 0);
	App->particles->AddParticle(App->particles->exLeft, bx[n] - 32, by[n] + 6, Collider::Type::PLAYER_SHOT, 0);
	// Right
	App->particles->AddParticle(App->particles->exH, bx[n] + 16, by[n] + 6, Collider::Type::PLAYER_SHOT, 0);
	App->particles->AddParticle(App->particles->exRight, bx[n] + 32, by[n] + 6, Collider::Type::PLAYER_SHOT, 0);
	isCounting[n] = false;
	count[n] = 0;
	a_bombs++;
}

void ModulePlayer::SaveBombPos(int x, int y, int n)
{
	bx[n] = x;
	by[n] = y;
}

void ModulePlayer::NewBomb()
{
	if (n_bombs < MAX_BOMBS)
	{
		n_bombs++;
		a_bombs++;
	}
}
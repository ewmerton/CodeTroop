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
	deadFx = App->audio->LoadFx("Assets/GameOverSound.wav");

	currentAnimation = &idleAnim;

	position.x = 24;
	position.y = 66;

	freezeUp = false;
	freezeDown = false;
	freezeLeft = false;
	freezeRight = false;
	isCollUp = false;
	isCollDown = false;
	isCollLeft = false;
	isCollRight = false;

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

	collider = App->collisions->AddCollider({ position.x, position.y + 7, 16, 16 }, Collider::Type::PLAYER, this);
	colliderUp = App->collisions->AddCollider({ position.x, position.y - 9, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	colliderDown = App->collisions->AddCollider({ position.x, position.y + 23, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	colliderLeft = App->collisions->AddCollider({ position.x - 16, position.y + 7, 16, 16 }, Collider::Type::PLAYER_NXT, this);
	colliderRight = App->collisions->AddCollider({ position.x + 16, position.y + 7, 16, 16 }, Collider::Type::PLAYER_NXT, this);

	char lookupTable[] = { "0123456789" };
	nFont = App->fonts->Load("Assets/hud_font.png", lookupTable, 1);

	return ret;
}

update_status ModulePlayer::PreUpdate()
{
	isCollUp = false;
	isCollDown = false;
	isCollLeft = false;
	isCollRight = false;

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::Update()
{
	if (lvlComplete || dead)
	{
		freeze = true;
	}

	if (freeze)
	{
		freezeUp = true;
		freezeDown = true;
		freezeLeft = true;
		freezeRight = true;
	}

	if (!isCollUp)
	{
		freezeUp = false;
	}
	if (!isCollDown)
	{
		freezeDown = false;
	}
	if (!isCollLeft)
	{
		freezeLeft = false;
	}
	if (!isCollRight)
	{
		freezeRight = false;
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !freeze)
	{
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
		if (!freezeLeft)
		{
			position.x -= speed;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !freeze)
	{
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
		if (!freezeRight)
		{
			position.x += speed;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !freeze)
	{
		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
		if (!freezeDown)
		{
			position.y += speed;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && !freeze)
	{		
		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
		if (!freezeUp)
		{
			position.y -= speed;
		}
	}

	// Bomb system
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && !freeze)
	{
		iPoint pos = CenterInTile({ position.x, position.y + 7 });
		App->bomb->PlaceBomb(pos);
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
	colliderUp->SetPos(position.x, position.y - 9);
	colliderDown->SetPos(position.x, position.y + 23);
	colliderLeft->SetPos(position.x - 16, position.y + 7);
	colliderRight->SetPos(position.x + 16, position.y + 7);

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
				App->fade->FadeToBlack(App->getScene->GetActualScene(), App->getScene->GetActualScene(), 60);
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
	if (c1 == collider && destroyed == false) // Normal collision
	{
		switch (c2->type)
		{
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

	if (c1 == colliderUp && destroyed == false) //Wall Collision
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			if (c1->rect.y == c2->rect.y + c2->rect.h - 16)
			{
				freezeUp = true;
				isCollUp = true;
			} break;

		case Collider::Type::ROCK:
			if (c1->rect.y == c2->rect.y)
			{
				freezeUp = true;
				isCollUp = true;
			} break;

		case Collider::Type::FLOWER:
			if (c1->rect.y == c2->rect.y)
			{
				freezeUp = true;
				isCollUp = true;
			} break;
		default:
			break;
		}
	}
	if (c1 == colliderDown && destroyed == false)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			if (c1->rect.y == c2->rect.y)
			{
				freezeDown = true;
				isCollDown = true;
			} break;

		case Collider::Type::ROCK:
			if (c1->rect.y == c2->rect.y)
			{
				freezeDown = true;
				isCollDown = true;
			} break;

		case Collider::Type::FLOWER:
			if (c1->rect.y == c2->rect.y)
			{
				freezeDown = true;
				isCollDown = true;
			} break;
		default:
			break;
		}
	}
	if (c1 == colliderLeft && destroyed == false)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			if (c1->rect.x == c2->rect.x + c2->rect.w - 16)
			{
				freezeLeft = true;
				isCollLeft = true;
			} break;

		case Collider::Type::ROCK:
			if (c1->rect.x == c2->rect.x)
			{
				freezeLeft = true;
				isCollLeft = true;
			} break;

		case Collider::Type::FLOWER:
			if (c1->rect.x == c2->rect.x)
			{
				freezeLeft = true;
				isCollLeft = true;
			} break;
		default:
			break;
		}
	}
	if (c1 == colliderRight && destroyed == false)
	{
		switch (c2->type)
		{
		case Collider::Type::WALL:
			if (c1->rect.x == c2->rect.x)
			{
				freezeRight = true;
				isCollRight = true;
			} break;

		case Collider::Type::ROCK:
			if (c1->rect.x == c2->rect.x)
			{
				freezeRight = true;
				isCollRight = true;
			} break;

		case Collider::Type::FLOWER:
			if (c1->rect.x == c2->rect.x)
			{
				freezeRight = true;
				isCollRight = true;
			} break;
		default:
			break;
		}
	}
}

iPoint ModulePlayer::GetPlayerPos()
{
	return position;
}

iPoint ModulePlayer::CenterInTile(iPoint p)
{
	iPoint f_point;

	if ((p.x - 24) % 16 == 0)
	{
		f_point.x = p.x;

		if ((p.y - 34) % 16 == 0)
		{
			f_point.y = p.y;
		}
		else
		{
			while ((p.y - 34) % 16 != 0)
			{
				p.y += 1;
			}

			f_point.y = p.y - 9;
		}
	}
	else
	{
		f_point.y = p.y;

		while ((p.x - 24) % 16 != 0)
		{
			p.x -= 1;
		}

		f_point.x = p.x;
	}

	return f_point;
}
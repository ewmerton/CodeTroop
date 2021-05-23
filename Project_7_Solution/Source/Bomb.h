#ifndef __BOMB_H__
#define __BOMB_H__

#include "SDL/include/SDL_Rect.h"

#include "Module.h"
#include "p2Point.h"

class ModuleBomb : public Module
{
public:

	//Constructor
	ModuleBomb(bool startEnabled);

	//Destructor
	~ModuleBomb();

	bool Start() override;

	update_status PreUpdate() override;

	update_status Update() override;

	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

	//Methods
	void PlaceBomb(iPoint p);

private:
	void SpawnBomb(iPoint p);

	void BombExplosion(iPoint p);

	uint placeBomb = 0;
	uint explote = 0;

	// Array for bombs
	uint a_bombs = 1;

	//Bomb bombs/*[MAX_BOMBS]*/ = { nullptr };
	Collider* collider = nullptr;

	iPoint position;

	bool Cooldown = false;
	uint count = 0;

	Collider* cUp = nullptr;
	Collider* cDown = nullptr;
	Collider* cLeft = nullptr;
	Collider* cRight = nullptr;
	bool continueUp, continueDown, continueLeft, continueRight;
	bool placed;

	Collider* extraUp = nullptr;
	Collider* extraDown = nullptr;
	Collider* extraLeft = nullptr;
	Collider* extraRight = nullptr;
};

#endif

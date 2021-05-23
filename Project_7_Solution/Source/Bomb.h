#ifndef __BOMB_H__
#define __BOMB_H__

#include "SDL/include/SDL_Rect.h"

#include "Module.h"
#include "p2Point.h"

#define MAX_BOMBS 5

struct Bomb {
	Collider* collider = nullptr;

	iPoint position, aP;

	bool Cooldown = false ;
	uint count = 0 ;
};

class ModuleBomb : public Module
{
public:

	//Constructor
	ModuleBomb(bool startEnabled);

	//Destructor
	~ModuleBomb();

	bool Start() override;

	update_status Update() override;

	//Methods
	void NewBomb();

	void PlaceBomb(iPoint p);

private:
	void SpawnBomb(iPoint p, int i);

	iPoint SavePosition(iPoint p, int n);

	void BombExplosion(iPoint p);

	uint placeBomb = 0;
	uint explote = 0;

	// Array for bombs
	uint n_bombs = 1;
	uint a_bombs = 1;

	uint n = 0;

	Bomb bombs[MAX_BOMBS] = { nullptr };
};

#endif

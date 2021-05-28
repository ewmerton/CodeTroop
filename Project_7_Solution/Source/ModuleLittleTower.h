#ifndef __MODULE_LITTLE_TOWER_H__
#define __MODULE_LITTLE_TOWER_H__

#include "Module.h"
#include "p2Point.h"

#define NUM_LITTLE_TOWERS 30

struct SDL_Texture;

struct Little_tower {
	Collider* colliderT = nullptr;
	SDL_Texture* little_towerT = nullptr;

	int x;
	int y;
	bool isDestroyed = false;
};

class ModuleLittleTower : public Module
{
public:
	//Constructor
	ModuleLittleTower(bool startEnabled);

	//Destructor
	~ModuleLittleTower();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;


	update_status Update() override;
	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;

public:

	// Rock position in map
	iPoint position;

	// The sprite rectangle for the rocks
	SDL_Texture* little_towerTexture = nullptr;

	Little_tower little_towers[NUM_LITTLE_TOWERS] = { nullptr };

	Little_tower CreateLittleTower(int x, int y, SDL_Texture* t);

	int rTowers;

};

#endif
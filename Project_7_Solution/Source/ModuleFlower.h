#ifndef __MODULE_FLOWER_H__
#define __MODULE_FLOWER_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"

#define NUM_FLOWERS 100

struct SDL_Texture;

struct Flower {
	Collider* colliderT = nullptr;
	SDL_Texture* flowerT = nullptr;

	int x;
	int y;
	bool isDestroyed = false;
	uint dCount = 0;
	bool destroyed = false;
};

class ModuleFlower : public Module
{
public:
	//Constructor
	ModuleFlower(bool startEnabled);

	//Destructor
	~ModuleFlower();

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
	SDL_Texture* flowerTexture = nullptr;

	Flower flowers[NUM_FLOWERS] = { nullptr };

	Flower CreateFlower(int x, int y, SDL_Texture* t);

	Animation* currentAnimation[NUM_FLOWERS] = { nullptr };
	Animation idle;
	Animation dead;

};

#endif
#ifndef __MODULE_RED_FLOWER_H__
#define __MODULE_RED_FLOWER_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"


#define NUM_RED_FLOWERS 5

struct SDL_Texture;

struct RedFlower {
	Collider* colliderT = nullptr;
	SDL_Texture* flowerT = nullptr;

	int x;
	int y;
	bool isDestroyed = false;
	uint dCount = 0;
	bool destroyed = false;
	
};

class ModuleRedFlower : public Module
{
public:
	//Constructor
	ModuleRedFlower(bool startEnabled);

	//Destructor
	~ModuleRedFlower();

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

	RedFlower red_flowers[NUM_RED_FLOWERS] = { nullptr };

	RedFlower CreateRedFlower(int x, int y, SDL_Texture* t);

	Animation* currentAnimation[NUM_RED_FLOWERS] = { nullptr };
	Animation idle;
	Animation dead;
};

#endif
#ifndef __MODULE_FLOWER_H__
#define __MODULE_FLOWER_H__

#include "Module.h"
#include "p2Point.h"

#define NUM_FLOWERS 26

struct SDL_Texture;

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

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	virtual void AddFlower(int x, int y);

public:

	// Rock position in map
	iPoint position;

	// The sprite rectangle for the rocks
	SDL_Texture* flowerTexture = nullptr;

	// Rock collider   no hace falta?
	//Collider* collider[NUM_FLOWER] = { nullptr };
};

#endif
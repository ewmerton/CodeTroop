#ifndef __MODULE_ROCK_H__
#define __MODULE_ROCK_H__

#include "Module.h"
#include "p2Point.h"

#define NUM_ROCKS 26

struct SDL_Texture;

class ModuleRock : public Module
{
public:
	//Constructor
	ModuleRock();

	//Destructor
	~ModuleRock();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:

	// Rock position in map
	iPoint position;

	// The sprite rectangle for the rocks
	SDL_Texture* rockTexture = nullptr;

	// Rock collider
	Collider* collider[NUM_ROCKS] = { nullptr };
};

#endif
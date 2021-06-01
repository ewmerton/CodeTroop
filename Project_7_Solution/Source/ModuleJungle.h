#ifndef __MODULE_JUNGLE__
#define __MODULE_JUNGLE__

#include "Module.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleJungle : public Module
{
public:
	//Constructor
	ModuleJungle(bool startEnabled);

	//Destructor
	~ModuleJungle();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;


	update_status Update() override;
	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;


public:

	// Rock position in map
	iPoint position;

	// The sprite rectangle for the rocks
	SDL_Texture* jungleTextureL = nullptr;
	SDL_Texture* jungleTextureR = nullptr;


};

#endif
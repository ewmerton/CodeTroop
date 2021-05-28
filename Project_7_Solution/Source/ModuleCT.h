#ifndef __MODULE_CT_H__
#define __MODULE_CT_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleCT : public Module
{
public:
	//Constructor
	ModuleCT(bool startEnabled);

	//Destructor
	~ModuleCT();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	update_status Update() override;
	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:

	// Tower position in map
	iPoint position;

	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation covertAnim;
	Animation idleAnim;
	Animation outAnim;

	void TowerDestroyed();
	void MoonColected();

	// The sprite rectangle for the Tower
	SDL_Texture* texture = nullptr;

	// Tower collider -- 3 colliders
	Collider* collider[7] = { nullptr };
	Collider* moon = nullptr;
	Collider* barrier = nullptr;
};

#endif

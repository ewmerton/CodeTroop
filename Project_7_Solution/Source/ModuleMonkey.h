#ifndef __MODULE_MONKEY_H__
#define __MODULE_MONKEY_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleMonkey : public Module
{
public:
	// Constructor
	ModuleMonkey(bool startEnabled);

	// Destructor
	~ModuleMonkey();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	update_status PreUpdate() override;
	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleUP;
	Animation idleDOWN;
	Animation idleLEFT;
	Animation idleRIGHT;
	Animation walkUP;
	Animation walkDOWN;
	Animation walkLEFT;
	Animation walkRIGHT;
	Animation tp;
	Animation deadAnim;

	// The player's collider
	Collider* collider = nullptr;
	Collider* b_collider[8] = { nullptr };
	Collider* colliderFace = nullptr;


	// A flag to detect when the player has been destroyed
	bool dead = false;
	uint dCount = 0;
	bool destroyed = false;
	bool isAlive();

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 60;

	// Sounds
	uint deadFx = 0;

	int lifes = 3;

	int delayUp = 15;
	int delayDown = 15;
	int delayLeft = 15;
	int delayRight = 15;
	bool dUp = false;
	bool dDown = false;
	bool dLeft = false;
	bool dRight = false;
	int u = 0;
	int d = 0;
	int l = 0;
	int r = 0;

	int delayTP = 15;
	bool dTP = false;

};

#endif

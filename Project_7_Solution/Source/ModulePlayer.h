#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Bomb.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

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

	iPoint CenterInTile(iPoint p);

	// The speed in which we move the player (pixels per frame)
	int speed = 1;
	bool freezeUp, freezeDown, freezeLeft, freezeRight;
	bool isCollUp, isCollDown, isCollLeft, isCollRight;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;
	Animation winAnim;
	Animation deadAnim;

	// The player's collider
	Collider* collider = nullptr;
	Collider* colliderUp = nullptr;
	Collider* colliderDown = nullptr;
	Collider* colliderLeft = nullptr;
	Collider* colliderRight = nullptr;


	// A flag to detect when the player has been destroyed
	bool dead = false;
	uint dCount = 0;
	bool destroyed = false;
	bool lvlComplete = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 60;

	// Font
	int nFont = -1;

	// Player's lifes
	uint lifes = 1;
	char lifesText[10] = { "\0" };

	// Player's score
	uint score = 0;
	char scoreText[10] = { "\0" };

	// Player's time
	uint stime = 0;
	char stimeText[10] = { "\0" };
	uint mtime = 0;
	char mtimeText[10] = { "\0" };

	// Sounds
	uint deadFx = 0;

	bool godMode = false;

	bool freeze = false;

};

#endif //!__MODULE_PLAYER_H__
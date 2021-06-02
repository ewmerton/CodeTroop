#ifndef _SCENESTAGE_H_
#define _SCENESTAGE_H_

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneStage : public Module
{
public:
	//constructor
	SceneStage(bool startEnabled);

	//destructor
	~SceneStage();

	//called when the module is activated
	//loads the necessary textures for the map background
	bool Start() override;

	//called at the middle of the application loop
	//updates the scene's background animations
	update_status Update() override;

	//called at the end of the application loop
	//performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* Texture1 = nullptr;
	SDL_Texture* Texture2 = nullptr;

	uint enter = 0;

	bool changeTex = false;
};

#endif

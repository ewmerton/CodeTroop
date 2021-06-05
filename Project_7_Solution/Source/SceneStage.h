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
	SDL_Texture* Texture3 = nullptr;
	SDL_Texture* Texture4 = nullptr;
	SDL_Texture* Texture5 = nullptr;
	SDL_Texture* Texture6 = nullptr;
	SDL_Texture* Texture7 = nullptr;
	SDL_Texture* Texture8 = nullptr;

	SDL_Texture* bgTexture2 = nullptr;
	SDL_Texture* Texture9 = nullptr;
	SDL_Texture* Texture10 = nullptr;
	SDL_Texture* Texture11 = nullptr;
	SDL_Texture* Texture12 = nullptr;
	SDL_Texture* Texture13 = nullptr;
	SDL_Texture* Texture14 = nullptr;
	SDL_Texture* Texture15 = nullptr;
	SDL_Texture* Texture16 = nullptr;

	


	uint enter = 0;
	uint cd = 0;

	bool changeTex = false;
};

#endif

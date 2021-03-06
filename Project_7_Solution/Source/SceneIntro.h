#ifndef _SCENEINTRO_H_
#define _SCENEINTRO_H_

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneIntro : public Module
{
public:
	//constructor
	SceneIntro(bool startEnabled);

	//destructor
	~SceneIntro();

	//called when the module is activated
	//loads the necessary textures for the map background
	bool Start() override;

	update_status PreUpdate() override;

	//called at the middle of the application loop
	//updates the scene's background animations
	update_status Update() override;

	//called at the end of the application loop
	//performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	bool CleanUp() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* intro = nullptr;
	SDL_Texture* SegaLogo = nullptr;
	SDL_Texture* SegaCreditos = nullptr;
	SDL_Texture* nameTexture = nullptr;
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* Texture1 = nullptr;
	SDL_Texture* Texture2 = nullptr;
	SDL_Texture* Texture3 = nullptr;
	SDL_Texture* Texture4 = nullptr;
	SDL_Texture* Texture5 = nullptr;

	uint arrow = 0;
	uint enter = 0;

	bool changeTex = false;
	bool changeTex2 = false;
	uint cd = 0;
};

#endif

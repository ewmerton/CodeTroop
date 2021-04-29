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

	//called at the middle of the application loop
	//updates the scene's background animations
	update_status Update() override;

	//called at the end of the application loop
	//performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
};

#endif	// __SCENEINTRO_H__

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

<<<<<<< HEAD
#define NUM_MODULES 15
=======
#define NUM_MODULES 13
>>>>>>> 8ee0bb5c96326010da4c88b47113baa386c72645

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneIntro;
class SceneLevel1;
class ModuleRock;
class ModuleCT;
class ModuleEnemies;
class ModuleParticles;
class ModuleCollisions;
class ModuleFonts;
class ModuleRender;
class ModuleFadeToBlack;


class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	SceneIntro* sceneIntro = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;

	ModuleRock* rock = nullptr;
	ModuleCT* tower = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
<<<<<<< HEAD
	ModuleFadeToBlack* fade = nullptr;
=======
>>>>>>> 8ee0bb5c96326010da4c88b47113baa386c72645
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
	
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Bomb.h"
#include "ModulePlayer.h"
#include "ModuleMonkey.h"
#include "GetScene.h"
#include "SceneIntro.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "ModuleJungle.h"
#include "ModuleRock.h"
#include "ModuleLittleTower.h"
#include "ModuleFlower.h"
#include "ModuleRedFlower.h"
#include "ModuleCT.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = getScene = new GetScene(false);
	modules[5] = sceneIntro = new SceneIntro(true);
	modules[6] = sceneLevel_1 = new SceneLevel1(false);
	modules[7] = sceneLevel_2 = new SceneLevel2(false);
	modules[8] = sceneLevel_3 = new SceneLevel3(false);

	modules[9] = rock = new ModuleRock(false);
	modules[10] = flower = new ModuleFlower(false);
	modules[11] = red_flower = new ModuleRedFlower(false);
	modules[12] = little_tower = new ModuleLittleTower(false);
	modules[13] = tower = new ModuleCT(false);
	modules[14] = particles = new ModuleParticles(true);
	modules[15] = bomb = new ModuleBomb(false);
	modules[16] = player = new ModulePlayer(false);
	modules[17] = monkey = new ModuleMonkey(false);
	modules[18] = enemies = new ModuleEnemies(false);
	modules[19] = jungle = new ModuleJungle(false);

	modules[20] = collisions = new ModuleCollisions(false);
	modules[21] = fonts = new ModuleFonts(true);
	modules[22] = fade = new ModuleFadeToBlack(true);
	modules[23] = render = new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	if (App->input->keys[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
	{
		return update_status::UPDATE_STOP;
	}

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}

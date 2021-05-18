#include "GetScene.h"

#include "Application.h"
#include "SceneLevel1.h"

GetScene::GetScene(bool startEnabled) : Module(startEnabled)
{

}

GetScene::~GetScene()
{

}

Module* GetScene::GetActualScene()
{
	if (App->sceneLevel_1->IsEnabled() == true)
	{
		ActualScene = (Module*)App->sceneLevel_1;
	}

	return ActualScene;
}

Module* GetScene::GetNextScene()
{
	if (App->sceneLevel_1->IsEnabled() == true)
	{
		//NextScene = (Module*)App->sceneLevel_2;
		NextScene = (Module*)App->sceneIntro; // TEMPORALMENTE
	}

	return NextScene;
}
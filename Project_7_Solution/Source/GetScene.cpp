#include "GetScene.h"

#include "Application.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"


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

	else if (App->sceneLevel_2->IsEnabled() == true)
	{
		ActualScene = (Module*)App->sceneLevel_2;
	}

	return ActualScene;
}

Module* GetScene::GetNextScene()
{
	if (App->sceneLevel_1->IsEnabled() == true)
	{
		NextScene = (Module*)App->sceneLevel_2;
	}

	return NextScene;
}
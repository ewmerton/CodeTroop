#include "GetScene.h"

#include "Application.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"


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
	else if (App->sceneLevel_3->IsEnabled() == true)
	{
		ActualScene = (Module*)App->sceneLevel_3;
	}

	return ActualScene;
}

Module* GetScene::GetNextScene()
{
	if (App->sceneLevel_1->IsEnabled() == true)
	{
		NextScene = (Module*)App->sceneLevel_2;
	}
	else if (App->sceneLevel_2->IsEnabled() == true)
	{
		NextScene = (Module*)App->sceneLevel_3;
	}
	else if (App->sceneLevel_3->IsEnabled() == true)
	{
		NextScene = (Module*)App->sceneIntro;
	}

	return NextScene;
}
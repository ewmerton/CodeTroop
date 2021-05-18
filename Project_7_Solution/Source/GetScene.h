#ifndef __GETSCENE_H__
#define __GETSCENE_H__

#include "Module.h"

class GetScene : public Module
{
public:
	// Constructor
	GetScene(bool startEnabled);

	// Destructor
	~GetScene();

public:
	Module* GetActualScene();
	Module* GetNextScene();

private:
	Module* ActualScene = nullptr;
	Module* NextScene = nullptr;

};

#endif
#pragma once

#include "SceneManager.h"
#include "SceneIsland.h"

class SceneManager
{
public:

	SceneIsland sceneIsland;
	AssetManager assetManager;

	SceneManager();

	void ClearScene();
	void UpdateScene();

	void LoadSceneIsland();
};


#pragma once

#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "SceneIsland.h"
#include "assetmanager.h"

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


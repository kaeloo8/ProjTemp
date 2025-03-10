#pragma once
#include <filesystem>
#include <vector>
#include <iostream>
#include "assetmanager.h"
#include "SceneManager.h"
#include "Ui.h"

class StartingGame
{
	SceneManager sceneManager;
	AssetManager assetManager;
	
public:
	int LoadGame();
	int LoadSave();
};


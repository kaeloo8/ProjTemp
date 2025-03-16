#pragma once
#include <iostream>
#include "GameManager.h"
#include "Scene.h"

template<typename T>
void GameManager::LaunchScene()
{
	VerifWin();
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	_ASSERT(true);

	for (auto En : mEntities) {
		En->Destroy();
	}

	T* newScene = new T();
	newScene->SetGameManager(this);

	bool loaded = false;
	/*for (auto VerifLoadedScene : SceneLoaded) {
		std::cout << newScene->SceneName << std::endl;
		if (newScene->SceneName == VerifLoadedScene->SceneName) {
			std::cout << "reprise" << std::endl;
			mpScene = VerifLoadedScene;
			mpScene->OnUpdate();
			loaded = true;
		}
	}*/

	if (!loaded) {
		mpScene = newScene;
		mpScene->SetGameManager(this);
		mpScene->OnInitialize();
		std::cout << "creation" << std::endl;
		NumberScene++;
		SceneLoaded.push_back(mpScene);
	}

	Run();
}
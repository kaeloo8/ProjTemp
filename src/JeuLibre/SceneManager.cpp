#include "pch.h"
#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager() : activeScene(nullptr) {
    // Par d�faut, on peut charger une sc�ne de d�marrage (ex: menu principal)
    LoadSceneMainMenu();
}

void SceneManager::ClearScene() {
    if (activeScene) {
        activeScene->OnExit();
        activeScene = nullptr;
    }
}

void SceneManager::UpdateScene(sf::Time deltaTime) {
    if (activeScene) {
        activeScene->Update(deltaTime);
    }
}

void SceneManager::LoadSceneIsland() {
    // Efface la sc�ne active
    ClearScene();
    // Active la sc�ne d'�le
    activeScene = &sceneIsland;
    activeScene->OnEnter();
    std::cout << "SceneIsland charg�e et active\n";
}

void SceneManager::LoadSceneMainMenu() {
    ClearScene();
    activeScene = &sceneMainMenu;
    activeScene->OnEnter();
    std::cout << "SceneMainMenu charg�e et active\n";
}

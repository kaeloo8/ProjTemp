#include "pch.h"
#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager() : activeScene(nullptr) {
    // Par défaut, on peut charger une scène de démarrage (ex: menu principal)
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
    // Efface la scène active
    ClearScene();
    // Active la scène d'île
    activeScene = &sceneIsland;
    activeScene->OnEnter();
    std::cout << "SceneIsland chargée et active\n";
}

void SceneManager::LoadSceneMainMenu() {
    ClearScene();
    activeScene = &sceneMainMenu;
    activeScene->OnEnter();
    std::cout << "SceneMainMenu chargée et active\n";
}

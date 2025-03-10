#pragma once

#include "SceneMainMenu.h"
#include "SceneIsland.h"
#include "AssetManager.h"
#include "IScene.h"

class SceneManager {
public:
    // Scènes disponibles
    SceneMainMenu sceneMainMenu;
    SceneIsland sceneIsland;
    AssetManager assetManager;
    
    SceneManager();

    // Efface la scène active et appelle OnExit() si nécessaire
    void ClearScene();

    // Met à jour la scène active (délègue Update())
    void UpdateScene(sf::Time deltaTime);

    // Charge et active la scène de l'île
    void LoadSceneIsland();

    // (Optionnel) Charge et active le menu principal
    void LoadSceneMainMenu();

private:
    IScene* activeScene;
};

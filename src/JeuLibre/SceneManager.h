#pragma once

#include "SceneMainMenu.h"
#include "SceneIsland.h"
#include "AssetManager.h"
#include "IScene.h"

class SceneManager {
public:
    // Sc�nes disponibles
    SceneMainMenu sceneMainMenu;
    SceneIsland sceneIsland;
    AssetManager assetManager;
    
    SceneManager();

    // Efface la sc�ne active et appelle OnExit() si n�cessaire
    void ClearScene();

    // Met � jour la sc�ne active (d�l�gue Update())
    void UpdateScene(sf::Time deltaTime);

    // Charge et active la sc�ne de l'�le
    void LoadSceneIsland();

    // (Optionnel) Charge et active le menu principal
    void LoadSceneMainMenu();

private:
    IScene* activeScene;
};

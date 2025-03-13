#pragma once

#include "AssetManager.h"
#include "IScene.h"
#include <memory>
#include "Scene.h"

class SceneManager {
private:
    std::unique_ptr<Scene> currentScene;

public:
    SceneManager() = default;

    // Change la sc�ne actuelle
    void setScene(std::unique_ptr<Scene> newScene);

    // Gestion des �v�nements
    void handleEvent(sf::Event& event);

    // Mise � jour
    void update(float dt);

    // Affichage
    void render(sf::RenderWindow& window);
};


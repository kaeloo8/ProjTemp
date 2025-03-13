#pragma once

#include "IScene.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class SceneMainMenu : public IScene {
public:
    void OnEnter() override {
        // Initialisation de la scène (chargement des assets, etc.)
    }

    void OnExit() override {
        // Nettoyage si nécessaire
    }

    void Update(sf::Time deltaTime) override {
        // Mise à jour du menu principal (gestion des entrées, animations, etc.)
    }
};

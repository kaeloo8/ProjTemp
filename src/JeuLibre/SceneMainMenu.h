#pragma once

#include "IScene.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class SceneMainMenu : public IScene {
public:
    void OnEnter() override {
        std::cout << "SceneMainMenu OnEnter\n";
        // Initialisation de la scène (chargement des assets, etc.)
    }

    void OnExit() override {
        std::cout << "SceneMainMenu OnExit\n";
        // Nettoyage si nécessaire
    }

    void Update(sf::Time deltaTime) override {
        // Mise à jour du menu principal (gestion des entrées, animations, etc.)
    }
};

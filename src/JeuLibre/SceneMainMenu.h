#pragma once

#include "IScene.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class SceneMainMenu : public IScene {
public:
    void OnEnter() override {
        std::cout << "SceneMainMenu OnEnter\n";
        // Initialisation de la sc�ne (chargement des assets, etc.)
    }

    void OnExit() override {
        std::cout << "SceneMainMenu OnExit\n";
        // Nettoyage si n�cessaire
    }

    void Update(sf::Time deltaTime) override {
        // Mise � jour du menu principal (gestion des entr�es, animations, etc.)
    }
};

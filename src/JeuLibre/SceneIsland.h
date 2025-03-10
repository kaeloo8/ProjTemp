#pragma once

#include "IScene.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class SceneIsland : public IScene {
public:
    void OnEnter() override {
        std::cout << "SceneIsland OnEnter\n";
        // Initialisation de la sc�ne (chargement des assets, configuration de l'�le, etc.)
    }

    void OnExit() override {
        std::cout << "SceneIsland OnExit\n";
        // Nettoyage de la sc�ne
    }

    void Update(sf::Time deltaTime) override {
        // Mise � jour de la sc�ne de l'�le (logique de jeu, mouvement, etc.)
    }
};

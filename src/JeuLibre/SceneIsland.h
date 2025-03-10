#pragma once

#include "IScene.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class SceneIsland : public IScene {
public:
    void OnEnter() override {
        std::cout << "SceneIsland OnEnter\n";
        // Initialisation de la scène (chargement des assets, configuration de l'île, etc.)
    }

    void OnExit() override {
        std::cout << "SceneIsland OnExit\n";
        // Nettoyage de la scène
    }

    void Update(sf::Time deltaTime) override {
        // Mise à jour de la scène de l'île (logique de jeu, mouvement, etc.)
    }
};

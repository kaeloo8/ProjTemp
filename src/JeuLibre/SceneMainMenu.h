#pragma once

#include "IScene.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class SceneMainMenu : public IScene {
public:
    void OnEnter() override {
        // Initialisation de la sc�ne (chargement des assets, etc.)
    }

    void OnExit() override {
        // Nettoyage si n�cessaire
    }

    void Update(sf::Time deltaTime) override {
        // Mise � jour du menu principal (gestion des entr�es, animations, etc.)
    }
};

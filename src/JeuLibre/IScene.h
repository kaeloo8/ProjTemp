#pragma once

#include <SFML/System.hpp>

class IScene {
public:
    virtual ~IScene() = default;
    virtual void OnEnter() = 0;                // Initialisation de la scène
    virtual void OnExit() = 0;                 // Nettoyage de la scène
    virtual void Update(sf::Time deltaTime) = 0; // Mise à jour de la scène
    // Vous pouvez ajouter une méthode Render(sf::RenderWindow&) si nécessaire
};

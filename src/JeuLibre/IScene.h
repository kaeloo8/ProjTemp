#pragma once

#include <SFML/System.hpp>

class IScene {
public:
    virtual ~IScene() = default;
    virtual void OnEnter() = 0;                // Initialisation de la sc�ne
    virtual void OnExit() = 0;                 // Nettoyage de la sc�ne
    virtual void Update(sf::Time deltaTime) = 0; // Mise � jour de la sc�ne
    // Vous pouvez ajouter une m�thode Render(sf::RenderWindow&) si n�cessaire
};

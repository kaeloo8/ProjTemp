#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "Entity.h"
#include "Player.h"

class CameraSys : public Entity
{
    sf::View camera;
    Entity* target = nullptr; // R�f�rence vers le joueur
    float smoothFactor = 0.1f; // Plus proche de 1 = cam�ra rapide, plus proche de 0 = lente

public:
    CameraSys();
    sf::View getView();
    void OnUpdate() override;

    void SetTarget(Entity* _Entity);
};

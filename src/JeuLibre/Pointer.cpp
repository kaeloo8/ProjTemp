#include "pch.h"
#include "Pointer.h"
#include "GameManager.h"

Pointer::Pointer() {
    Win = GameManager::Get()->GetWindow();
    SetOrigin(0, 0);
}

void Pointer::OnUpdate() {
    if (!Win || !Win->isOpen()) return;
    sf::Vector2i mousePosPixel = sf::Mouse::getPosition(*Win);

    // Convertir la position en coordonnées monde en tenant compte de la View
    worldPos = Win->mapPixelToCoords(mousePosPixel, Win->getView());

    SetPosition(worldPos.x, worldPos.y, 0.5);
}

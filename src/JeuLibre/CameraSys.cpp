#include "pch.h"
#include "CameraSys.h"
#include "GameManager.h"

CameraSys::CameraSys() {
    GameManager::Get()->SetCamera(this);
    float sizeX = GameManager::Get()->Window->getSize().x;
    float sizeY = GameManager::Get()->Window->getSize().y;
    camera.setSize(sizeX, sizeY);
}

sf::View CameraSys::getView() {
    return camera;
}

void CameraSys::SetTarget(Entity* _Entity) {
    target = _Entity;
}

void CameraSys::OnUpdate() {
    if (target) {
        sf::Vector2f camPos = camera.getCenter();
        sf::Vector2f targetPos = target->GetPosition();

        // Interpolation linéaire pour lisser le mouvement de la caméra
        sf::Vector2f newCamPos = camPos + (targetPos - camPos) * smoothFactor;

        camera.setCenter(newCamPos);
        GameManager::Get()->Window->setView(camera);
    }
}
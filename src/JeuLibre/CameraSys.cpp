#include "pch.h"
#include "CameraSys.h"
#include "TimeSys.h"

CameraSys::CameraSys() {
    GameManager::Get()->SetCamera(this);
    float sizeX = GameManager::Get()->Window->getSize().x;
    float sizeY = GameManager::Get()->Window->getSize().y;
    camera.setSize(sizeX, sizeY); // À adapter selon la fenêtre
    camera.setCenter(sizeX/2, sizeY/2);
}

sf::View CameraSys::getView() {
    return camera;
}

void CameraSys::OnUpdate() {
    float velocityX = 0.f;
    float velocityY = 0.f;
    float mSpeed = 300.f; // Pixels par seconde

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocityY -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocityY += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocityX -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocityX += 1.f;
    }

    // Normalisation pour éviter le déplacement diagonal plus rapide
    float length = std::sqrt(velocityX * velocityX + velocityY * velocityY);
    if (length > 0) {
        velocityX /= length;
        velocityY /= length;
    }

    // Appliquer le mouvement avec delta time
    float deltaTime = GameManager::Get()->GetDeltaTime();
    camera.move(velocityX * mSpeed * deltaTime, velocityY * mSpeed * deltaTime);
}

#include "pch.h"
#include "S1Ville.h"
#include "S0Menu.h"
#include <iostream>

void S1Ville::OnInitialize() {
    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);
    lPointer = CreateEntity<Pointer>("croix");
    lPointer->SetScale((Win->getSize().x * 0.12) / 100, (Win->getSize().x * 0.12) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->Layout = 10;

    lPlayer = CreateEntity<Player>("base_idle_strip9");
    lPlayer->SetScale(3, 3);
    lPlayer->SetOrigin(0.5f, 0.5f);
    lPlayer->SetPosition((GetWindowWidth() / 2) - lPlayer->GetSprite()->getGlobalBounds().width, (GetWindowHeight() / 2));
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(25, 20);
    lPlayer->Layout = 1;
    lPlayer->mSpeed = 1;

    KeyHPressed = false;
}

void S1Ville::SetName() {
    SceneName = "S1Ville";
}

void S1Ville::OnEvent(const sf::Event& event) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        if (!KeyHPressed) {
            std::cout << "H press" << std::endl;
            GameManager::Get()->LaunchScene<S0Menu>();
        }
    }
    else {
        KeyHPressed = false;
    }
}

void S1Ville::OnUpdate() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x, mousePos.y);

    float velocityX = 0.f;
    float velocityY = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocityY -= 5.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocityY += 5.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocityX -= 5.f;
        lPlayer->GetSprite()->setScale(-std::abs(lPlayer->GetSprite()->getScale().x), lPlayer->GetSprite()->getScale().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocityX += 5.f;
        lPlayer->GetSprite()->setScale(std::abs(lPlayer->GetSprite()->getScale().x), lPlayer->GetSprite()->getScale().y);
    }
    if (velocityX != 0 || velocityY != 0)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            lPlayer->mSpeed = 300;
            lPlayer->isSprinting = true;
        }
        else
        {
            lPlayer->isMoving = true;
            lPlayer->isSprinting = false;
            lPlayer->mSpeed = 150;
        }

    }
    else {
        lPlayer->isMoving = false;
    };


    //std::cout << lPlayer->mSpeed << std::endl;

    float magnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY);
    if (magnitude > 10.f) {
        velocityX = (velocityX / magnitude) * 10.f;
        velocityY = (velocityY / magnitude) * 10.f;
    }

    // On déplace le joueur
    lPlayer->GoToPosition(lPlayer->GetPosition().x + velocityX, lPlayer->GetPosition().y + velocityY, lPlayer->mSpeed);
}


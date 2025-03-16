#include "pch.h"
#include "S0Menu.h"
#include <iostream>

void S0Menu::OnInitialize() {
	Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);
	lPointer = CreateEntity<Pointer>("Pointer");
	lPointer->SetScale((Win->getSize().x * 0.12) / 100, (Win->getSize().x * 0.12) / 100);
	lPointer->SetOrigin(0, 0);
	lPointer->Layout = 10;

	lPlayer = CreateEntity<Player>("base_walk_strip8");
    lPlayer->SetScale(3,3);
    lPlayer->SetOrigin(0.5f, 0.5f);
	lPlayer->SetPosition((GetWindowWidth() / 2)-lPlayer->GetSprite()->getGlobalBounds().width, (GetWindowHeight() / 2));
	lPlayer->AddAABBHitbox();
	lPlayer->SetHitboxSize(25, 20);
	lPlayer->Layout = 1;
}
void S0Menu::OnEvent(const sf::Event& event) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		
	}
}

void S0Menu::OnUpdate() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x, mousePos.y);

    float velocityX = 0.f;
    float velocityY = 0.f;
    bool moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocityY -= 5.f;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocityY += 5.f;
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocityX -= 5.f;
        lPlayer->GetSprite()->setScale(-std::abs(lPlayer->GetSprite()->getScale().x), lPlayer->GetSprite()->getScale().y);
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocityX += 5.f;
        lPlayer->GetSprite()->setScale(std::abs(lPlayer->GetSprite()->getScale().x), lPlayer->GetSprite()->getScale().y);
        moving = true;
    }

    if (!moving) {
        // Si le joueur n'est pas en mouvement, on peut réinitialiser son animation
        lPlayer->SetRotation(0);
    }

    float magnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY);
    if (magnitude > 10.f) {
        velocityX = (velocityX / magnitude) * 10.f;
        velocityY = (velocityY / magnitude) * 10.f;
    }

    // On déplace le joueur
    lPlayer->GoToPosition(lPlayer->GetPosition().x + velocityX, lPlayer->GetPosition().y + velocityY, 200);
}

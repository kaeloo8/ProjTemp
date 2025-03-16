#include "pch.h"
#include "S0Menu.h"
#include <iostream>

void S0Menu::OnInitialize() {
	Win = GameManager::Get()->Window;
	lPointer = CreateEntity<Pointer>("Pointer");
	lPointer->SetScale((Win->getSize().x * 0.1) / 100, (Win->getSize().x * 0.1) / 100);
	lPointer->SetOrigin(1.f, 1.f);
	lPointer->Layout = 1;

	lPlayer = CreateEntity<Player>("croix");
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			velocityY -= 5.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			velocityY += 5.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			velocityX -= 5.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			velocityX += 5.f;
	}

	if (velocityY == 0)
	{
		lPlayer->SetRotation(0);
	}

	float magnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY);
	if (magnitude > 10.f) {
		velocityX = (velocityX / magnitude) * 10.f;
		velocityY = (velocityY / magnitude) * 10.f;
	}

	lPlayer->GoToPosition(lPlayer->GetPosition().x + velocityX, lPlayer->GetPosition().y + velocityY, 200);
}
void S0Menu::Load() {
	return;
}
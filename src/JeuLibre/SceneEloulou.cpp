#include "pch.h"
#include "SceneEloulou.h"
#include "S1Ville.h"
#include "S0Menu.h"
#include <iostream>

void SceneEloulou::OnInitialize() {
    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);
    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.12) / 100, (Win->getSize().x * 0.12) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->Layout = 200;

    Fond = CreateEntity<Entity>("FondEcran");
    Fond->SetOrigin(0, 0);
    Fond->SetPosition(0, 0);
    Fond->SetSize(GetWindowWidth(), GetWindowHeight());
    Fond->Layout = 0;

    lPlayer = CreateEntity<Player>("base_idle_strip9");
    lPlayer->SetScale(3, 3);
    lPlayer->SetOrigin(0.5f, 0.5f);
    lPlayer->SetPosition((GetWindowWidth() / 2) - lPlayer->GetSprite()->getGlobalBounds().width, (GetWindowHeight() / 2));
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(25, 20);
    lPlayer->Layout = 1;
}
void SceneEloulou::OnEvent(const sf::Event& event) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (!KeyEscPressed) {
            std::cout << "Retour Menu" << std::endl;
            GameManager::Get()->LaunchScene<S0Menu>();
        }
    }
    else {
        KeyEscPressed = false;
    }
}

void SceneEloulou::SetName() {
    SceneName = "SceneEloulou";
}

void SceneEloulou::OnUpdate() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x, mousePos.y);
}

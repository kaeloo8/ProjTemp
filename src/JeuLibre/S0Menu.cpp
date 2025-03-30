#include "pch.h"
#include "Scene.h"
#include "Entity.h"

#include "S0Menu.h"
#include "S1Ville.h"
#include "SceneChevalier.h"
#include "SceneEloulou.h"
#include "SceneGorille.h"
#include <iostream>

void S0Menu::OnInitialize() {
    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);

    GameManager::Get()->DrawHitBox = false;

    // Curseur personnalisé
    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.12) / 100, (Win->getSize().x * 0.12) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->AddCircleHitbox();
    lPointer->SetHitboxSize(10);
    lPointer->Layout = 10;

    float sizeX = 5;
    float sizeY = 5;

    // Boutons
    ButtonCheval = CreateEntity<Entity>("Bouton_0010");
    ButtonCheval->SetPosition(GetWindowWidth() - 200, GetWindowHeight() / 2 - 200);
    ButtonCheval->SetOrigin(0.5, 0.5);
    ButtonCheval->AddCircleHitbox();
    ButtonCheval->SetHitboxSize(30);
	ButtonCheval->SetScale(sizeX, sizeY);
    ButtonCheval->Layout = 2;
    ButtonCheval->mTag = GameManager::Tag::tHoverable;

    ButtonElo = CreateEntity<Entity>("Bouton_0008");
    ButtonElo->SetPosition(GetWindowWidth() - 200, GetWindowHeight() / 2);
    ButtonElo->SetOrigin(0.5, 0.5);
    ButtonElo->AddCircleHitbox();
    ButtonElo->SetHitboxSize(30);
    ButtonElo->SetScale(sizeX, sizeY);
    ButtonElo->Layout = 2;
    ButtonElo->mTag = GameManager::Tag::tHoverable;

    ButtonLeo = CreateEntity<Entity>("Bouton_0011");
    ButtonLeo->SetPosition(GetWindowWidth() - 200, GetWindowHeight() / 2 + 200);
    ButtonLeo->SetOrigin(0.5, 0.5);
    ButtonLeo->AddCircleHitbox();
    ButtonLeo->SetHitboxSize(30);
    ButtonLeo->SetScale(sizeX, sizeY);
    ButtonLeo->Layout = 2;
    ButtonLeo->mTag = GameManager::Tag::tHoverable;

    Fond = CreateEntity<Entity>("FondEcran");
    Fond->SetOrigin(0, 0);
    Fond->SetPosition(0, 0);
    Fond->SetSize(GetWindowWidth(), GetWindowHeight());
    Fond->Layout = 0;
}

void S0Menu::OnEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = Win->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

        if (ButtonCheval->mSprite.getGlobalBounds().contains(mousePos)) {
            GameManager::Get()->LaunchScene<SceneChevalier>();
        }
        if (ButtonElo->mSprite.getGlobalBounds().contains(mousePos)) {
            GameManager::Get()->LaunchScene<SceneEloulou>();
        }
        if (ButtonLeo->mSprite.getGlobalBounds().contains(mousePos)) {
            //GameManager::Get()->LaunchScene<SceneGorille>();
        }
    }
}


void S0Menu::SetName() {

}

void S0Menu::OnUpdate() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x, mousePos.y);
}
#include "pch.h"
#include "Scene.h"
#include "Entity.h"
#include "S0Menu.h"
#include "S1Ville.h"
#include "UI.h"
#include "SceneChevalier.h"
#include "SceneEloulou.h"
#include "SceneGorille.h"
#include "Bouton.h"
#include <iostream>

void S0Menu::OnInitialize() {
    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);

    GameManager::Get()->DrawHitBox = false;

    lUI = CreateEntity<UI>("0");
    lUI->Layout = -1;

    lUI->CreateButton(GetWindowWidth() - 200, GetWindowHeight() / 2 - 200, 100, 100, "sc1", "Bouton_0004", "Bouton_0005");
    lUI->CreateButton(GetWindowWidth() - 200, GetWindowHeight() / 2, 100, 100, "sc2", "Bouton_0000", "Bouton_0001");
    lUI->CreateButton(GetWindowWidth() - 200, GetWindowHeight() / 2 + 200, 100, 100, "sc3", "Bouton_0006", "Bouton_0007");

    // Curseur personnalisé
    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.12) / 100, (Win->getSize().x * 0.12) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->AddCircleHitbox();
    lPointer->SetHitboxSize(10);
    lPointer->Layout = 21;

    Fond = CreateEntity<Entity>("FondEcran");
    Fond->SetOrigin(0, 0);
    Fond->SetPosition(0, 0);
    Fond->SetSize(GetWindowWidth(), GetWindowHeight());
    Fond->Layout = 0;
}

void S0Menu::OnEvent(const sf::Event& event) {

}


void S0Menu::SetName() {

}

void S0Menu::OnUpdate() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x, mousePos.y);

    if (lUI->IsHovering("sc1") && lUI->IsClicked("sc1"))
        GameManager::Get()->LaunchScene<SceneChevalier>();
    if (lUI->IsHovering("sc2") && lUI->IsClicked("sc2"))
        GameManager::Get()->LaunchScene<SceneEloulou>();
    if (lUI->IsHovering("sc3") && lUI->IsClicked("sc3"))
        GameManager::Get()->LaunchScene<SceneGorille>();

    //lUI->GetB("sc1")->pos = {30, 30};
}
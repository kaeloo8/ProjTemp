#include "pch.h"
#include "S0Menu.h"
#include "SceneChevalier.h"

void SceneChevalier::OnInitialize()
{
}

void SceneChevalier::OnEvent(const sf::Event& event)
{
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

void SceneChevalier::OnUpdate()
{
}

void SceneChevalier::SetName()
{
}

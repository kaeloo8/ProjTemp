#include "pch.h"
#include "SceneGorille.h"
#include "S0Menu.h"

void SceneGorille::OnInitialize()
{
}

void SceneGorille::OnEvent(const sf::Event& event)
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

void SceneGorille::OnUpdate()
{
}

void SceneGorille::SetName()
{
}

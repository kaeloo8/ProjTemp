#include "pch.h"
#include "S0Menu.h"
#include "SceneChevalier.h"
#include "TileMap.h"
#include "CameraSys.h"

void SceneChevalier::OnInitialize()
{

    cam = CreateEntity<CameraSys>("0");
    cam->Layout = -1;

    Win = GameManager::Get()->Window;
    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.13) / 100, (Win->getSize().x * 0.13) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->Layout = 200;

    lPlayer = CreateEntity<Player>("base_idle_strip9");
    lPlayer->SetScale(3, 3);
    lPlayer->SetOrigin(0.5f, 0.5f);
    lPlayer->SetPosition((GetWindowWidth() / 2) - lPlayer->GetSprite()->getGlobalBounds().width, (GetWindowHeight() / 2));
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(25, 20);
    lPlayer->Layout = 2;

    map = CreateEntity<TileMap>("0");
    map->Layout = -1;
    map->create("mapVille");
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

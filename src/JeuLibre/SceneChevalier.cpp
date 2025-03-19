#include "pch.h"
#include "S0Menu.h"
#include "SceneChevalier.h"
#include "TileMap.h"
#include "CameraSys.h"
#include <random>

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
    lPlayer->SetHitboxSize(lPlayer->mSprite.getGlobalBounds().width/6, lPlayer->mSprite.getGlobalBounds().height/4);
    lPlayer->Layout = 2;

    for (int i = 0;i < 10; i++) {
        Monster* M;
        M = CreateEntity<Monster>("skeleton_idle_strip6");
        M->SetScale(3, 3);
        M->SetOrigin(0.5f, 0.5f);
        M->SetPosition((std::rand() % 600) + 100, (std::rand() % 400) + 100);
        M->AddAABBHitbox();
        M->SetHitboxSize(lPlayer->mSprite.getGlobalBounds().width / 6, lPlayer->mSprite.getGlobalBounds().height / 4);
        M->Layout = 2;
    }

    // DÉFINIR LE JOUEUR COMME CIBLE DE LA CAMÉRA
    cam->SetTarget(lPlayer);

    TileMap* map = new TileMap();
    map->create("mapVille"); // Charge la map
    GameManager::Get()->SetTileMap(map);
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
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*Win); // Récupérer position pixel
        sf::Vector2f worldPos = Win->mapPixelToCoords(pixelPos); // Convertir en coordonnées monde

    }

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
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x + lPlayer->GetPosition().x - GameManager::Get()->Window->getSize().x/2, mousePos.y + lPlayer->GetPosition().y - GameManager::Get()->Window->getSize().y / 2);
}

void SceneChevalier::SetName()
{
}

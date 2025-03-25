#include "pch.h"
#include "S0Menu.h"
#include "SceneChevalier.h"
#include "TileMap.h"
#include "CameraSys.h"
#include <random>

void SceneChevalier::OnInitialize()
{
    GameManager::Get()->AssetMana.LoadFromFile("../../../img/MapTile/");

    cam = CreateEntity<CameraSys>("0");
    cam->Layout = -1;

    CamFocus = CreateEntity<Entity>("0");
    CamFocus->SetPosition(650, 340);
    CamFocus->Layout = -1;

    cam->SetTarget(CamFocus);

    Win = GameManager::Get()->Window;
    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.13) / 100, (Win->getSize().x * 0.13) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->Layout = 200;

    lPlayer = CreateEntity<Player>("base_idle_strip9");
    lPlayer->SetScale(3, 3);
    lPlayer->SetOrigin(0.5f, 0.5f);
    lPlayer->SetPosition(650,340);
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
        M->mTarget = lPlayer;
    }

    // DÉFINIR LE JOUEUR COMME CIBLE DE LA CAMÉRA

    TileMap* map = new TileMap();
    map->SetPosition(0, 0);
    map->createD();
    GameManager::Get()->SetTileMap(map);

    Entity* W1 = CreateEntity<Entity>("0");
    W1->Layout = -1;
    W1->AddAABBHitbox();
    W1->SetHitboxSize(1300, 50);
    W1->SetPosition(650, 25);

    lColide.push_back(W1);

    Entity* W2 = CreateEntity<Entity>("0");
    W2->Layout = -1;
    W2->AddAABBHitbox();
    W2->SetHitboxSize(1300, 50);
    W2->SetPosition(650, 675);
    
    lColide.push_back(W2);

    Entity* W3 = CreateEntity<Entity>("0");
    W3->Layout = -1;
    W3->AddAABBHitbox();
    W3->SetHitboxSize(50, 700);
    W3->SetPosition(25, 350);

    lColide.push_back(W3);

    Entity* W4 = CreateEntity<Entity>("0");
    W4->Layout = -1;
    W4->AddAABBHitbox();
    W4->SetHitboxSize(50, 700);
    W4->SetPosition(1275, 350);

    lColide.push_back(W4);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        CamFocus->SetPosition(650, 340);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        CamFocus->SetPosition(1950, 340);
    }

}

void SceneChevalier::OnUpdate()
{
    
}

void SceneChevalier::SetName()
{
}

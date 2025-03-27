#include "pch.h"
#include "S0Menu.h"
#include "SceneChevalier.h"
#include "TileMap.h"
#include "CameraSys.h"
#include <random>

void SceneChevalier::OnInitialize()
{
    GameManager::Get()->AssetMana.LoadFromFile("../../../img/MapTile/Donjon");

    cam = CreateEntity<CameraSys>("0");
    cam->Layout = -1;

    Decalx = 1300;
    Decaly = 700;

    CamFocus = CreateEntity<Entity>("0");
    CamFocus->SetPosition(Decalx / 2, Decaly / 2);
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
    lPlayer->SetPosition(Decalx / 2, Decaly / 2);
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(lPlayer->mSprite.getGlobalBounds().width/6, lPlayer->mSprite.getGlobalBounds().height/4);
    lPlayer->Layout = 2;
    
    for (int i = 0;i < 10; i++) {
        Monster* M;
        M = CreateEntity<Monster>("skeleton_idle_strip6");
        M->AddCircleHitbox();
        M->MonsterOption(true, true, true, true);
        M->InitMonster("skeleton");
        M->SetScale(3, 3);
        M->SetOrigin(0.5f, 0.5f);
        M->SetPosition((std::rand() % 301) + (400 * (std::rand() % 2))+ 100, (std::rand() % 201) + (200 * (std::rand() % 2)) + 100);
        M->SetInitialPosition();
        M->SetSpeed(100);
        M->SetTarget(lPlayer);
        M->Layout = 2;
        lEnnemie.push_back(M);
    }

    // DÉFINIR LE JOUEUR COMME CIBLE DE LA CAMÉRA

    TileMap* map = new TileMap();
    map->SetPosition(0, 0);
    map->createD();
    GameManager::Get()->AddTileMap(map);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        lEnnemie[0]->ChangeHide();
        lEnnemie[1]->ChangeHide();
        lEnnemie[2]->ChangeHide();
        lEnnemie[3]->ChangeHide();
        lEnnemie[4]->ChangeHide();
    }

}

void SceneChevalier::OnUpdate()
{
    if (lPlayer->GetPosition().x < CamFocus->GetPosition().x - (Decalx / 2))
        CamFocus->SetPosition(CamFocus->GetPosition().x - Decalx, CamFocus->GetPosition().y);

    if (lPlayer->GetPosition().x > CamFocus->GetPosition().x + (Decalx / 2))
        CamFocus->SetPosition(CamFocus->GetPosition().x + Decalx, CamFocus->GetPosition().y);

    if (lPlayer->GetPosition().y < CamFocus->GetPosition().y - (Decaly / 2))
        CamFocus->SetPosition(CamFocus->GetPosition().x, CamFocus->GetPosition().y - Decaly);

    if (lPlayer->GetPosition().y > CamFocus->GetPosition().y + (Decaly / 2))
        CamFocus->SetPosition(CamFocus->GetPosition().x, CamFocus->GetPosition().y + Decaly);
    
}

void SceneChevalier::SetName()
{
}

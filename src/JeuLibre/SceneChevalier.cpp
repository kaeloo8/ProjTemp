#include "pch.h"
#include "S0Menu.h"
#include "SceneChevalier.h"
#include "TileMap.h"
#include "CameraSys.h"
#include <random>
#include "SpawnSys.h"

void SceneChevalier::OnInitialize()
{

    cam = CreateEntity<CameraSys>("DropM_0000");
    cam->Layout = -1;

    Decalx = 1300;
    Decaly = 700;

    CamFocus = CreateEntity<Entity>("DropM_0000");
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
    lPlayer->mMode = PlayerMode::Attack;
    
    for (int i = 0;i < 3; i++) {
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
        M->SetTag(GameManager::Tag::tEnnemie);
        lEnnemie.push_back(M);
    }

    int sx = GameManager::Get()->Window->getSize().x - 100;
    int sy = GameManager::Get()->Window->getSize().y - 100;

    SpawnArea = CreateEntity<SpawnSys>("TileMap_0174");
    SpawnArea->SetSize(sx, sy);
    SpawnArea->SetOrigin(0.5, 0.5);
    SpawnArea->Layout = -1;
    SpawnArea->SetCam(CamFocus);
    SpawnArea->SetTarget(lPlayer);
    SpawnArea->AddAABBHitbox();
    SpawnArea->nSpawn = 10;

    TileMap* map = new TileMap();
    map->SetPosition(0, 0);
    map->createD();
    GameManager::Get()->AddTileMap(map);


    GameManager::Get()->InDonjon = true;

    verifspawn = false;
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
    if (lPlayer->GetPosition().x < CamFocus->GetPosition().x - (Decalx / 2)) {
        CamFocus->SetPosition(CamFocus->GetPosition().x - Decalx, CamFocus->GetPosition().y);
        verifspawn = false;
    }

    if (lPlayer->GetPosition().x > CamFocus->GetPosition().x + (Decalx / 2)) {
        CamFocus->SetPosition(CamFocus->GetPosition().x + Decalx, CamFocus->GetPosition().y);
        verifspawn = false;
    }

    if (lPlayer->GetPosition().y < CamFocus->GetPosition().y - (Decaly / 2)) {
        CamFocus->SetPosition(CamFocus->GetPosition().x, CamFocus->GetPosition().y - Decaly);
        verifspawn = false;
    }

    if (lPlayer->GetPosition().y > CamFocus->GetPosition().y + (Decaly / 2)) {
        CamFocus->SetPosition(CamFocus->GetPosition().x, CamFocus->GetPosition().y + Decaly);
        verifspawn = false;
    }
    
    float lptc = (CamFocus->GetPosition().x - lPlayer->GetPosition().x) + (CamFocus->GetPosition().y - lPlayer->GetPosition().y);
    if (lptc < 0) {
        lptc *= -1;
    }
    if (verifspawn == false && lptc < 300) {
        SpawnArea->move(CamFocus->GetPosition());
    }
}

void SceneChevalier::SetName()
{
}

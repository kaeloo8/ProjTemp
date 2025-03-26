#include "pch.h"
#include "SceneEloulou.h"
#include "TileMap.h"
#include "S1Ville.h"
#include "S0Menu.h"
#include <iostream>

void SceneEloulou::OnInitialize() {

    GameManager::Get()->AssetMana.LoadFromFile("../../../img/MapTile/");
    map = new TileMap();
    map->create("Ocean"); // Charge la map
    GameManager::Get()->SetTileMap(map);

    Cam = CreateEntity<CameraSys>("0");
    Cam->Layout = -1;

    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);
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
    lPlayer->Layout = 1;

    lBuild = CreateEntity<BuildSystem>("0");
    lBuild->SetPlayer(lPlayer);
    lBuild->SetPointer(lPointer);

    //Skeleton = CreateEntity<Monster>("skeleton_idle_strip6");
    //Skeleton->MonsterOption(true, true, true, true);
    //Skeleton->InitMonster("skeleton");
    //Skeleton->SetScale(3, 3);
    //Skeleton->SetOrigin(0.5f, 0.5f);
    //Skeleton->SetPosition((GetWindowWidth() / 2 +500), (GetWindowHeight() / 2));
    //Skeleton->SetInitialPosition();
    //Skeleton->SetSpeed(100);
    //Skeleton->SetTarget(lPlayer);
    //Skeleton->Layout = 2;

    Cam->SetTarget(lPlayer);

    float sizeX = 5;
    float sizeY = 5;
}

void SceneEloulou::OnEvent(const sf::Event& event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
        if (!KeyEscPressed) {
            std::cout << "Tile select" << std::endl;
            map->tiles[1].clear();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
        if (!KeyEscPressed) {
            map->tiles[lBuild->Tiley][lBuild->Tilex].sprite.setTexture(GameManager::Get()->GetTexture("TileMap_0004"));
        }
    }
}

void SceneEloulou::SetName() {
    SceneName = "SceneEloulou";
}

void SceneEloulou::Load()
{
}

void SceneEloulou::OnUpdate() {
    if (IsInBuildingMode)
    {
        lBuild->ChooseTile();
    }
    map->UpdateWater();
}

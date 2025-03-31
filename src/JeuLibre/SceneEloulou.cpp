#include "pch.h"
#include "SceneEloulou.h"
#include "TileMap.h"
#include "S1Ville.h"
#include "S0Menu.h"
#include <iostream>

void SceneEloulou::OnInitialize() {

    GameManager::Get()->AssetMana.LoadFromFile("../../../img/MapTile/");
    Ocean = new TileMap();
    Ocean->create("Ocean");
    GameManager::Get()->AddTileMap(Ocean);
    map = new TileMap();
    map->create("Ile");
    GameManager::Get()->AddTileMap(map);

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
    lPlayer->SetPosition((GetWindowWidth() *1.5), (GetWindowHeight() * 1.5));
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(25, 20);
    lPlayer->Layout = 5;

    lBuild = CreateEntity<BuildSystem>("0");
    lBuild->SetPlayer(lPlayer);
    lBuild->SetPointer(lPointer);

    Mur1 = CreateEntity<Entity>("3");
    Mur1->SetOrigin(0.5, 0.5);
    Mur1->SetScale(3, 3);
    Mur1->SetPosition((GetWindowWidth() * 1.5) + 100, (GetWindowHeight() * 1.5));
    Mur1->AddAABBHitbox();
    Mur1->SetHitboxSize(Mur1->mSprite.getGlobalBounds().width, Mur1->mSprite.getGlobalBounds().height);
    Mur1->SolidHitbox();

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
            std::cout << map->tiles[lBuild->Tiley][lBuild->Tilex].type << std::endl;
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (lPlayer->mMode != PlayerMode::Attack)
        {
            lPlayer->ActionPoint = { lBuild->GetBuildPosition().x, lBuild->GetBuildPosition().y };
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
    if (lPlayer->mMode != PlayerMode::Attack)
    {
        if (lPlayer->mState != PlayerState::sGoToWork)
        {
            lBuild->ChooseTile();
        }
    }
    if (lPlayer->mMode == PlayerMode::Dig) {
        if (lPlayer->mState == PlayerState::sDig && lPlayer->HasDug == true) {
            Hole* H = CreateEntity<Hole>("soil_00");
            H->SetPosition(lPlayer->ActionPoint.x, lPlayer->ActionPoint.y);
            H->SetSize(50, 50);
            H->Layout = 3;

            lHole.push_back(H);
            std::cout << lHole.size() << std::endl;

            lPlayer->HasDug = false;
        }
        else if (lPlayer->mState != PlayerState::sDig) {
            lPlayer->HasDug = false;
        }
    }

    Ocean->UpdateWater();
}

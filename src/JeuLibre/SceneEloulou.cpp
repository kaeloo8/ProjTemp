#include "pch.h"
#include "SceneEloulou.h"
#include "TileMap.h"
#include "S1Ville.h"
#include "S0Menu.h"
#include <iostream>

void SceneEloulou::OnInitialize() {

    GameManager::Get()->AssetMana.LoadFromFile("../../../img/MapTile/");
    map = new TileMap();
    map->create("mapVille"); // Charge la map
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
    lBuild->SetEditableTilemap(map);

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
    // Gestion du clic de souris pour le menu
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        // Si la souris est dans la zone du menu (ex : dernière 80 pixels de la fenêtre)
        if (mousePos.x > Win->getSize().x - 80) {
            lBuild->HandleMenuClick(mousePos);
            return; // On ne change pas de tile si on clique dans le menu
        }
    }

    // Si la touche T est pressée, on remplace la texture de la tile sélectionnée
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
        if (!KeyEscPressed) {
            // Appel de ChooseTile qui va placer le sprite de remplacement sur la tile sélectionnée
            lBuild->ChooseTile();
            // Mise à jour de la texture de la tile dans la map
            sf::Texture& newTexture = GameManager::Get()->AssetMana.GetTexture(lBuild->currentTextureID);
            map->tiles[lBuild->Tiley][lBuild->Tilex].sprite.setTexture(newTexture);
        }
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

void SceneEloulou::SetName() {
    SceneName = "SceneEloulou";
}

void SceneEloulou::Load()
{
}

void SceneEloulou::OnUpdate() {
    if (IsInBuildingMode)
    {
        //lBuild->ChooseTile();
    }
}

#include "pch.h"
#include "SceneEloulou.h"
#include "TileMap.h"
#include "S1Ville.h"
#include "S0Menu.h"
#include <iostream>

void SceneEloulou::OnInitialize() {

    GameManager::Get()->AssetMana.LoadFromFile("../../../img/MapTile/");

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

    Cam->SetTarget(lPlayer);

    Skeleton = CreateEntity<Monster>("skeleton_idle_strip6");
    Skeleton->SetScale(3, 3);
    Skeleton->SetOrigin(0.5f, 0.5f);
    Skeleton->SetPosition((GetWindowWidth() / 2 +500), (GetWindowHeight() / 2));
    Skeleton->SetInitialPosition();
    Skeleton->SetSpeed(100);
    Skeleton->SetTarget(lPlayer);
    Skeleton->Layout = 2;


    float sizeX = 5;
    float sizeY = 5;

    Button1 = CreateEntity<Entity>("bouttonJaune");
    Button1->SetPosition(GetWindowWidth()/2 - 300, GetWindowHeight() / 7);
    Button1->SetOrigin(0.5, 0.5);
    Button1->AddCircleHitbox();
    Button1->SetHitboxSize(80);
    Button1->SetScale(sizeX, sizeY);
    Button1->Layout = 2;

    Button2 = CreateEntity<Entity>("bouttonBleu");
    Button2->SetPosition(GetWindowWidth()/2 -100, GetWindowHeight() / 7);
    Button2->SetOrigin(0.5, 0.5);
    Button2->AddCircleHitbox();
    Button2->SetHitboxSize(30);
    Button2->SetScale(sizeX, sizeY);
    Button2->Layout = 2;

    Button3 = CreateEntity<Entity>("bouttonBleu");
    Button3->SetPosition(GetWindowWidth()/2 + 100, GetWindowHeight() / 7);
    Button3->SetOrigin(0.5, 0.5);
    Button3->AddCircleHitbox();
    Button3->SetHitboxSize(30);
    Button3->SetScale(sizeX, sizeY);
    Button3->Layout = 2;

    Button4 = CreateEntity<Entity>("bouttonJaune");
    Button4->SetPosition(GetWindowWidth() / 2 + 300, GetWindowHeight() / 7);
    Button4->SetOrigin(0.5, 0.5);
    Button4->AddCircleHitbox();
    Button4->SetHitboxSize(30);
    Button4->SetScale(sizeX, sizeY);
    Button4->Layout = 2;

    Button5 = CreateEntity<Entity>("bouttonVert");
    Button5->SetPosition(GetWindowWidth() / 2 + 500, GetWindowHeight() / 7);
    Button5->SetOrigin(0.5, 0.5);
    Button5->AddCircleHitbox();
    Button5->SetHitboxSize(30);
    Button5->SetScale(sizeX, sizeY);
    Button5->Layout = 2;

    Button6 = CreateEntity<Entity>("bouttonVert");
    Button6->SetPosition(GetWindowWidth() / 2 - 500, GetWindowHeight() / 7);
    Button6->SetOrigin(0.5, 0.5);
    Button6->AddCircleHitbox();
    Button6->SetHitboxSize(30);
    Button6->SetScale(sizeX, sizeY);
    Button6->Layout = 2;

    TileMap* map = new TileMap();
    map->create("mapVille"); // Charge la map
    GameManager::Get()->SetTileMap(map);
}

void SceneEloulou::OnEvent(const sf::Event& event) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (!KeyEscPressed) {
            std::cout << "Retour Menu" << std::endl;
            GameManager::Get()->LaunchScene<S0Menu>();
        }
    }
    else {
        KeyEscPressed = false;
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = Win->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

        if (Button1->mSprite.getGlobalBounds().contains(mousePos)) {
            lPlayer->ChangeHaircut("longhair");
        }
        if (Button2->mSprite.getGlobalBounds().contains(mousePos)) {
            lPlayer->ChangeHaircut("curlyhair");
        }
        if (Button3->mSprite.getGlobalBounds().contains(mousePos)) {
            lPlayer->ChangeHaircut("shorthair");
        }
        if (Button4->mSprite.getGlobalBounds().contains(mousePos)) {
            lPlayer->ChangeHaircut("mophair");
        }
        if (Button5->mSprite.getGlobalBounds().contains(mousePos)) {
            lPlayer->ChangeHaircut("bowlhair");
        }
        if (Button6->mSprite.getGlobalBounds().contains(mousePos)) {
            lPlayer->ChangeHaircut("spikeyhair");
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
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x + lPlayer->GetPosition().x - GameManager::Get()->Window->getSize().x / 2, mousePos.y + lPlayer->GetPosition().y - GameManager::Get()->Window->getSize().y / 2);

}

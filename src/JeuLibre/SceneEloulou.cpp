#include "pch.h"
#include "SceneEloulou.h"
#include "TileMap.h"
#include "S1Ville.h"
#include "S0Menu.h"
#include <iostream>
#include <algorithm>

void SceneEloulou::OnInitialize() {

    if (GameManager::Get()->tileMaps.size() < 1) {
        Ocean = new TileMap();
        Ocean->create("Ocean");
        GameManager::Get()->AddTileMap(Ocean);
        map = new TileMap();
        map->create("Ile");
        GameManager::Get()->AddTileMap(map);
    }
    else {
        Ocean = GameManager::Get()->GetTileMap(0);
        Ocean->SetPosition(0, 0);
        map = GameManager::Get()->GetTileMap(1);
        map->SetPosition(0, 0);
    }

    GameManager::Get()->InDonjon = false;

    Cam = CreateEntity<CameraSys>("0");
    Cam->Layout = -1;

    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);
    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.13) / 100, (Win->getSize().x * 0.13) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->AddCircleHitbox();
    lPointer->SetHitboxSize(1);
    lPointer->SetTag(GameManager::Tag::tPointer);
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
	lBuild->SetTileMap(map);
    lBuild->SetPoiter(lPointer);

    Cam->SetTarget(lPlayer);

    for (auto& Tile : map->lTile)
    {
        if (Tile.type == TileType::Spawnable)
        {
            bool isTree = std::rand() % 2 == 0;  // Tire aléatoirement entre 0 et 1

            if (std::rand() % 16 == 1)  // Si le tirage est égal à 1 (comme dans ton exemple)
            {
                if (isTree)  // Si le booléen est vrai, génère un arbre
                {
                    Flore* T = CreateEntity<Flore>("Tree_0001");
                    T->SetOrigin(0.5, 0.5);
                    T->SetPosition(Tile.sprite.getPosition().x + 25, Tile.sprite.getPosition().y);
                    T->SetSize(100, 100);
                    T->AddAABBHitbox();
                    T->SetHitboxSize(25, 25);
                    T->SolidHitbox();
                    T->SetFloreLife(3);
                    T->Layout = 3;
                    lFlore.push_back(T);
                    Tile.type = TileType::Tree;
                    T->mFloreType = FloreType::Tree;
                    Tile.AddEntityOnTile(T);
                }
                else  // Si le booléen est faux, génère une pierre
                {
                    // Tirage aléatoire pour déterminer le type de pierre
                    int stoneRoll = std::rand() % 20;  // Un tirage entre 0 et 19

                    StoneType stoneType;
                    if (stoneRoll < 10) {
                        stoneType = StoneType::Stone;
                    }
                    else if (stoneRoll < 14) {
                        stoneType = StoneType::Coal;   
                    }
                    else if (stoneRoll < 16) {
                        stoneType = StoneType::Iron;  
                    }
                    else if (stoneRoll < 17) {
                        stoneType = StoneType::Gold; 
                    }
                    else {
                        stoneType = StoneType::Diamond; 
                    }

                    // Crée l'objet Flore avec le type de pierre choisi
                    Flore* T = CreateEntity<Flore>("Rock_0012");  // L'image de base peut être modifiée plus bas
                    T->SetOrigin(0.5, 0.5);
                    T->SetPosition(Tile.sprite.getPosition().x + 25, Tile.sprite.getPosition().y+10);
                    T->SetSize(100, 100);
                    T->AddAABBHitbox();
                    T->SetHitboxSize(25, 25);
                    T->SolidHitbox();
                    T->SetFloreLife(std::rand()% 3 + 1);  
                    T->Layout = 4;  
                    T->mStoneType = stoneType;  
                    T->mFloreType = FloreType::Stone;
                    T->UpdateImagetype();

                    lFlore.push_back(T);

                    Tile.type = TileType::Stone;
                    Tile.AddEntityOnTile(T);
                }
            }
            else
            {
                Tile.type = TileType::Empty;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        UI* U = CreateEntity<UI>("B_0000");
        U->mTag = GameManager::Tag::tUI;
        U->SetOrigin(0.5f, 0.5f);
        U->SetSize(50, 50);
        U->Layout = 5;
        if (i == 0)
        {
            U->pos = {GetWindowWidth() - 100 - 40, GetWindowHeight() - 100};
        }
        if (i == 1)
        {
            U->pos = { GetWindowWidth() - 100, GetWindowHeight() - 100 - 40 };
        }
        if (i == 2)
        {
            U->pos = { GetWindowWidth() - 100 + 40, GetWindowHeight() - 100 };
        }
        if (i == 3)
        {
            U->pos = { GetWindowWidth() - 100, GetWindowHeight() - 100 + 40 };
        }
        lPlayerModeUi.push_back(U);
    }

    float sizeX = 5;
    float sizeY = 5;
}

void SceneEloulou::OnEvent(const sf::Event& event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (!KeyEscPressed) {
            std::cout << "Retour Menu" << std::endl;
            GameManager::Get()->LaunchScene<S0Menu>();
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (lPlayer->mMode != PlayerMode::Attack)
        {
            lPlayer->ActionPoint = { lBuild->GetBuildPosition().x, lBuild->GetBuildPosition().y };
            lPlayer->ActionTile = { lBuild->GetBuildPosition().x / 50,lBuild->GetBuildPosition().y / 50 };

        }
        if (lPlayer->mMode != PlayerMode::Hand)
        {

        }
    }

    HandleModeChange(sf::Keyboard::Num1, Key1Pressed, PlayerMode::Pickaxe, 0);
    HandleModeChange(sf::Keyboard::Num2, Key2Pressed, PlayerMode::Dig, 1);
    HandleModeChange(sf::Keyboard::Num3, Key3Pressed, PlayerMode::Axe, 2);
    HandleModeChange(sf::Keyboard::Num4, Key4Pressed, PlayerMode::Fish, 3);
}

void SceneEloulou::addHole()
{
    Tile* T = &map->lTile[(lPlayer->ActionTile.y * map->width) + lPlayer->ActionTile.x];

    if (T->type == TileType::Hole || T->type == TileType::Empty) {}
    else {return;}

    if (T->type == TileType::Hole)
    {
        for (auto FloreOnTile : T->GetEntityOnTile())
        {
            FloreOnTile->Destroy();
        }
        T->type = TileType::Empty;
    }
    else {
        Hole* H = CreateEntity<Hole>("soil_00");
        map->lTile[(lPlayer->ActionTile.y * map->width) + lPlayer->ActionTile.x].type = TileType::Hole;
        H->Adresse = { static_cast<int>(lPlayer->ActionTile.x),  static_cast<int>(lPlayer->ActionTile.y) };
        H->SetPosition(lPlayer->ActionPoint.x, lPlayer->ActionPoint.y);
        H->SetSize(50, 50);
        H->Layout = 3;
        T->AddEntityOnTile(H);
        T->type = TileType::Hole;
        lHole.push_back(H);
        std::cout << lHole.size() << std::endl;
    }
}

void SceneEloulou::addVegetables()
{
    
}

void SceneEloulou::cutTree()
{
    Tile* T = &map->lTile[(lPlayer->ActionTile.y * map->width) + lPlayer->ActionTile.x];

    if (T->type == TileType::Tree) {}
    else { return; }


    for (auto EOT : T->GetEntityOnTile())
    {
        Flore* F = dynamic_cast<Flore*>(EOT);
        if (F)
        {
            F->HitFlore();
            break;
        }
    }


    lPlayer->HasAxe = false;
}

void SceneEloulou::mineStone()
{
    Tile* T = &map->lTile[(lPlayer->ActionTile.y * map->width) + lPlayer->ActionTile.x];

    if (T->type == TileType::Stone) {}
    else { return; }


    for (auto EOT : T->GetEntityOnTile())
    {
        if (EOT != nullptr) {
            Flore* F = dynamic_cast<Flore*>(EOT);
            if (F)
            {
                F->HitFlore();
                break;
            }
        }
        
    }


    lPlayer->HasAxe = false;
}

void SceneEloulou::HandleModeChange(sf::Keyboard::Key key, bool& keyPressed, PlayerMode mode, int uiIndex) {
    if (sf::Keyboard::isKeyPressed(key)) {
        if (!keyPressed) {
            keyPressed = true;
            if (lPlayer->mMode == mode)
                lPlayer->mMode = PlayerMode::Hand;
            else
                lPlayer->mMode = mode;

            // Mise à jour des images selon le mode actuel
            if (lPlayer->mMode == PlayerMode::Hand) {
                for (int i = 0; i < 4; i++) {
                    lPlayerModeUi[i]->SetImage("B_0000");
                }
            }
            else {
                for (int i = 0; i < 4; i++) {
                    if (i == uiIndex)
                        lPlayerModeUi[i]->SetImage("B_0001");
                    else
                        lPlayerModeUi[i]->SetImage("B_0000");
                }
            }
        }
    }
    else {
        keyPressed = false;
    }
}

void SceneEloulou::SetName() {
    SceneName = "SceneEloulou";
}

void SceneEloulou::Load()
{
}

void SceneEloulou::OnUpdate() {

    std::vector<Flore*> tempsClear;
    for (auto e : lFlore) {
        if (!e->mToDestroy || e != nullptr) {
            tempsClear.push_back(e);
        }
    }
    lFlore.clear();
    lFlore = tempsClear;

    lBuild->ChooseTile();
    /*for (size_t i = 0; i < 2; i++)
    {
        lTree[i]->AddRotation(10);
    }*/

    if (lPlayer->mMode == PlayerMode::Attack || lPlayer->mMode == PlayerMode::Hand)
    {
        lBuild->SelectedTileImg->isHide = true;
    }
    else
    {
        lBuild->SelectedTileImg->isHide = false;
    }


    //Ocean->UpdateWater();
}

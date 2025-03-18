#include "pch.h"
#include "S0Menu.h"
#include "SceneChevalier.h"
#include <fstream>
#include "TileMap.h"

void SceneChevalier::OnInitialize()
{

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

    std::vector<std::vector<char*>> lTileDoc;

    bool LoadLevel = true;

    for (int i = 0; LoadLevel; i++) {
        std::string fileName = "../../../res/mapPatern/mapVille.txt";
        std::ifstream file(fileName);

        std::cout << "Lecture de : " << fileName << std::endl;

        if (!file.is_open()) {
            std::cout << "Erreur : Impossible d'ouvrir le fichier :" << fileName << std::endl;;
            LoadLevel = false;
        }
        else {

            std::string line;
            while (std::getline(file, line)) {
                std::vector<char*> fileContent;

                for (char c : line) {
                    char* transform = new char[2];
                    transform[0] = c;
                    transform[1] = '\0';
                    fileContent.push_back(transform);
                }

                lTileDoc.push_back(fileContent);
            }
            file.close();
            LoadLevel = false;
        }
    }

    float size = GameManager::Get()->Window->getSize().x/20;

    for (auto line : lTileDoc) {
        std::vector<sf::Sprite> lineOfTile;
        for (auto tileType : line) { // size 20 resize by screen 
            
            sf::Texture tileOfMap = GameManager::Get()->AssetMana.GetTexture("0");
            sf::Sprite tile(tileOfMap);
            tile.setScale(size, size);
            if (tile.getTexture() == nullptr) {
                std::cerr << "Le sprite n'a pas de texture !" << std::endl;
            }
            lineOfTile.push_back(tile);
        }
        /*map.push_back(lineOfTile);*/
    }
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
}

void SceneChevalier::OnUpdate()
{
}

void SceneChevalier::SetName()
{
}

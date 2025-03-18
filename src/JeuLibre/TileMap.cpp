#include "pch.h"
#include "TileMap.h"
#include <fstream>


void TileMap::OnUpdate() {
}


void TileMap::create(std::string path) {

    float size = GameManager::Get()->Window->getSize().x / 28;
    float posX = 0;
    float posY = 0;

    std::string fileName = "../../../res/mapPatern/" + path + ".txt";
    std::ifstream file(fileName);

    std::cout << "Lecture de : " << fileName << std::endl;

    if (!file.is_open()) {
        std::cout << "Erreur : Impossible d'ouvrir le fichier :" << fileName << std::endl;
    }

    else {

        std::string line;
        while (std::getline(file, line)) {
            std::vector<sf::Sprite> fileContent;

            for (char c : line) {
                char* transform = new char[2];
                transform[0] = c;
                transform[1] = '\0';

                sf::Sprite tSprite;
                tSprite.setTexture(GameManager::Get()->AssetMana.GetTexture(transform));
                tSprite.setScale(size, size);
                tSprite.setPosition(posX, posY);

                fileContent.push_back(tSprite);
                posX += size;
            }
            lSprite.push_back(fileContent);
            posY += size;
            posX = 0;
        }
        file.close();
    }
    GameManager::Get()->tileMap = this;

}
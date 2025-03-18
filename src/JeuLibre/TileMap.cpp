#include "pch.h"
#include "TileMap.h"
#include "GameManager.h"
#include <fstream>
#include <vector>
#include <iostream>

void TileMap::create(const std::string& path)
{
    float tileSize = GameManager::Get()->Window->getSize().x / 15.0f;
    float posX = 0;
    float posY = 0;

    std::string fileName = "../../../res/mapPatern/" + path + ".txt";
    std::ifstream file(fileName);

    std::cout << "Lecture de : " << fileName << std::endl;

    if (!file.is_open()) {
        std::cout << "Erreur : Impossible d'ouvrir le fichier : " << fileName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<Tile> lineTiles;
        for (char c : line) {
            std::string textureId(1, c);

            const sf::Texture& texture = GameManager::Get()->AssetMana.GetTexture(textureId);

            // Affichage de debug pour vérifier les valeurs
            std::cout << "Tile '" << c << "' à la position (" << posX << ", " << posY << ") avec tileSize " << tileSize
                << " et texture size (" << texture.getSize().x << ", " << texture.getSize().y << ")" << std::endl;

            Tile tile(c, texture, posX, posY, tileSize);
            lineTiles.push_back(tile);
            posX += tileSize;
        }
        tiles.push_back(lineTiles);
        posY += tileSize;
        posX = 0;
    }
    file.close();
}

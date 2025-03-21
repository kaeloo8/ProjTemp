#include "pch.h"
#include "TileMap.h"
#include "GameManager.h"
#include <fstream>
#include <vector>
#include <iostream>

void TileMap::create(const std::string& path)
{
     // Taille fixe des tiles
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
        posX = 0; // R�initialisation de X pour chaque ligne

        std::istringstream lineStream(line);
        std::string textureId;

        while (lineStream >> textureId) { // Extraction propre en ignorant les espaces
            const sf::Texture& texture = GameManager::Get()->AssetMana.GetTexture("TileMap_"+textureId);

            std::cout << texture.getSize().x << " : " << texture.getSize().y << std::endl;

            // V�rification que la texture est valide
            if (texture.getSize().x == 0 || texture.getSize().y == 0) {
                std::cout << "?? Erreur : Texture non charg�e pour l'ID '" << textureId << "'" << std::endl;
                continue;
            }

            // Ajout de la tile
            lineTiles.emplace_back(textureId, texture, posX, posY);
            posX += tileSize;
        }

        tiles.push_back(lineTiles);
        posY += tileSize;
    }
    file.close();
}

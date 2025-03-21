#include "pch.h"
#include "TileMap.h"
#include "GameManager.h"
#include <fstream>
#include <vector>
#include <iostream>

void TileMap::create(const std::string& path)
{
    float tileSize = 30.0f; // Taille fixe des tiles
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
        posX = 0; // Réinitialisation de X pour chaque ligne

        for (char c : line) {
            std::string textureId(1, c);
            const sf::Texture& texture = GameManager::Get()->AssetMana.GetTexture(textureId);

            // Vérification que la texture est valide
            if (texture.getSize().x == 0 || texture.getSize().y == 0) {
                std::cout << "?? Erreur : Texture non chargée pour l'ID '" << textureId << "'" << std::endl;
                continue;
            }

            // Debug : Afficher les infos de la tile

            lineTiles.emplace_back(c, texture, posX, posY);
            posX += tileSize;
        }

        tiles.push_back(lineTiles);
        posY += tileSize;
    }
    file.close();
}

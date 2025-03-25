#include "pch.h"
#include "TileMap.h"
#include "GameManager.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <random>

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
        posX = 0; // Réinitialisation de X pour chaque ligne

        std::istringstream lineStream(line);
        std::string textureId;

        while (lineStream >> textureId) { // Extraction propre en ignorant les espaces
            const sf::Texture& texture = GameManager::Get()->AssetMana.GetTexture("TileMap_"+textureId);

            std::cout << texture.getSize().x << " : " << texture.getSize().y << std::endl;

            // Vérification que la texture est valide
            if (texture.getSize().x == 0 || texture.getSize().y == 0) {
                std::cout << "?? Erreur : Texture non chargée pour l'ID '" << textureId << "'" << std::endl;
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

void TileMap::createD() {
    tiles.clear(); // Réinitialisation de la map

    const int roomWidth = 26;
    const int roomHeight = 14;
    const int tileSize = 50; // Taille des tiles

    // Nombre aléatoire de salles en X et Y (entre 3 et 5)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(3, 5);

    int cols = dist(gen);
    int rows = dist(gen);

    std::vector<std::vector<Room>> rooms(rows, std::vector<Room>(cols));

    // Génération des salles avec connexions aléatoires
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Room& room = rooms[i][j];
            room.x = j * roomWidth * tileSize;
            room.y = i * roomHeight * tileSize;

            room.doors[0] = (i > 0) ? (rand() % 2) : false; // Haut
            room.doors[1] = (i < rows - 1) ? (rand() % 2) : false; // Bas
            room.doors[2] = (j > 0) ? (rand() % 2) : false; // Gauche
            room.doors[3] = (j < cols - 1) ? (rand() % 2) : false; // Droite

            if (i > 0 && rooms[i - 1][j].doors[1]) room.doors[0] = true;
            if (j > 0 && rooms[i][j - 1].doors[3]) room.doors[2] = true;
        }
    }

    // Création des tiles en fonction des salles
    for (const auto& row : rooms) {
        for (const auto& room : row) {
            for (int y = 0; y < roomHeight; ++y) {
                std::vector<Tile> lineTiles;
                for (int x = 0; x < roomWidth; ++x) {
                    std::string textureId = "000" + std::to_string(std::rand() % 3 + 4);

                    if (y == 0 || y == roomHeight - 1 || x == 0 || x == roomWidth - 1)
                        textureId = "000" + std::to_string(std::rand() % 4);

                    // Placement des portes sur 2 tiles
                    if (room.doors[0] && y == 0 && (x == roomWidth / 2 || x == roomWidth / 2 - 1)) textureId = "0008";
                    if (room.doors[1] && y == roomHeight - 1 && (x == roomWidth / 2 || x == roomWidth / 2 - 1)) textureId = "0008";
                    if (room.doors[2] && x == 0 && (y == roomHeight / 2 || y == roomHeight / 2 - 1)) textureId = "0008";
                    if (room.doors[3] && x == roomWidth - 1 && (y == roomHeight / 2 || y == roomHeight / 2 - 1)) textureId = "0008";

                    const sf::Texture& texture = GameManager::Get()->AssetMana.GetTexture("DonjonTile_" + textureId);
                    lineTiles.emplace_back(textureId, texture, room.x + x * tileSize, room.y + y * tileSize);
                }
                tiles.push_back(lineTiles);
            }
        }
    }
}


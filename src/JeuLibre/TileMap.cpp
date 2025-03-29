#pragma once
#include "pch.h"
#include "TileMap.h"
#include "GameManager.h"
#include <fstream>
#include <random>
#include <stack>
#include <algorithm>

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
            const sf::Texture& texture = GameManager::Get()->AssetMana.GetTexture("TileMap_" + textureId);

            std::cout << texture.getSize().x << " : " << texture.getSize().y << std::endl;

            // Vérification que la texture est valide
            if (texture.getSize().x == 0 || texture.getSize().y == 0) {
                std::cout << "?? Erreur : Texture non chargée pour l'ID '" << textureId << "'" << std::endl;
                continue;
            }

            // Création de la tile
            Tile tile(textureId, texture, posX, posY);

            tile.type = TileType::Empty;

            lineTiles.push_back(std::move(tile));
            posX += tileSize;
        }

        tiles.push_back(std::move(lineTiles));
        posY += tileSize;
    }
    file.close();
}

void TileMap::createD() {
    tiles.clear(); // Réinitialisation de la map

    const int roomWidth = 26;
    const int roomHeight = 14;
    const int tileSize = 50; // Taille des tiles

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(3, 5);

    int cols = dist(gen);
    int rows = dist(gen);

    std::vector<std::vector<Room>> rooms(rows, std::vector<Room>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Room& room = rooms[i][j];
            room.x = j * roomWidth * tileSize;
            room.y = i * roomHeight * tileSize;
            room.doors[0] = room.doors[1] = room.doors[2] = room.doors[3] = false;
        }
    }

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::stack<std::pair<int, int>> stack;
    stack.push({ 0, 0 });
    visited[0][0] = true;

    while (!stack.empty()) {
        auto [i, j] = stack.top();
        stack.pop();

        std::vector<std::pair<int, int>> neighbors;
        if (i > 0 && !visited[i - 1][j]) neighbors.push_back({ i - 1, j });
        if (i < rows - 1 && !visited[i + 1][j]) neighbors.push_back({ i + 1, j });
        if (j > 0 && !visited[i][j - 1]) neighbors.push_back({ i, j - 1 });
        if (j < cols - 1 && !visited[i][j + 1]) neighbors.push_back({ i, j + 1 });

        std::shuffle(neighbors.begin(), neighbors.end(), gen);

        for (auto [ni, nj] : neighbors) {
            if (!visited[ni][nj]) {
                if (ni == i - 1) { rooms[i][j].doors[0] = true; rooms[ni][nj].doors[1] = true; }
                if (ni == i + 1) { rooms[i][j].doors[1] = true; rooms[ni][nj].doors[0] = true; }
                if (nj == j - 1) { rooms[i][j].doors[2] = true; rooms[ni][nj].doors[3] = true; }
                if (nj == j + 1) { rooms[i][j].doors[3] = true; rooms[ni][nj].doors[2] = true; }

                visited[ni][nj] = true;
                stack.push({ ni, nj });
            }
        }
    }

    for (const auto& row : rooms) {
        for (const auto& room : row) {
            for (int y = 0; y < roomHeight; ++y) {
                std::vector<Tile> lineTiles;
                for (int x = 0; x < roomWidth; ++x) {
                    std::string textureId = "000" + std::to_string(std::rand() % 3 + 7);

                    if (y == 0)
                        textureId = "0004";
                    if (y == roomHeight - 1)
                        textureId = "0005";
                    if (x == 0 ) 
                        textureId = "0000";
                    if(x == roomWidth - 1)
                        textureId = "0003";



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

void TileMap::UpdateWater()
{
    static float animationTimer = 0.f;
    animationTimer += GameManager::Get()->GetDeltaTime();

    if (animationTimer >= WaterSpeed) {
        for (auto& line : tiles) {
            for (auto& tile : line) {
                // Pour chaque cycle, vérifier si l'ID de la tile est dans le cycle
                for (const auto& cycle : animCycles) {
                    auto it = std::find(cycle.begin(), cycle.end(), tile.id);
                    if (it != cycle.end()) {
                        int index = std::distance(cycle.begin(), it);
                        index = (index + 1) % cycle.size();
                        tile.id = cycle[index];
                        // Met à jour la texture en fonction du nouvel ID
                        tile.sprite.setTexture(GameManager::Get()->AssetMana.GetTexture("TileMap_" + tile.id));
                        break; // On passe à la tile suivante dès qu'un cycle est trouvé
                    }
                }
            }
        }
        animationTimer = 0.f;
    }
}
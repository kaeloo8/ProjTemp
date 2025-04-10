#pragma once
#include "pch.h"
#include "TileMap.h"
#include "GameManager.h"
#include <fstream>
#include <random>
#include <stack>
#include <algorithm>

void Tile::AddEntityOnTile(Entity* e) {
    EntityOnTile.push_back(e);
}

std::vector<Entity*> Tile::GetEntityOnTile() {
    return EntityOnTile;
}

void TileMap::create(const std::string& path)
{
    // Taille fixe des tiles
    float posX = 0;
    float posY = 0;
    int tileSize = 50;

    lTile.clear(); // Réinitialisation de la map

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
        width = 0;

        while (lineStream >> textureId) { // Extraction propre en ignorant les espaces
            const sf::Texture& texture = GameManager::Get()->AssetMana.GetTexture("TileMap_" + textureId);

            // Vérification que la texture est valide
            if (texture.getSize().x == 0 || texture.getSize().y == 0) {
                std::cout << "?? Erreur : Texture non chargée pour l'ID '" << textureId << "'" << std::endl;
                continue;
            }

            // Création de la tile
            Tile tile(textureId, texture, posX, posY);

            if (textureId == "0174")
            {
                tile.type = TileType::Swimmable;
            }
            else if (textureId == "0000")
            {
				tile.type = TileType::Spawnable;
            }
            else 
            {
                tile.type = TileType::Empty;
            }

            lTile.push_back(tile);
            posX += tileSize;
            width++;

        }
        posY += tileSize;
        height++;
    }
    file.close();
}

void TileMap::createD() {
    lTile.clear(); // Réinitialisation de la map

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

    // On définit la taille totale de la tilemap
    int mapWidth = rooms[0].size() * roomWidth;   // Nombre total de tiles en X
    int mapHeight = rooms.size() * roomHeight;    // Nombre total de tiles en Y

    width = mapWidth;
    height = mapHeight;

    int px = 0;
    int py = 0;

    // On initialise la tilemap vide avec des lignes de la bonne taille
    std::vector<Tile> ti(std::vector<Tile>(mapWidth*mapHeight));

    // Placement des tiles
    for (size_t rowIdx = 0; rowIdx < rooms.size(); ++rowIdx) {
        for (size_t colIdx = 0; colIdx < rooms[rowIdx].size(); ++colIdx) {
            const Room& room = rooms[rowIdx][colIdx];  // Salle actuelle

            for (int y = 0; y < roomHeight; ++y) {
                for (int x = 0; x < roomWidth; ++x) {
                    std::string textureId = "000" + std::to_string(std::rand() % 4 + 6);

                    if (y == 0) textureId = "0004";
                    if (y == roomHeight - 1) textureId = "0005";
                    if (x == 0) textureId = "0000";
                    if (x == roomWidth - 1) textureId = "0003";

                    // Placement des portes
                    if (room.doors[0] && y == 0 && (x == roomWidth / 2 || x == roomWidth / 2 - 1)) textureId = "0008";
                    if (room.doors[1] && y == roomHeight - 1 && (x == roomWidth / 2 || x == roomWidth / 2 - 1)) textureId = "0008";
                    if (room.doors[2] && x == 0 && (y == roomHeight / 2 || y == roomHeight / 2 - 1)) textureId = "0008";
                    if (room.doors[3] && x == roomWidth - 1 && (y == roomHeight / 2 || y == roomHeight / 2 - 1)) textureId = "0008";

                    int globalX = (colIdx * roomWidth) + x;
                    int globalY = (rowIdx * roomHeight) + y;

                    const sf::Texture& texture = GameManager::Get()->AssetMana.GetTexture("DonjonTile_" + textureId);
                    Tile T(textureId, texture, globalX * tileSize, globalY * tileSize);
                    T.type = (textureId == "0000" || textureId == "0001" || textureId == "0002" || textureId == "0003" || textureId == "0004" || textureId == "0005")
                        ? TileType::Solid
                        : TileType::Empty;

                    // CORRECTION ICI : utilisation de mapWidth au lieu de roomWidth
                    ti[(mapWidth * globalY) + globalX] = T;

                }
            }
        }
    }

    // Debug : vérifier la taille de la tilemap
    std::cout << "Tilemap size: " << ti.size() << std::endl;

    lTile = ti;
}

void TileMap::UpdateWater()
{
    float WaterSpeed = 0.5f;
    static float animationTimer = 0.f;
    animationTimer += GameManager::Get()->GetDeltaTime();

    if (animationTimer >= WaterSpeed) {
        for (auto& tile : lTile) {
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
        
        animationTimer = 0.f;
    }
}


Tile::Tile() {
    id = "";
    sprite.setTexture(GameManager::Get()->GetTexture("0"));
    sprite.setScale(tileSize / sprite.getGlobalBounds().width, tileSize / sprite.getGlobalBounds().height);
    sprite.setPosition(0, 0);
}

Tile::Tile(const std::string& tileId, const sf::Texture& texture, float x, float y) {
    id = tileId;
    sprite.setTexture(texture);
    sprite.setScale(tileSize / texture.getSize().x, tileSize / texture.getSize().y);
    sprite.setPosition(x, y);
}

void TileMap::AddEntityOnTile(int pos, Entity* e) {
    if (pos < 0 || pos >= static_cast<int>(lTile.size())) {
        return;
    }
    lTile[pos].EntityOnTile.push_back(e);
}




std::vector<Var> TileMap::GetEntityOnTile(int pos) {
    if (pos >= lTile.size()) {
        return {};
    }

    std::vector<Var> result;
    for (Entity* e : lTile[pos].EntityOnTile) {
        if (auto f = dynamic_cast<Flore*>(e)) {
            result.push_back(f);
        }
        else if (auto h = dynamic_cast<Hole*>(e)) {
            result.push_back(h);
        }
        else {
            result.push_back(e);
        }
    }

    return result;
}

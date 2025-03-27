#pragma once
#include "Entity.h"
#include "Collider.h"
#include <vector>
#include <SFML/Graphics.hpp>

enum class TileType {
    Empty,
    Full,
    Solid
};

struct Tile {
public:
    float tileSize = 50;
    sf::Sprite sprite;
    std::string id;
    TileType type;
    Collider* Tilecollider;

    Tile(const std::string& tileId, const sf::Texture& texture, float x, float y)
        : id(tileId)
    {
        sprite.setTexture(texture);
        sprite.setScale(tileSize / texture.getSize().x, tileSize / texture.getSize().y);
        sprite.setPosition(x, y);
        AddAABBHitbox();
    }
    void AddAABBHitbox();
};

struct Room {
    int x, y;
    bool doors[4]; 
};

class TileMap : public Entity {
public:

    float WaterSpeed = 0.5f;
    float tileSize = 50;
    std::vector<std::vector<Tile>> tiles;

    std::vector<std::vector<std::string>> animCycles = {
        { "0208", "0209", "0210", "0211" },
        { "0212", "0213", "0214", "0215" },
        { "0216", "0217", "0218", "0219" },
        { "0220", "0221", "0222", "0223" }
    };

    std::vector<std::string> SolidTile = {"0174"};

    void create(const std::string& path);
    void createD();
    void UpdateWater();

};

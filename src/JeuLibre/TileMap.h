#pragma once
#include "Entity.h"
#include <vector>
#include <SFML/Graphics.hpp>

struct Tile {
public:
    float tileSize = 50;
    sf::Sprite sprite;
    std::string id;

    Tile(const std::string& tileId, const sf::Texture& texture, float x, float y)
        : id(tileId)
    {
        sprite.setTexture(texture);
        sprite.setScale(tileSize / texture.getSize().x, tileSize / texture.getSize().y);
        sprite.setPosition(x, y);
    }
};

struct Room {
    int x, y;
    bool doors[4]; 
};

class TileMap : public Entity {
public:

    float tileSize = 50;
    std::vector<std::vector<Tile>> tiles;

    void create(const std::string& path);
    void createD();
};

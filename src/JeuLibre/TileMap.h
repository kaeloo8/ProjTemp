#pragma once
#include "Entity.h"
#include <vector>
#include <SFML/Graphics.hpp>

struct Tile {
    sf::Sprite sprite;
    char id; 

    Tile(char tileId, const sf::Texture& texture, float x, float y, float tileSize)
        : id(tileId)
    {
        sprite.setTexture(texture);
        sprite.setScale(tileSize / texture.getSize().x, tileSize / texture.getSize().y);

        sprite.setPosition(x, y);
    }
};

class TileMap : public Entity {
public:
    std::vector<std::vector<Tile>> tiles;

    void create(const std::string& path);
};

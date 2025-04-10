#pragma once
#include <variant>
#include "Entity.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Flore.h"
#include "Hole.h"


using Var = std::variant<Entity*, Flore*, Hole*>;

enum class TileType {
    //collide
    Empty,
    Solid,
    Swimmable,
    Repulsif,

    //Elements
    Wall,
    Barrier,
    Vegetal,
    Hole,
    HoleWithVegetables,
    Tree,
    Stone,
	Water,
    FishingSpot,
    Spawnable,
    Trap,
    Nothing
};

inline std::ostream& operator<<(std::ostream& os, const TileType& type) {
    switch (type) {
    case TileType::Empty: os << "Empty"; break;
    case TileType::Solid: os << "Solid"; break;
    case TileType::Vegetal: os << "Vegetal"; break;
    case TileType::Nothing: os << "Nothing"; break;
    }
    return os;
}

struct Tile {
public:
    float tileSize = 50;
    sf::Sprite sprite;
    std::string id;

    std::vector<Entity*> EntityOnTile;

    TileType type;

    Tile();
    Tile(const std::string& tileId, const sf::Texture& texture, float x, float y);
    void AddEntityOnTile(Entity* e);
    std::vector<Entity*> GetEntityOnTile();
};

struct Room {
    int x, y;
    bool doors[4]; 
};

class TileMap : public Entity {
public:
    int width;
    int height;

    std::vector<Tile> lTile;

    std::vector<std::vector<std::string>> animCycles = {
        { "0208", "0209", "0210", "0211" },
        { "0212", "0213", "0214", "0215" },
        { "0216", "0217", "0218", "0219" },
        { "0220", "0221", "0222", "0223" }
    };

    void create(const std::string& path);
    void createD();
    void UpdateWater();
    void AddEntityOnTile(int pos, Entity* e);

    std::vector<Var> GetEntityOnTile(int pos);
};
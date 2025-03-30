#pragma once
#include "Player.h"
#include "TileMap.h"
#include "Pointer.h"
#include <vector>


class BuildSystem : public Entity
{
public:
    Entity* SelectedTileImg;

    bool BuildingMode;

    Player* PlayerReference;
    Tile* SelectedTile;
    Pointer* PointerReference;

    std::vector<std::vector<Tile>> tiles; 
    int Tilex;
    int Tiley;

    BuildSystem();
    ~BuildSystem();

    sf::Vector2f GetBuildPosition();

    void SetPlayer(Player* _player);
    void SetPointer(Pointer* _pointer);
    void ChooseTile();
};
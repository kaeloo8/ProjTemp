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
	TileMap* Map;
    Pointer* PointerRef;

    int Tilex;
    int Tiley;

    BuildSystem();
    ~BuildSystem();

    sf::Vector2f GetBuildPosition();

	void SetTileMap(TileMap* _tilemap);
    void SetPlayer(Player* _player);
    void SetPoiter(Pointer* _Pointer);
    Tile* GetTileHover();
    void ChooseTile();
};
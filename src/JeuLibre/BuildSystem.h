#pragma once
#include "Player.h"
#include "TileMap.h"
#include "Pointer.h"

class BuildSystem
{
public:
    bool BuildingMode;

    Player* Player;
    Tile* SelectedTile;
    Pointer* Pointer;

    BuildSystem();
    ~BuildSystem();


};


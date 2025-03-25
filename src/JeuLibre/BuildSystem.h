#pragma once
#include "Player.h"
#include "TileMap.h"
#include "Pointer.h"
#include <vector>

class BuildSystem : public Entity
{
public:
    bool BuildingMode;

    Player* PlayerReference;
    Tile* SelectedTile;
    Pointer* PointerReference;
    std::vector<std::vector<Tile>> tiles; // Ajout du vecteur de tiles
    int Tilex;
    int Tiley;

    BuildSystem();
    ~BuildSystem();

    void SetPlayer(Player* _player);
    void SetPointer(Pointer* _pointer);
    void ChooseTile();
};

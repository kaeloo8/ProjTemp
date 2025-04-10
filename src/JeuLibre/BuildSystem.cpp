#include "pch.h"
#include "BuildSystem.h"

BuildSystem::BuildSystem()
{
    SelectedTileImg = CreateEntity<Entity>("CursorSelector");
    SelectedTileImg->Layout = 10;
    SelectedTileImg->SetOrigin(0, 0);
    SelectedTileImg->SetSize(50,50);
    BuildingMode = true;
}

BuildSystem::~BuildSystem()
{
}

sf::Vector2f BuildSystem::GetBuildPosition()
{
    return SelectedTileImg->GetPosition();
}

void BuildSystem::SetTileMap(TileMap* _tilemap)
{
	Map = _tilemap;
}

void BuildSystem::SetPlayer(Player* _player)
{
	PlayerReference = _player;
}

void BuildSystem::SetPoiter(Pointer* _Pointer) {
    PointerRef = _Pointer;
}


void BuildSystem::ChooseTile()
{
    if (!PlayerReference) {
        return;
    }

    if (Map == nullptr)
    {
        return;
    }

    sf::Vector2f pointerPos = PointerRef->worldPos;

    float tileSize = 50;
    int tileX = pointerPos.x / tileSize;
    int tileY = pointerPos.y / tileSize;

    if (tileY >= 0 && tileY <= Map->height && tileX >= 0 && tileX <= Map->width) {
        Tilex = tileX;
        Tiley = tileY;
    }
    else {
        std::cout << "Aucune tile trouvée sous le pointeur !" << std::endl;
    }

    Tile tile = Map->lTile[Tilex + (Tiley * Map->width)];

    SelectedTile = &tile;

    sf::Vector2i pos(tile.sprite.getPosition().x, tile.sprite.getPosition().y);

    SelectedTileImg->SetPosition(pos.x, pos.y);

	if (BuildingMode)
	{
        SelectedTileImg->isHide = false;
    }
	else
	{
        SelectedTileImg->isHide = true;
    }
}

Tile* BuildSystem::GetTileHover() {
    return SelectedTile;
}
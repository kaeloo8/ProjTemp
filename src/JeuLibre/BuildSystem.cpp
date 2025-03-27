#include "pch.h"
#include "BuildSystem.h"

BuildSystem::BuildSystem()
{
    SelectedTileImg = CreateEntity<Entity>("CursorSelector");
    SelectedTileImg->Layout = 10;
    SelectedTileImg->SetSize(50,50);
}

BuildSystem::~BuildSystem()
{
}

sf::Vector2f BuildSystem::GetBuildPosition()
{
    return SelectedTileImg->GetPosition();;
}

void BuildSystem::SetPlayer(Player* _player)
{
	PlayerReference = _player;
}

void BuildSystem::SetPointer(Pointer* _pointer)
{
	PointerReference = _pointer;
}

void BuildSystem::ChooseTile()
{
    if (!PointerReference || !PlayerReference) {
        return; // Vérifie si le pointeur et le joueur sont valides.
    }
    sf::Vector2f pointerPos = PointerReference->worldPos;
    float tileSize = 50;
    //std::cout << pointerPos.x << " : " << pointerPos.y << std::endl;
    int tileX = pointerPos.x / tileSize;
    int tileY = pointerPos.y / tileSize;

    // Vérifier que les indices sont valides dans le vecteur de tile
    if (tileY >= 0 && tileY <= 39 && tileX >= 0 && tileX <= 63) {
        Tilex = tileX;
        Tiley = tileY;
        std::cout << "Tile sélectionnée : " << Tilex << "." << Tiley << std::endl;

        if (GameManager::Get()->GetTileMap(1)) {
            auto& tile = GameManager::Get()->GetTileMap(0)->tiles[Tiley][Tilex];
            SelectedTileImg->SetPosition(tile.sprite.getPosition().x, tile.sprite.getPosition().y);
        }

    }
    else {
        std::cout << "Aucune tile trouvée sous le pointeur !" << std::endl;
    }
}
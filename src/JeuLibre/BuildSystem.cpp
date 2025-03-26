#include "pch.h"
#include "BuildSystem.h"

BuildSystem::BuildSystem()
{
    SelectedTileImg = CreateEntity<Entity>("3");
    SelectedTileImg->Layout = 10;
    SelectedTileImg->SetSize(50,50);
}

BuildSystem::~BuildSystem()
{
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
    //std::cout << tileX << std::endl;
    //std::cout << tileY << std::endl;

    // Vérifier que les indices sont valides dans le vecteur de tile
    if (tileY >= 0 && tileY <= 19 && tileX >= 0 && tileX <= 29) {
        Tilex = tileX;
        Tiley = tileY;
        std::cout << "Tile sélectionnée : " << Tilex << "." << Tiley << std::endl;
        SelectedTileImg->SetPosition(GameManager::Get()->GetTilemap()->tiles[Tiley][Tilex].sprite.getPosition().x, GameManager::Get()->GetTilemap()->tiles[Tiley][Tilex].sprite.getPosition().y);
    }
    else {
        std::cout << "Aucune tile trouvée sous le pointeur !" << std::endl;
    }
}
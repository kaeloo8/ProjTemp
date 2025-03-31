#include "pch.h"
#include "Pointer.h"
#include "GameManager.h"

Pointer::Pointer() {
    Win = GameManager::Get()->GetWindow();
    SetOrigin(0, 0);
    SetTag(GameManager::Tag::tPointer);
}

void Pointer::OnUpdate() {
    if (!Win || !Win->isOpen()) return;
    sf::Vector2i mousePosPixel = sf::Mouse::getPosition(*Win);

    // Convertir la position en coordonnées monde en tenant compte de la View
    worldPos = Win->mapPixelToCoords(mousePosPixel, Win->getView());

    ChangeI("Pointer");

    SetPosition(worldPos.x, worldPos.y, 0.5);
}


void Pointer::ChangeI(const char* path) {
    sf::Vector2f s1 = { mSprite.getGlobalBounds().width, mSprite.getGlobalBounds(). height};
    mSprite.setTexture(GameManager::Get()->AssetMana.GetTexture(path));
    mSprite.setScale((Win->getSize().x * 0.12) / 100, (Win->getSize().x * 0.12) / 100); // pour etre sur que l'image ne soit ni trop grand ni trop petit (je sait pas si sa conserve la taille quand on switch de texture) 
}

void Pointer::OnCollision(Entity* pOther) {

    if (pOther->mTag != GameManager::Tag::tHoverable) {
        ChangeI("Pointer");
        return;
    }
    ChangeI("Pointer_Click");

    
}

#pragma once
#include "Entity.h"
#include "S0Menu.h"

class UI : public Entity
{
    sf::Font mFont;
    sf::Sprite mImage;
    sf::Sprite mHoverImage;
    Pointer* mPointer;

public:
    UI();
    void HandleClick(float mouseX, float mouseY);
    void Open();
    void Close();
    void SetPointer(Pointer* _pointer);

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;

};
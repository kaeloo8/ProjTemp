#pragma once
#include "Entity.h"
#include "S0Menu.h"

class UI : public Entity
{
    sf::Font mFont;
    sf::Sprite mImage;
    sf::Sprite mHoverImage;
    sf::RectangleShape background;
    sf::Text title;
    sf::Text closeText;
    Pointer* mPointer;
    Entity* mParent = nullptr;

    float mGapX = 0;
    float mGapY = 0;


public:
    
    UI();

    void SetPointer(Pointer* _pointer);
    void HangToEntity(Entity* _parent);

    bool HandleClick(float mouseX, float mouseY);
    void Open();
    void Close();

    void GapX(float X);
    void GapY(float Y);
    void SetGap(float X, float Y);

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;

};
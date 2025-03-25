#pragma once
#include "Entity.h"
#include "S0Menu.h"
#include "Pointer.h"

class UI : public Entity
{
    sf::Font mFont;

    sf::Sprite mDefaultImage;
    std::string cDefaultImage;

    sf::Sprite mHoverImage;
    std::string cHoverImage;

    sf::RectangleShape background;
    
    sf::Text title;
    sf::Text closeText;
    Pointer* mPointer;
    Entity* mParent = nullptr;

    float mGapX = 0;
    float mGapY = 0;



public:
    
    UI();

    bool IsClickable;

    void SetPointer(Pointer* _pointer);
    void HangToEntity(Entity* _parent);

    bool HandleClick(float mouseX, float mouseY);
    bool HandleClick(sf::Vector2f MousePos);
    bool HandleHover(sf::Vector2f MousePos);
    void Open();
    void Close();

    void GapX(float X);
    void GapY(float Y);
    void SetGap(float X, float Y);

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;

};
#pragma once
#include "S0Menu.h"
#include "Pointer.h"
#include "Entity.h"
#include "Bouton.h"

class UI : public Entity
{
    // ???
    sf::Sprite mDefaultImage;
    std::string cDefaultImage;
    // ???
    sf::Sprite mHoverImage;
    std::string cHoverImage;

    struct element
    {
        Bouton* bEn;
        std::string NameI;
        int NumberI;
    };

    sf::Font mFont;

    Pointer* lPointer;

    std::vector<element> lBouton;

    float mGapX, mGapY = 0;

public:
    
    UI();

    bool IsClickable;

    bool HandleClick(float mouseX, float mouseY);
    bool HandleClick(sf::Vector2f MousePos);
    bool HandleHover(sf::Vector2f MousePos);

    void cBouton(sf::Vector2f pos, sf::Vector2f size, char* path);
    void cBouton(int x, int y, int sx, int sy, char* path);

    void GapX(float X);
    void GapY(float Y);
    void SetGap(float X, float Y);

    void SetPointer(Pointer* _pointer);
    
    void Open();
    void Close();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;

    void SetImage(const char* path) override;

};
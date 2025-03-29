#pragma once
#include "S0Menu.h"
#include "Pointer.h"
#include "Entity.h"

class UI : public Entity
{

    struct element
    {
        Entity* En;
        std::string NameI;
        int NumberI;
    };

    sf::Font mFont;

    Pointer* mPointer;

    std::vector<element> lBouton;

public:
    
    UI();

    void cBouton(sf::Vector2f pos, sf::Vector2f size, char* path);
    void cBouton(sf::Vector2f pos, int sx, int sy, char* path);
    void cBouton(int x, int y, sf::Vector2f size, char* path);
    void cBouton(int x, int y, int sx, int sy, char* path);

    void SetPointer(Pointer* _pointer);

    void Open();
    void Close();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;

    void SetImage(const char* path) override;

};
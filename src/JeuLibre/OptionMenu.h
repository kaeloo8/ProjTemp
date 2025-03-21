#pragma once
#include "UI.h"
#include "Entity.h"

class OptionMenu : public UI
{
    sf::Font mFont;
    sf::Sprite mImage;
    sf::Sprite mHoverImage;
    sf::RectangleShape background;
    sf::Text title;
    sf::Text closeText;

    bool MenuOpen = false;

public:
    OptionMenu();
    void HandleClick(float mouseX, float mouseY);
    void OpenOptionMenu();
    void CloseOptionMenu();
    void SetPointer(Pointer* _pointer);

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;
};


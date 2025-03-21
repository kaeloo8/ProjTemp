#include "pch.h"
#include "OptionMenu.h"

OptionMenu::OptionMenu()
{
    // Fond semi-transparent
    background.setSize({ 400, 300 });
    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setPosition(200, 150);
}

void OptionMenu::HandleClick(float mouseX, float mouseY)
{
}

void OptionMenu::OpenOptionMenu()
{
    MenuOpen = true;
    
}

void OptionMenu::CloseOptionMenu()
{
}

void OptionMenu::SetPointer(Pointer* _pointer)
{
}

void OptionMenu::OnUpdate()
{
    OpenOptionMenu();

}

void OptionMenu::OnCollision(Entity* pCollidedWith)
{
}

void OptionMenu::SetImage(const char* path)
{
}

#pragma once
#include "UI.h"
#include "Entity.h"

class OptionMenu : public UI
{
    std::vector<UI*> uiElements; 
    bool MenuOpen = false;

public:

    OptionMenu();
    
    bool HandleClick(float mouseX, float mouseY);
    bool IsOpen() const { return MenuOpen; }

    void AddUIElement(UI* element);
    void Open();
    void Close();
    
    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;
};


#pragma once
#include "UI.h"
#include "Entity.h"

class OptionMenu : public UI
{


    bool MenuOpen = false;

public:

    OptionMenu();
    
    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;
};


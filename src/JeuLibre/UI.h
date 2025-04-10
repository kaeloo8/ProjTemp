#pragma once

#include "Pointer.h"
#include "Entity.h"
#include "Bouton.h"
#include <map>

class UI : public Entity {
private:
    sf::Font mFont;
    Pointer* lPointer = nullptr;

    std::map<std::string, Bouton*> lBoutons;

    float mGapX = 0.0f;
    float mGapY = 0.0f;

public:
    sf::Vector2i pos;
    bool IsClickable = true;

    UI();

    // Création de boutons
    void CreateButton(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& name, const char* path, const char* pathHover);
    void CreateButton(float x, float y, int sx, int sy, const std::string& name, const char* path, const char* pathHover);

    // Positionnement des éléments UI
    void SetGap(float gapX, float gapY);
    void SetPointer(Pointer* pointer);

    // État des boutons
    bool IsHovering(const std::string& name) const;
    bool IsClicked(const std::string& name) const;
    Bouton* GetButton(const std::string& name);

    // Override Entity
    void OnUpdate() override;
    void OnCollision(Entity* other) override;
    void SetImage(const char* path) override;
};

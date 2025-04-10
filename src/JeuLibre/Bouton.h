#pragma once 
#include "Entity.h"

class Bouton : public Entity {
private:
    sf::Texture mDefaultTexture;
    sf::Texture mHoverTexture;

    bool mIsHovering = false;
    bool mIsClicked = false;


public:

    sf::Vector2f mLocalPos;

    Bouton();

    void SetTextures(const char* pathDefault, const char* pathHover);
    void SetLocalPosition(float x, float y);
    void SetLocalPosition(const sf::Vector2f& pos);
    sf::Vector2f GetLocalPosition() const;

    bool IsHovering() const;
    bool IsClicked() const;

    void OnUpdate() override;
    void OnCollision(Entity* other) override;

    // Reset click/hover manually if needed
    void ResetStates();
};

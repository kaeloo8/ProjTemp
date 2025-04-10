#include "pch.h"
#include "Bouton.h"
#include "GameManager.h"

Bouton::Bouton() {
    mLocalPos = { 0.f, 0.f };
    mIsHovering = false;
    mIsClicked = false;
}

void Bouton::SetTextures(const char* pathDefault, const char* pathHover) {
    mDefaultTexture = GameManager::Get()->GetTexture(pathDefault);
    mHoverTexture = GameManager::Get()->GetTexture(pathHover);
    mSprite.setTexture(mDefaultTexture);
}

void Bouton::SetLocalPosition(float x, float y) {
    mLocalPos = { x, y };
}

void Bouton::SetLocalPosition(const sf::Vector2f& pos) {
    mLocalPos = pos;
}

sf::Vector2f Bouton::GetLocalPosition() const {
    return mLocalPos;
}

bool Bouton::IsHovering() const {
    return mIsHovering;
}

bool Bouton::IsClicked() const {
    return mIsClicked;
}

void Bouton::ResetStates() {
    mIsClicked = false;
    mIsHovering = false;
    mSprite.setTexture(mDefaultTexture);
}

void Bouton::OnUpdate() {
    if (!mIsHovering) {
        mSprite.setTexture(mDefaultTexture);
    }
    mIsClicked = false;  // reset at the start of update, click only lasts one frame
    mIsHovering = false;
}

void Bouton::OnCollision(Entity* other) {
    if (other->mTag != GameManager::Tag::tPointer)
        return;

    mSprite.setTexture(mHoverTexture);
    mIsHovering = true;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        mIsClicked = true;
    }
}

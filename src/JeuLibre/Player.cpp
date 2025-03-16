#include "pch.h"
#include "Player.h"
#include "GameManager.h"   // Pour GetAssetManager() si besoin
#include <cstring>         // Pour strcmp

Player::Player()
    : mAnimator(nullptr)   // Pas d'animation par d�faut
{
    mAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_walk_strip8"),
        8,
        0.1f
    );
}

Player::~Player()
{
    if (mAnimator) {
        delete mAnimator;
        mAnimator = nullptr;
    }
}

void Player::OnUpdate()
{
    float dt = GetDeltaTime();

    // Si on a un Animator (mAnimator != nullptr)
    if (mAnimator)
    {
        // Si le joueur bouge (v�rifie mDirection.x / mDirection.y, ou ce que tu veux)
        if (mDirection.x != 0.f || mDirection.y != 0.f) {
            mAnimator->Update(dt); // On fait d�filer l'animation
        }
        else {
            mAnimator->Reset();   // On remet � z�ro si le joueur ne bouge plus
        }
    }
}

void Player::OnCollision(Entity* pCollidedWith)
{

}

void Player::SetImage(const char* path)
{

}

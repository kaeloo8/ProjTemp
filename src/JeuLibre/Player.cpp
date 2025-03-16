#include "pch.h"
#include "Player.h"
#include "GameManager.h"   // Pour GetAssetManager() si besoin
#include <cstring>         // Pour strcmp

Player::Player()
    : mAnimator(nullptr)   // Pas d'animation par défaut
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
        // Si le joueur bouge (vérifie mDirection.x / mDirection.y, ou ce que tu veux)
        if (mDirection.x != 0.f || mDirection.y != 0.f) {
            mAnimator->Update(dt); // On fait défiler l'animation
        }
        else {
            mAnimator->Reset();   // On remet à zéro si le joueur ne bouge plus
        }
    }
}

void Player::OnCollision(Entity* pCollidedWith)
{

}

void Player::SetImage(const char* path)
{

}

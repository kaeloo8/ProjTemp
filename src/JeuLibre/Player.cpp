#include "pch.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr), mState(PlayerState::Idle)
{
    // Cr�ation de l'animation de marche
    mWalkAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_walk_strip8"),
        8,    // nombre de frames walk
        0.1f  // dur�e par frame walk
    );

    // Cr�ation de l'animation idle
    mIdleAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_idle_strip9"),  // nom de la spritesheet idle
        9,    // nombre de frames idle
        0.2f  // dur�e par frame idle
    );

    // Cr�ation de l'animation sprint
    mSprintAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_run_strip8"), // nom de la spritesheet sprint
        8,    // nombre de frames sprint
        0.08f // dur�e par frame sprint
    );
    // Cr�ation de l'animation de dash
    mDashAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_roll_strip10"),  // nom de la spritesheet de roll/dash
        10,    // nombre de frames roll
        0.1f  // dur�e par frame roll
    );

}

Player::~Player()
{
    delete mWalkAnimator;
    delete mIdleAnimator;
    delete mSprintAnimator;
}
void Player::SetState(PlayerState state)
{
    if (mState != state)
    {
        mState = state;

        if (mState == PlayerState::Idle) {
            SetImage("base_idle_strip9");
            if (mIdleAnimator) mIdleAnimator->Reset();
        }
        else if (mState == PlayerState::Walking) {
            SetImage("base_walk_strip8");
            if (mWalkAnimator) mWalkAnimator->Reset();
        }
        else if (mState == PlayerState::Sprinting) {
            SetImage("base_run_strip8");
            if (mSprintAnimator) mSprintAnimator->Reset();
        }
        else if (mState == PlayerState::Dashing) {  
            SetImage("base_roll_strip10");
            if (mDashAnimator) mDashAnimator->Reset();
        }
    }
}

void Player::OnUpdate()
{
    float dt = GetDeltaTime();

    // G�rer les �tats en fonction de l'action du joueur
    if (isDashing) {
        SetState(PlayerState::Dashing);  // Si on est en train de dasher, passer � l'�tat Dashing
    }
    else if (isMoving) {
        if (isSprinting) {
            SetState(PlayerState::Sprinting);  // Si on court, passer � l'�tat Sprinting
        }
        else {
            SetState(PlayerState::Walking);  // Si on marche, passer � l'�tat Walking
        }
    }
    else {
        SetState(PlayerState::Idle);  // Si on ne bouge pas, passer � l'�tat Idle
    }

    // Mise � jour de l'animation en fonction de l'�tat actuel
    if (mState == PlayerState::Walking && mWalkAnimator) {
        mWalkAnimator->Update(dt);
    }
    else if (mState == PlayerState::Idle && mIdleAnimator) {
        mIdleAnimator->Update(dt);
    }
    else if (mState == PlayerState::Sprinting && mSprintAnimator) {
        mSprintAnimator->Update(dt);
    }
    else if (mState == PlayerState::Dashing && mDashAnimator) {
        mDashAnimator->Update(dt);  // Mise � jour de l'animation de dash
    }
}


void Player::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

void Player::OnCollision(Entity* pCollidedWith)
{
    // Gestion des collisions...
}

#include "pch.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr), mState(PlayerState::Idle)
{
    // Création de l'animation de marche
    mWalkAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_walk_strip8"),
        8,    // nombre de frames walk
        0.1f  // durée par frame walk
    );

    // Création de l'animation idle
    mIdleAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_idle_strip9"),  // nom de la spritesheet idle
        9,    // nombre de frames idle
        0.2f  // durée par frame idle
    );

    // Création de l'animation sprint
    mSprintAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_run_strip8"), // nom de la spritesheet sprint
        8,    // nombre de frames sprint
        0.08f // durée par frame sprint
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
    }
}

void Player::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

void Player::OnUpdate()
{
    float dt = GetDeltaTime();
    
    if (isMoving) {
        if (isSprinting)
        {
            SetState(PlayerState::Sprinting);
        }
        else {
			SetState(PlayerState::Walking);
        }
    }
    else {
        SetState(PlayerState::Idle);
    }

    if (mState == PlayerState::Walking && mWalkAnimator)
        mWalkAnimator->Update(dt);
    else if (mState == PlayerState::Idle && mIdleAnimator)
        mIdleAnimator->Update(dt);
    else if (mState == PlayerState::Sprinting && mSprintAnimator)
        mSprintAnimator->Update(dt);
}

void Player::OnCollision(Entity* pCollidedWith)
{
    // Gestion des collisions...
}

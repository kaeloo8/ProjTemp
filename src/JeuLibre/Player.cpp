#include "pch.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mState(PlayerState::Idle)
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
}

Player::~Player()
{
    if (mWalkAnimator) {
        delete mWalkAnimator;
        mWalkAnimator = nullptr;
    }
    if (mIdleAnimator) {
        delete mIdleAnimator;
        mIdleAnimator = nullptr;
    }
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
    }
}


void Player::SetImage(const char* path)
{
	mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

void Player::OnUpdate()
{
    float dt = GetDeltaTime();

    if (mDirection.x != 0.f || mDirection.y != 0.f)
        SetState(PlayerState::Walking);
    else
        SetState(PlayerState::Idle);

    if (mState == PlayerState::Walking && mWalkAnimator)
        mWalkAnimator->Update(dt);
    else if (mState == PlayerState::Idle && mIdleAnimator)
        mIdleAnimator->Update(dt);
}

void Player::OnCollision(Entity* pCollidedWith)
{
    // Gestion des collisions...
}

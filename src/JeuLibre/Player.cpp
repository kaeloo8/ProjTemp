#include "pch.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr), mDashAnimator(nullptr), mState(PlayerState::Idle)
{
    PlayerHair = CreateEntity<Hair>(PlayerHaircut);
    PlayerHair->SetScale(3, 3);
    PlayerHair->SetOrigin(0.5, 0.5);
    PlayerHair->Layout = 10;
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
    // Création de l'animation de dash
    mDashAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_roll_strip10"),  // nom de la spritesheet de roll/dash
        10,    // nombre de frames roll
        0.1f  // durée par frame roll
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

void Player::FaceLeft()
{
    GetSprite()->setScale(-std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(-std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::FaceRight()
{
    GetSprite()->setScale(std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::OnUpdate()
{
    float dt = GetDeltaTime();
	PlayerHair->SetPosition(GetPosition().x, GetPosition().y);

    // Gérer les états en fonction de l'action du joueur
    if (isDashing) {
        PlayerHair->SetState(HairState::Dashing);
        SetState(PlayerState::Dashing);  // Si on est en train de dasher, passer à l'état Dashing
    }
    else if (isMoving) {
        if (isSprinting) {
            PlayerHair->SetState(HairState::Sprinting);
            SetState(PlayerState::Sprinting);  // Si on court, passer à l'état Sprinting
        }
        else {
			PlayerHair->SetState(HairState::Walking);
            SetState(PlayerState::Walking);  // Si on marche, passer à l'état Walking
        }
    }
    else {
        PlayerHair->SetState(HairState::Idle);
        SetState(PlayerState::Idle);  // Si on ne bouge pas, passer à l'état Idle
    }

    // Mise à jour de l'animation en fonction de l'état actuel
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
        mDashAnimator->Update(dt);  // Mise à jour de l'animation de dash
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

#include "pch.h"
#include "PlayerPart.h"
#include "GameManager.h"

PlayerPart::PlayerPart()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr), mState(PlayerPartState::Idle)
{
	Haircut = "bowlhair";
    HairWalk = std::string(Haircut) + "_walk_strip8";
    HairRun = std::string(Haircut) + "_run_strip8";
    HairDash = std::string(Haircut) + "_roll_strip10";
    HairIdle = std::string(Haircut) + "_idle_strip9";

    // Création de l'animation de marche
    mWalkAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string(HairWalk),
        8,    // nombre de frames walk
        0.1f  // durée par frame walk
    );

    // Création de l'animation idle
    mIdleAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string(HairIdle),  // nom de la spritesheet idle
        9,    // nombre de frames idle
        0.2f  // durée par frame idle
    );

    // Création de l'animation sprint
    mSprintAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string(HairRun), // nom de la spritesheet sprint
        8,    // nombre de frames sprint
        0.08f // durée par frame sprint
    );
    // Création de l'animation de dash
    mDashAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string(HairDash),  // nom de la spritesheet de roll/dash
        10,    // nombre de frames roll
        0.1f  // durée par frame roll
    );

}

PlayerPart::~PlayerPart()
{
    delete mWalkAnimator;
    delete mIdleAnimator;
    delete mSprintAnimator;
	delete mDashAnimator;
}
void PlayerPart::SetState(PlayerPartState state)
{
    if (mState != state)
    {
        mState = state;

        if (mState == PlayerPartState::Idle) {
            SetImage(HairIdle);
            if (mIdleAnimator) mIdleAnimator->Reset();
        }
        else if (mState == PlayerPartState::Walking) {
            SetImage(HairWalk);
            if (mWalkAnimator) mWalkAnimator->Reset();
        }
        else if (mState == PlayerPartState::Sprinting) {
            SetImage(HairRun);
            if (mSprintAnimator) mSprintAnimator->Reset();
        }
        else if (mState == PlayerPartState::Dashing) {
            SetImage(HairDash);
            if (mDashAnimator) mDashAnimator->Reset();
        }
    }
}

void PlayerPart::OnUpdate()
{
    float dt = GetDeltaTime();

    // Mise à jour de l'animation en fonction de l'état actuel
    if (mState == PlayerPartState::Walking && mWalkAnimator) {
        mWalkAnimator->Update(dt);
    }
    else if (mState == PlayerPartState::Idle && mIdleAnimator) {
        mIdleAnimator->Update(dt);
    }
    else if (mState == PlayerPartState::Sprinting && mSprintAnimator) {
        mSprintAnimator->Update(dt);
    }
    else if (mState == PlayerPartState::Dashing && mDashAnimator) {
        mDashAnimator->Update(dt);  // Mise à jour de l'animation de dash
    }
}


void PlayerPart::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

void PlayerPart::SetImage(std::string path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

void PlayerPart::OnCollision(Entity* pCollidedWith)
{
    // Gestion des collisions...
}

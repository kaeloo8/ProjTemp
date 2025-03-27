#include "pch.h"
#include "PlayerPart.h"
#include "GameManager.h"

PlayerPart::PlayerPart()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr), mState(PlayerPartState::sIdle)
{
	BodyPartName = "bowlhair";
    InitBodyPart(BodyPartName);
}

PlayerPart::~PlayerPart()
{
    Clearanimation();
}
void PlayerPart::SetState(PlayerPartState state)
{
    if (mState != state)
    {
        mState = state;

        if (mState == PlayerPartState::sIdle) {
            SetImage(PartIdle);
            if (mIdleAnimator) mIdleAnimator->Reset();
        }
        else if (mState == PlayerPartState::sWalking) {
            SetImage(PartWalk);
            if (mWalkAnimator) mWalkAnimator->Reset();
        }
        else if (mState == PlayerPartState::sSprinting) {
            SetImage(PartSprint);
            if (mSprintAnimator) mSprintAnimator->Reset();
        }
        else if (mState == PlayerPartState::sAttacking) {
            SetImage(PartAttack);
            if (mAttackAnimator) mAttackAnimator->Reset();
        }
        else if (mState == PlayerPartState::sDashing) {
            SetImage(PartDash);
            if (mDashAnimator) mDashAnimator->Reset();
        }
        else if (mState == PlayerPartState::sHurt) {
            SetImage(PartHurt);
            if (mHurtAnimator) mHurtAnimator->Reset();
        }
        else if (mState == PlayerPartState::sCasting) {
            SetImage(PartCasting);
            if (mCastingAnimator) mCastingAnimator->Reset();
        }
        else if (mState == PlayerPartState::sWattering) {
            SetImage(PartWattering);
            if (mWatteringAnimator) mWatteringAnimator->Reset();
        }
        else if (mState == PlayerPartState::sReeling) {
            SetImage(PartReeling);
            if (mReelingAnimator) mReelingAnimator->Reset();
        }
        else if (mState == PlayerPartState::sCaught) {
            SetImage(PartCaught);
            if (mCaughtAnimator) mCaughtAnimator->Reset();
        }
        else if (mState == PlayerPartState::sDig) {
            SetImage(PartDig);
            if (mDigAnimator) mDigAnimator->Reset();
        }
        else if (mState == PlayerPartState::sAxe) {
            SetImage(PartDig);
            if (mDigAnimator) mDigAnimator->Reset();
        }
        else if (mState == PlayerPartState::sMining) {
            SetImage(PartMining);
            if (mMiningAnimator) mMiningAnimator->Reset();
        }
    }
}



void PlayerPart::InitBodyPart(const char* partName)
{
    BodyPartName = partName;

    if (mIdleAnimator != nullptr)
    {
        Clearanimation();
    }
    // Met à jour les chemins des spritesheets
    PartIdle = std::string(BodyPartName) + "_idle_strip9";
    PartWalk = std::string(BodyPartName) + "_walk_strip8";
    PartSprint = std::string(BodyPartName) + "_run_strip8";
    PartAttack = std::string(BodyPartName) + "_attack_strip10";
    PartDash = std::string(BodyPartName) + "_roll_strip10";
    PartHurt = std::string(BodyPartName) + "_hurt_strip8";
    PartCasting = std::string(BodyPartName) + "_casting_strip15";
    PartWattering = std::string(BodyPartName) + "_watering_strip5";
    PartReeling = std::string(BodyPartName) + "_reeling_strip13";
    PartCaught = std::string(BodyPartName) + "_caught_strip10";
    PartDig = std::string(BodyPartName) + "_dig_strip13";
    PartAxe = std::string(BodyPartName) + "_axe_strip10";
    PartMining = std::string(BodyPartName) + "_mining_strip10";

    // Création des nouveaux animateurs avec les chemins mis à jour
    mIdleAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartIdle, 9, 0.2f);
    mWalkAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartWalk, 8, 0.1f);
    mSprintAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartSprint, 8, 0.08f);
    mAttackAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartAttack, 10, 0.07f);
    mDashAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartDash, 10, 0.07f);
    mHurtAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartHurt, 8, 0.1f);
    mCastingAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartCasting, 15, 0.1f);
    mWatteringAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartWattering, 5, 0.1f);
    mReelingAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartReeling, 13, 0.1f);
    mCaughtAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartReeling, 10, 0.1f);
    mDigAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartDig, 13, 0.1f);
    mAxeAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartAxe, 10, 0.1f);
    mMiningAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), PartMining, 10, 0.1f);

    // Charge la texture par défaut (idle)
    SetImage(PartIdle);
}

void PlayerPart::Clearanimation()
{
    // Supprime les anciens animateurs
    delete mWalkAnimator;
    delete mIdleAnimator;
    delete mSprintAnimator;
    delete mDashAnimator;
    delete mAttackAnimator;
}


void PlayerPart::OnUpdate()
{
    float dt = GetDeltaTime();

    switch (mState)
    {
    case PlayerPartState::sIdle:
        if (mIdleAnimator) mIdleAnimator->Update(dt);
        break;
    case PlayerPartState::sWalking:
        if (mWalkAnimator) mWalkAnimator->Update(dt);
        break;
    case PlayerPartState::sSprinting:
        if (mSprintAnimator) mSprintAnimator->Update(dt);
        break;
    case PlayerPartState::sAttacking:
        if (mAttackAnimator) mAttackAnimator->Update(dt);
        break;
    case PlayerPartState::sDashing:
        if (mDashAnimator) mDashAnimator->Update(dt);
        break;
    case PlayerPartState::sHurt:
        if (mHurtAnimator) mHurtAnimator->Update(dt);
        break;
    case PlayerPartState::sCasting:
        if (mCastingAnimator) mCastingAnimator->Update(dt);
        break;
    case PlayerPartState::sWattering:
        if (mWatteringAnimator) mWatteringAnimator->Update(dt);
        break;
    case PlayerPartState::sReeling:
        if (mReelingAnimator) mReelingAnimator->Update(dt);
        break;
    case PlayerPartState::sCaught:
        if (mCaughtAnimator) mCaughtAnimator->Update(dt);
        break;
    case PlayerPartState::sDig:
        if (mDigAnimator) mDigAnimator->Update(dt);
        break;
    case PlayerPartState::sAxe:
        if (mAxeAnimator) mAxeAnimator->Update(dt);
        break;
    case PlayerPartState::sMining:
        if (mMiningAnimator) mMiningAnimator->Update(dt);
        break;
    default:
        break;
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

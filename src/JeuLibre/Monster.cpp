#include "pch.h"
#include "Debug.h"
#include "Condition.h"
#include "Monster.h"
#include "MonsterAction.h"
#include "MonsterCondition.h"
#include <string>
#include "SceneEloulou.h"
#include <iostream>

#include "Transition.h" // Ajout de l'inclusion du fichier d'en-tête Transition

// ... le reste du code reste inchangé ...

Monster::Monster() : MonsterState(this, State::sCount), isAttacking(false), isMoving(false)
{
    MonsterName = "skeleton";
    InitMonster(MonsterName);
}

Monster::~Monster()
{
    ClearAnimation();
}

void Monster::OnAnimationUpdate()
{
    float dt = GetDeltaTime();
    int state = MonsterState.GetCurrentState();

    if (state == 1 || state == 3) {
        mWalkAnimator->Update(dt);
    }
    else if (state == 0 && mIdleAnimator) {
        mIdleAnimator->Update(dt);
    }
    else if (state == 2 && mAttackAnimator) {
        mAttackAnimator->Update(dt);
    }
}

void Monster::FaceRight()
{
    GetSprite()->setScale(std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
}

void Monster::FaceLeft()
{
    GetSprite()->setScale(-std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
}

void Monster::ClearAnimation()
{
    delete mIdleAnimator;    // 1
    delete mWalkAnimator;    // 2 et 11
    delete mChargeAnimator;  // 3
    delete mRunAwayAnimator; // 4
    delete mAttackAnimator;  // 5
    delete mShotAnimator;    // 6
    delete mStuntAnimator;   // 7
    delete mDamagedAnimator; // 8
    delete mDiedAnimator;    // 9
    delete mVictoryAnimator; // 10
}

void Monster::SetInitialPosition()
{
    InitialPosition = { GetPosition().x, GetPosition().y };
}

void Monster::InitMonster(const char* _MonsterName)
{
    MonsterName = _MonsterName;

    if (mIdleAnimator != nullptr)
    {
        ClearAnimation();
    }

    cIdle = std::string(MonsterName) + "_walk_strip8";
    cWalk = std::string(MonsterName) + "_run_strip8";
    cCharge = std::string(MonsterName) + "_run_strip8";
    cRunAway = std::string(MonsterName) + "_roll_strip10";
    cAttack = std::string(MonsterName) + "_idle_strip9";
    cShot = std::string(MonsterName) + "_attack_strip10";
    cStunt = std::string(MonsterName) + "_attack_strip10";
    cDamaged = std::string(MonsterName) + "_attack_strip10";
    cDied = std::string(MonsterName) + "_attack_strip10";
    cVictory = std::string(MonsterName) + "_attack_strip10";

    mIdleAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cIdle, 8, 0.1f);
    mWalkAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cWalk, 9, 0.2f);
    mAttackAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cAttack, 10, 0.07f);
    mStuntAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cStunt, 10, 0.07f);
    mDamagedAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cRunAway, 10, 0.1f);
    mDiedAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cDamaged, 10, 0.07f);

    if (CanCharge)
    {
        mChargeAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cCharge, 8, 0.08f);
    }
    if (CanRunAway)
    {
        mRunAwayAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cRunAway, 10, 0.1f);
    }
    if (CanShoot)
    {
        mShotAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cShot, 10, 0.1f);
    }
    if (CanTaunt)
    {
        mVictoryAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cVictory, 10, 0.07f);
    }

    // --- ÉTAT IDLE ---
    {
        Behaviour<Monster>* bMonsterIdle = MonsterState.CreateBehaviour(State::sIdle);
        bMonsterIdle->AddAction(new sIdle_Action());

        // -> Walk (si le joueur est proche)
        {
        }

        // -> GoBack (si le joueur est trop loin)
        {
        }
    }

    // --- ÉTAT WALK ---
    {
        Behaviour<Monster>* bWalk = MonsterState.CreateBehaviour(State::sWalk);
        bWalk->AddAction(new sFollowPlayer_Action());

        // -> Idle (si le joueur est trop loin, donc il ne peut plus le suivre)
        {
        }

        // -> Attack (si le monstre est assez proche pour attaquer)
        {
        }
    }

    // --- ÉTAT ATTACK ---
    {
        Behaviour<Monster>* bAttack = MonsterState.CreateBehaviour(State::sAttack);
        bAttack->AddAction(new sAttack_Action());

        // -> Walk (si le joueur s'éloigne)
        {
        }
    }

    // --- ÉTAT GO BACK ---
    {
        Behaviour<Monster>* bGoBack = MonsterState.CreateBehaviour(State::sGoBack);
        bGoBack->AddAction(new sReturnToPosition_Action());

        // -> Idle (si le monstre est revenu à sa position d'origine)
        {
        }

        // -> Walk (si le joueur revient dans la zone)
        {
        }
    }

    MonsterState.SetState(State::sIdle);
}

void Monster::SetTarget(Entity* _Target)
{
    mTarget = _Target;
}

void Monster::OrientToTarget(bool Oposite)
{
    if (!mTarget) return;
    if (Oposite)
    {
        if (mTarget->GetPosition().x < GetPosition().x)
        {
            FaceLeft();
        }
        else
        {
            FaceRight();
        }
    }
    else
    {
        if (mTarget->GetPosition().x < GetPosition().x)
        {
            FaceRight();
        }
        else
        {
            FaceLeft();
        }
    }
}

void Monster::OnUpdate()
{
    OnAnimationUpdate();
    MonsterState.Update();

    if (isAttacking)
    {
        AttackTimer -= GameManager::Get()->GetDeltaTime();

        if (AttackTimer <= 0)
        {
            isAttacking = false;
        }
    }

    if (true)
    {
        if (!mTarget) return;
        Debug::DrawLine(mTarget->GetPosition().x, mTarget->GetPosition().y, GetPosition().x, GetPosition().y, LineColor);
    }
}

void Monster::OnCollision(Entity* pCollidedWith)
{
}

void Monster::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

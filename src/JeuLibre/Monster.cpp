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

void Monster::MonsterOption(bool CanItShoot, bool CanItRunAway, bool CanItCharge, bool CanItTaunt)
{
    CanShoot = CanItShoot;
    CanRunAway = CanItRunAway;
    CanCharge = CanItCharge;
    CanTaunt = CanItTaunt;
}

void Monster::OnAnimationUpdate()
{
    float dt = GetDeltaTime();
    int state = MonsterState.GetCurrentState();

    switch (state) {
    case State::sIdle:
        mIdleAnimator->Update(dt);
        break;
    case State::sWalk:
    case 6: // Si 6 correspond aussi à Walk
        mWalkAnimator->Update(dt);
        break;
    case State::sCharge:
        mChargeAnimator->Update(dt);
        break;
    case State::sRunAway:
        mRunAwayAnimator->Update(dt);
        break;
    case State::sAttack:
        mAttackAnimator->Update(dt);
        break;
    case State::sShot:
        mShotAnimator->Update(dt);
        break;
    case State::sStunt:
        mStuntAnimator->Update(dt);
        break;
    case State::sDamaged:
        mDamagedAnimator->Update(dt);
        break;
    case State::sDied:
        mDiedAnimator->Update(dt);
        break;
    case State::sVictory:
        mVictoryAnimator->Update(dt);
        break;
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
    if (mIdleAnimator != nullptr)
    {
        return;
    }
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

    ClearAnimation();

    cIdle = std::string(MonsterName) + "_idle_strip6";
    cWalk = std::string(MonsterName) + "_walk_strip8";
    cCharge = std::string(MonsterName) + "_walk_strip8";
    cRunAway = std::string(MonsterName) + "_walk_strip8";
    cAttack = std::string(MonsterName) + "_attack_strip7";
    cShot = std::string(MonsterName) + "_jump_strip10";
    cStunt = std::string(MonsterName) + "_death_strip10";
    cDamaged = std::string(MonsterName) + "_death_strip10";
    cDied = std::string(MonsterName) + "_death_strip10";
    cVictory = std::string(MonsterName) + "_jump_strip10";

    mIdleAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cIdle, 6, 0.1f);
    mWalkAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cWalk, 8, 0.2f);
    mAttackAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cAttack, 7, 0.07f);
    mStuntAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cStunt, 10, 0.07f);
    mDamagedAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cRunAway, 8, 0.1f);
    mDiedAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cDamaged, 10, 0.07f);

    if (CanCharge)
    {
        mChargeAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cCharge, 8, 0.08f);
    }
    if (CanRunAway)
    {
        mRunAwayAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cRunAway, 8, 0.1f);
    }
    if (CanShoot)
    {
        mShotAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), cShot, 10, 0.2f);
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
            auto transition = bMonsterIdle->CreateTransition(State::sWalk);
            auto condition = transition->AddCondition<CanSeeThePlayer>();
            condition->expected = true;
        }

        // -> Goback
        {
            auto transition = bMonsterIdle->CreateTransition(State::sGoBack);
            auto condition = transition->AddCondition<IsAtInitialPosition>();
            condition->expected = false;
        }
    }

    // --- ÉTAT WALK ---
    {
        Behaviour<Monster>* bWalk = MonsterState.CreateBehaviour(State::sWalk);
        bWalk->AddAction(new sFollowPlayer_Action());

        // -> Idle
        {
            auto transition = bWalk->CreateTransition(State::sIdle);
            auto condition = transition->AddCondition<CanSeeThePlayer>();
            condition->expected = false;
        }

        // -> Attack
        {
            auto transition = bWalk->CreateTransition(State::sAttack);
            auto condition = transition->AddCondition<IsAtAttackDistance>();
            condition->expected = true;
        }
    }

    // --- ÉTAT GO BACK ---
    {
        Behaviour<Monster>* bGoBack = MonsterState.CreateBehaviour(State::sGoBack);
        bGoBack->AddAction(new sReturnToPosition_Action());

        // -> Idle (si le monstre est revenu à sa position d'origine)
        {
            auto transition = bGoBack->CreateTransition(State::sIdle);
            auto condition = transition->AddCondition<IsAtInitialPosition>();
            condition->expected = true;
        }

        // -> Walk (si le joueur revient dans la zone)
        {
            auto transition = bGoBack->CreateTransition(State::sWalk);
            auto condition = transition->AddCondition<CanSeeThePlayer>();
            condition->expected = true;
        }
    }

    // --- ÉTAT ATTACK ---
    {
        Behaviour<Monster>* bAttack = MonsterState.CreateBehaviour(State::sAttack);
        bAttack->AddAction(new sAttack_Action());

        // -> Walk
        {
            auto transition = bAttack->CreateTransition(State::sIdle);
            auto condition = transition->AddCondition<IsAtAttackDistance>();
            condition->expected = false;
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

    if (true)
    {
        if (!mTarget) return;
        Debug::DrawLine(mTarget->GetPosition().x, mTarget->GetPosition().y, GetPosition().x, GetPosition().y, LineColor);
        Debug::DrawText(GetPosition().x, GetPosition().y + 30, GetCurrentStateName(), sf::Color::Yellow);
    }
}

void Monster::OnCollision(Entity* pCollidedWith)
{
    if (pCollidedWith == )
}

void Monster::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

std::string Monster::GetCurrentStateName() {
    switch (MonsterState.GetCurrentState()) {
    case State::sIdle: return "Idle";
    case State::sWalk: return "Walk";
    case State::sAttack: return "Attack";
    case State::sGoBack: return "GoBack";
    default: return "Unknown";
    }
}

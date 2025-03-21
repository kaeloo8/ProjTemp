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

Monster::Monster() : DeffensiveMonsterState(this, State::sCount), isAttacking(false), isMoving(false)
{

    mIdleAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("skeleton_idle_strip6"),
        6,    // nombre de frames idle
        0.2f  // durée par frame idle
    );
    mWalkAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("skeleton_walk_strip8"),
        8,    // nombre de frames walk
        0.07f  // durée par frame walk
    );
    mAttackAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("skeleton_attack_strip7"),
        7,    // nombre de frames roll
        AttackSpeed  // durée par frame roll
    );

    // --- ÉTAT IDLE ---
    {
        Behaviour<Monster>* bMonsterIdle = DeffensiveMonsterState.CreateBehaviour(State::sIdle);
        bMonsterIdle->AddAction(new sIdle_Action());

        // -> Walk (si le joueur est proche)
        {
            auto transition = bMonsterIdle->CreateTransition(State::sWalk);
            auto condition = transition->AddCondition<DistanceToPlayerCondition>();
            condition->expected = true;
        }

        // -> GoBack (si le joueur est trop loin)
        {
            auto transition = bMonsterIdle->CreateTransition(State::sGoBack);
            auto condition = transition->AddCondition<IsAtHome>();
            condition->expected = false;
        }
    }

    // --- ÉTAT WALK ---
    {
        Behaviour<Monster>* bWalk = DeffensiveMonsterState.CreateBehaviour(State::sWalk);
        bWalk->AddAction(new sFollowPlayer_Action());

        // -> Idle (si le joueur est trop loin, donc il ne peut plus le suivre)
        {
            auto transition = bWalk->CreateTransition(State::sIdle);
            auto condition = transition->AddCondition<FarFromPlayerCondition>();
            condition->expected = true;
        }

        // -> Attack (si le monstre est assez proche pour attaquer)
        {
            auto transition = bWalk->CreateTransition(State::sAttack);
            auto condition = transition->AddCondition<AttackThePlayerCondition>(); // Ajoute une condition de distance plus proche
            condition->expected = true;
        }
    }

    // --- ÉTAT ATTACK ---
    {
        Behaviour<Monster>* bAttack = DeffensiveMonsterState.CreateBehaviour(State::sAttack);
        bAttack->AddAction(new sAttack_Action());

        // -> Walk (si le joueur s'éloigne)
        {
            auto transition = bAttack->CreateTransition(State::sWalk);
            auto condition = transition->AddCondition<AttackThePlayerCondition>(); // Si le joueur fuit
            condition->expected = false;
        }
    }

    // --- ÉTAT GO BACK ---
    {
        Behaviour<Monster>* bGoBack = DeffensiveMonsterState.CreateBehaviour(State::sGoBack);
        bGoBack->AddAction(new sReturnToPosition_Action());

        // -> Idle (si le monstre est revenu à sa position d'origine)
        {
            auto transition = bGoBack->CreateTransition(State::sIdle);
            auto condition = transition->AddCondition<IsAtHome>(); // Une autre condition pour vérifier si la position est atteinte
            condition->expected = true;
        }

        // -> Walk (si le joueur revient dans la zone)
        {
            auto transition = bGoBack->CreateTransition(State::sWalk);
            auto condition = transition->AddCondition<DistanceToPlayerCondition>();
            condition->expected = true;
        }
    }

    DeffensiveMonsterState.SetState(State::sIdle);
}

Monster::~Monster()
{
    delete mWalkAnimator;
    delete mIdleAnimator;
    delete mAttackAnimator;
}

void Monster::OnAnimationUpdate()
{
    float dt = GetDeltaTime();
    int state = DeffensiveMonsterState.GetCurrentState();
    // Mise à jour des animations selon l'état
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

void Monster::SetInitialPosition()
{
    InitialPosition = { GetPosition().x, GetPosition().y };
}

void Monster::SetTarget(Entity* _Target)
{
    mTarget = _Target;
}

void Monster::OrientToTarget()
{
    if (!mTarget) return;

    if (mTarget->GetPosition().x < GetPosition().x)
    {
        FaceLeft();
    }
    else
    {
        FaceRight();
    }
}

void Monster::OnUpdate()
{
    OnAnimationUpdate();
    DeffensiveMonsterState.Update();

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

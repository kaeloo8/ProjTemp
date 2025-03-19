#include "pch.h"
#include "Condition.h"
#include "Monster.h"
#include "MonsterAction.h"
#include "MonsterCondition.h"
#include <string>
#include "SceneEloulou.h"
#include <iostream>

#include "Transition.h" // Ajout de l'inclusion du fichier d'en-tête Transition

// ... le reste du code reste inchangé ...

Monster::Monster() : mState(State::sIdle), DeffensiveMonsterState(this, State::sCount), isAttacking(false), isMoving(false)
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
        0.1f  // durée par frame walk
    );
    mAttackAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("skeleton_attack_strip7"),
        7,    // nombre de frames roll
        0.07f  // durée par frame roll
    );
    // --- ÉTAT IDLE ---
    {
        Behaviour<Monster>* bMonsterIdle = DeffensiveMonsterState.CreateBehaviour(State::sIdle);
        bMonsterIdle->AddAction(new sIdle_Action());

        //-> Walk (se déplacer)
        {
            auto transition = bMonsterIdle->CreateTransition(State::sWalk);
            auto condition = transition->AddCondition<DistanceToPlayerCondition>();
            condition->expected = true;  // Le monstre commence à marcher si le joueur est à une certaine distance
        }

        //-> Attack (attaquer)
        {
        }

        //-> GoBack (revenir à la position d'origine)
        {
        }
    }

    // --- ÉTAT WALK ---
    {
        Behaviour<Monster>* bWalk = DeffensiveMonsterState.CreateBehaviour(State::sWalk);
        bWalk->AddAction(new sFollowPlayer_Action());

        //-> Idle (rester inactif)
        {
            auto transition = bWalk->CreateTransition(State::sIdle);
            auto condition = transition->AddCondition<DistanceToPlayerCondition>();
            condition->expected = false;  // Le monstre commence à marcher si le joueur est à une certaine distance
        }

        //-> Attack (attaquer)
        {
        }

        //-> GoBack (revenir à la position d'origine)
        {
        }
    }

    // --- ÉTAT ATTACK ---
    {
        Behaviour<Monster>* bAttack = DeffensiveMonsterState.CreateBehaviour(State::sAttack);
        bAttack->AddAction(new sAttack_Action());

        //-> Idle (rester inactif)
        {
        }

        //-> Walk (se déplacer)
        {
        }

        //-> GoBack (revenir à la position d'origine)
        {
        }
    }

    // --- ÉTAT GO BACK ---
    {
        Behaviour<Monster>* bGoBack = DeffensiveMonsterState.CreateBehaviour(State::sGoBack);
        bGoBack->AddAction(new sReturnToPosition_Action());

        //-> Idle (rester inactif)
        {
        }

        //-> Walk (se déplacer)
        {
        }

        //-> Attack (attaquer)
        {
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

    // Mise à jour des animations selon l'état
    if (mState == sWalk && mWalkAnimator) {
        mWalkAnimator->Update(dt);
    }
    else if (mState == sIdle && mIdleAnimator) {
        mIdleAnimator->Update(dt);
    }
    else if (mState == sAttack && mAttackAnimator) {
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

void Monster::OnUpdate()
{
    OnAnimationUpdate();
    DeffensiveMonsterState.Update();
}

void Monster::OnCollision(Entity* pCollidedWith)
{
}

void Monster::SetState(State state)
{
    if (mState != state)
    {
        mState = state;

        // Modification de l'image et réinitialisation de l'animation en fonction de l'état
        if (mState == State::sIdle) {
            SetImage("skeleton_idle_strip6");
            if (mIdleAnimator) mIdleAnimator->Reset();
        }
        else if (mState == State::sWalk || mState == State::sGoBack) {
            SetImage("skeleton_walk_strip8");
            if (mWalkAnimator) mWalkAnimator->Reset();
        }
        else if (mState == State::sAttack) {
            SetImage("skeleton_attack_strip7");
            if (mAttackAnimator) mAttackAnimator->Reset();
        }

    }
}

void Monster::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

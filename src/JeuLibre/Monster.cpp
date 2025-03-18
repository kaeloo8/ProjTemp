#include "pch.h"
#include "Condition.h"
#include "Monster.h"
#include "MonsterAction.h"
#include "MonsterCondition.h"
#include <string>
#include "SceneEloulou.h"
#include <iostream>

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

	// IDLE
	{
		Behaviour<Monster>* bMonsterIdle = DeffensiveMonsterState.CreateBehaviour(State::sIdle);
		bMonsterIdle->AddAction(new sIdle_Action());

		//-> Advance
		{
		}

		//-> StepBack
		{
		}

		//-> Run
		{
		}
	}

	// ADVANCE
	{
		Behaviour<Monster>* pAdvance = DeffensiveMonsterState.CreateBehaviour(State::sWalk);
		pAdvance->AddAction(new sAdvance_Action());

		//-> Idle
		{
		}

		//-> StepBack
		{
		}

		//-> Run
		{
		}
	}

	// STEPBACK
	{
		Behaviour<Monster>* pStepBack = DeffensiveMonsterState.CreateBehaviour(State::sGoBack);
		pStepBack->AddAction(new sStepBack_Action());

		//-> Idle
		{
		}

		//-> Advance
		{
		}

		//-> Run
		{
		}
	}

	// RUN
	{
		Behaviour<Monster>* pRun = DeffensiveMonsterState.CreateBehaviour(State::sAttack);
		pRun->AddAction(new sRun_Action());

		//-> Idle
		{
		}

		//-> StepBack
		{
		}

		//-> Advance 
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
}

void Monster::OnCollision(Entity* pCollidedWith)
{
}

void Monster::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

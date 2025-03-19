#pragma once
#include "Entity.h"
#include "Animator.h"
#include "StateMachine.h"


class Monster : public Entity
{
private:
    Animator* mIdleAnimator;
    Animator* mWalkAnimator;
    Animator* mAttackAnimator;

    void OnAnimationUpdate();

public:

    StateMachine<Monster> DeffensiveMonsterState;

    enum State
    {
        sIdle,
        sWalk,
        sAttack,
        sGoBack,

        sCount
    };
    static const int DeffensiveMonsterState_count = (int)State::sCount;

private:

    State mState = State::sIdle;

    int mTransitions[DeffensiveMonsterState_count][DeffensiveMonsterState_count] = {
        {0,1,1,1},
        {1,0,1,1},
        {1,1,0,1},
        {1,1,1,0}
    };

public:

    int Speed;
    int Life;

    bool isMoving;
    bool isAttacking;

    const char* PlayerHaircut = "shorthair_idle_strip9";

    Monster();
    ~Monster();

    float attackTimer;
    float attackCooldown = 0.f;
    const float attackDuration = 0.7f;

    void FaceRight();
    void FaceLeft();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;

    void SetImage(const char* path) override;

    friend class sIdle_Action;
    friend class sCharge_Action;
    friend class sAttack_Action;
    friend class sGoBack_Action;
};


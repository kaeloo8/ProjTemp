#pragma once
#include "Entity.h"
#include "Animator.h"
#include "StateMachine.h"
#include "Player.h"

class Monster : public Entity
{
private:
    Animator* mIdleAnimator;
    Animator* mWalkAnimator;
    Animator* mAttackAnimator;


    void OnAnimationUpdate();

    sf::Vector2f InitialPosition;

public:

    Player* mTarget;
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
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1}
    };

public:
    int Life;

    bool isMoving;
    bool isAttacking;

    float SeeDistance = 500;
    float AttackDistance;

    Monster();
    ~Monster();

    float attackTimer;
    float attackCooldown = 0.f;
    const float attackDuration = 0.7f;

    void FaceRight();
    void FaceLeft();

    void SetState(State state);

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;

    friend class sIdle_Action;
    friend class sFollowPlayer_Action;
    friend class sAttack_Action;
    friend class sReturnToPosition_Action;
};


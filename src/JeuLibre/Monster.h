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

    sf::Color LineColor;

public:

    Entity* mTarget = nullptr;
    StateMachine<Monster> DeffensiveMonsterState;
    sf::Vector2f InitialPosition;

    enum State
    {
        sIdle,
        sWalk,
        sAttack,
        sGoBack,
        sStunt,
        sDied,

        sCount
    };
    static const int DeffensiveMonsterState_count = (int)State::sCount;

private:

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
    float AttackDistance = 50;
    float AttackSpeed = 0.08f;

    Monster();
    ~Monster();

    void FaceRight();
    void FaceLeft();

    void SetInitialPosition();
    void SetTarget(Entity* _Target);
    void OrientToTarget();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;

    friend class sIdle_Action;
    friend class sFollowPlayer_Action;
    friend class sAttack_Action;
    friend class sReturnToPosition_Action;
};


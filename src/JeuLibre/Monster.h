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
    Animator* mChargeAnimator;
    Animator* mRunAwayAnimator;
    Animator* mAttackAnimator;
    Animator* mShotAnimator;
    Animator* mStuntAnimator;
    Animator* mDamagedAnimator;
    Animator* mDiedAnimator;
    Animator* mVictoryAnimator;

    std::string cIdle;
    std::string cWalk;
    std::string cCharge;
    std::string cRunAway;
    std::string cAttack;
    std::string cShot;
    std::string cStunt;
    std::string cDamaged;
    std::string cDied;
    std::string cVictory;

    void OnAnimationUpdate();

    //Debug
    sf::Color LineColor;

public:

    const char* MonsterName;
    Entity* mTarget = nullptr;
    StateMachine<Monster> DeffensiveMonsterState;
    sf::Vector2f InitialPosition;

    enum State
    {
        sIdle,
        sWalk,
        sCharge,
        sRunAway,
        sAttack,
        sShot,
        sGoBack,
        sStunt,
        sDamaged,
        sDied,
        sVictory,

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
    bool CanShoot;
    bool CanRunAway;
    bool CanCharge;
    bool CanTaunt;

    bool isStunt;
    bool isMoving;
    bool isAttacking;

    float SeeDistance = 500;
    float ShotDistance = 100;
    float ShotSpeed = 0.1f;
    float AttackDistance = 50;
    float AttackSpeed = 0.08f;
    float AttackTimer = 3;

    Monster();
    ~Monster();

    void FaceRight();
    void FaceLeft();

    void ClearAnimation();
    void SetInitialPosition();
    void InitMonster(const char* _MonsterName);
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


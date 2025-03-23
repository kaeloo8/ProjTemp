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
    sf::Vector2f mTargetPosition;

    StateMachine<Monster> MonsterState;
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
    static const int MonsterState_count = (int)State::sCount;

private:

    int mTransitions[MonsterState_count][MonsterState_count] = {
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
    bool isShooting;

    //RUN
    float DistanceMin = 40;
    //DAMAGE
    float PlayerDamage = 10;
    //DETECTION
    float SeeDistance = 500;
    //CHARGE
    float ChargeMultiplicator = 2;
    //SHOT
    float ShotDistance = 100;
    float ShotSpeed = 0.1f;
    //ATTACK
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
    void OrientToTarget(bool Oposite);

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;

    friend class sIdle_Action;
    friend class sFollowPlayer_Action;
    friend class sCharge_Action;
    friend class sRunAway_Action;
    friend class sAttack_Action;
    friend class sShot_Action;
    friend class sReturnToPosition_Action;
    friend class sStunt_Action;
    friend class sDamaged_Action;
    friend class sDied_Action;
    friend class sVictory_Action;
};


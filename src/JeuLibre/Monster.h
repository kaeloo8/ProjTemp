#pragma once
#include "Entity.h"
#include "Animator.h"


enum class MonsterState {
    Idle,
    Walking,
    Attacking
};


class Monster : public Entity
{
private:
    Animator* mIdleAnimator;
    Animator* mWalkAnimator;
    Animator* mAttackAnimator;

    MonsterState mState;

    void OnAnimationUpdate();

public:

    bool isMoving;
    bool isAttacking;

    const char* PlayerHaircut = "shorthair_idle_strip9";

    Monster();
    ~Monster();

    float lastVelocityX, lastVelocityY;
    float dashVelocityX, dashVelocityY;

    float attackTimer;
    float attackCooldown = 0.f;
    const float attackDuration = 0.7f;

    float dashTimer;
    float dashCooldown = 0.f;
    const float maxDashCooldown = 0.5f;

    void FaceRight();
    void FaceLeft();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(MonsterState state);

    void SetImage(const char* path) override;
};


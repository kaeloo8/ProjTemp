#pragma once

#include "Entity.h"
#include "Animator.h"

enum class HairState {
    Idle,
    Walking,
    Sprinting,
    Dashing
};

class Hair : public Entity
{
private:
    Animator* mWalkAnimator;
    Animator* mIdleAnimator;
    Animator* mSprintAnimator;
    Animator* mDashAnimator;
    HairState mState;

    std::string HairWalk;
    std::string HairRun;
    std::string HairDash;
    std::string HairIdle;

public:
    const char* Haircut;

    bool isMoving;
    bool isSprinting;
    bool isDashing;

    Hair();
    ~Hair();

    float lastVelocityX, lastVelocityY;
    float dashVelocityX, dashVelocityY;
    float dashTimer;
    float dashCooldown = 0.f;
    const float maxDashCooldown = 0.5f;

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(HairState state);

    void SetImage(const char* path) override;
    void SetImage(std::string path);
};

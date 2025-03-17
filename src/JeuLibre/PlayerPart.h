#pragma once

#include "Entity.h"
#include "Animator.h"

enum class PlayerPartState {
    Idle,
    Walking,
    Sprinting,
    Dashing
};

class PlayerPart : public Entity
{
private:
    Animator* mWalkAnimator;
    Animator* mIdleAnimator;
    Animator* mSprintAnimator;
    Animator* mDashAnimator;
    PlayerPartState mState;

    std::string HairWalk;
    std::string HairRun;
    std::string HairDash;
    std::string HairIdle;

public:
    const char* Haircut;

    bool isMoving;
    bool isSprinting;
    bool isDashing;

    PlayerPart();
    ~PlayerPart();

    float lastVelocityX, lastVelocityY;
    float dashVelocityX, dashVelocityY;
    float dashTimer;
    float dashCooldown = 0.f;
    const float maxDashCooldown = 0.5f;

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetState(PlayerPartState state);

    void SetImage(const char* path) override;
    void SetImage(std::string path);
};

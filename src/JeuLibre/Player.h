#pragma once

#include "Entity.h"
#include "Animator.h"

class Player : public Entity
{
private:
    Animator* mAnimator; // Pointeur vers l'Animator (null si aucune anim active)

public:
    Player(); 
    ~Player(); 

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;

    void SetImage(const char* path) override;
};

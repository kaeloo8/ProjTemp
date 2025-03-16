#pragma once
#include "Entity.h"
#include "Animator.h"

class Player : public Entity
{
public :
	Animator PlayerAnimator;

	Player();
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
};


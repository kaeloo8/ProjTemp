#include "pch.h"
#include "MonsterAction.h"
#include "Monster.h"
#include "Debug.h"
#include <iostream>

//----------------------  IDLE  ---------------------------------------
void sIdle_Action::Start(Monster* pMonster)
{
	pMonster->isMoving = false;
	pMonster->isAttacking = false;
	pMonster->SetImage(pMonster->cIdle.c_str());
	pMonster->mIdleAnimator->Reset();
}

void sIdle_Action::Update(Monster* pMonster) 
{

}

void sIdle_Action::End(Monster* pMonster)
{
	
}

//----------------------  WALK  ---------------------------------------
void sFollowPlayer_Action::Start(Monster* pMonster) 
{
	pMonster->isMoving = true;
	pMonster->SetImage(pMonster->cWalk.c_str());
	pMonster->mWalkAnimator->Reset();
}

void sFollowPlayer_Action::Update(Monster* pMonster) 
{
	pMonster->GoToPosition(pMonster->mTarget->GetPosition().x, pMonster->mTarget->GetPosition().y, pMonster->mSpeed);
	pMonster->OrientToTarget(true);
}

void sFollowPlayer_Action::End(Monster* pMonster) 
{
	pMonster->StopGo();
	pMonster->isMoving = false;
}

//----------------------  CHARGE  ---------------------------------------
void sCharge_Action::Start(Monster* pMonster)
{
	pMonster->isMoving = true;
	pMonster->OrientToTarget(true);
	pMonster->mTargetPosition = pMonster->mTarget->GetPosition();
	pMonster->SetImage(pMonster->cCharge.c_str());
	pMonster->mChargeAnimator->Reset();
}

void sCharge_Action::Update(Monster* pMonster)
{
	pMonster->GoToPosition(pMonster->mTargetPosition.x, pMonster->mTargetPosition.y, pMonster->mSpeed * pMonster->ChargeMultiplicator);
}

void sCharge_Action::End(Monster* pMonster)
{
	pMonster->StopGo();
	pMonster->isMoving = false;
}

//----------------------  RUNAWAY  ---------------------------------------
void sRunAway_Action::Start(Monster* pMonster)
{
	pMonster->isMoving = true;
	pMonster->OrientToTarget(false);
	pMonster->SetImage(pMonster->cRunAway.c_str());
	pMonster->mRunAwayAnimator->Reset();
}

void sRunAway_Action::Update(Monster* pMonster)
{

}

void sRunAway_Action::End(Monster* pMonster)
{
	pMonster->StopGo();
	pMonster->isMoving = false;
}

//----------------------  ATTACK  ---------------------------------------
void sAttack_Action::Start(Monster* pMonster) 
{
	pMonster->isAttacking = true;
	pMonster->SetImage(pMonster->cAttack.c_str());
	pMonster->mAttackAnimator->Reset();
}

void sAttack_Action::Update(Monster* pMonster) 
{
	pMonster->OrientToTarget(true);
}

void sAttack_Action::End(Monster* pMonster) 
{
	pMonster->isAttacking = false;
}

//----------------------  SHOT  ---------------------------------------
void sShot_Action::Start(Monster* pMonster)
{
	pMonster->isShooting = true;
	pMonster->SetImage(pMonster->cShot.c_str());
}

void sShot_Action::Update(Monster* pMonster)
{

}

void sShot_Action::End(Monster* pMonster)
{
	pMonster->isShooting = false;
}

//----------------------  GOBACK  ---------------------------------------
void sReturnToPosition_Action::Start(Monster* pMonster) 
{
	pMonster->isMoving = true;
	if (pMonster->InitialPosition.x < pMonster->GetPosition().x)
	{
		pMonster->FaceLeft();
	}
	else
	{
		pMonster->FaceRight();
	}
	pMonster->SetImage(pMonster->cWalk.c_str());
}

void sReturnToPosition_Action::Update(Monster* pMonster) 
{
	pMonster->GoToPosition(pMonster->InitialPosition.x, pMonster->InitialPosition.y, pMonster->mSpeed);
}

void sReturnToPosition_Action::End(Monster* pMonster) 
{
	pMonster->StopGo();
	pMonster->OrientToTarget(true);
	pMonster->isMoving = false;
}

//----------------------  STUNT  ---------------------------------------
void sStunt_Action::Start(Monster* pMonster)
{
	pMonster->isMoving = false;
}

void sStunt_Action::Update(Monster* pMonster)
{

}

void sStunt_Action::End(Monster* pMonster)
{

}

//----------------------  DAMAGED  ---------------------------------------
void sDamaged_Action::Start(Monster* pMonster)
{
	pMonster->mDamagedAnimator->Reset();
	pMonster->mHasbeenHit = true;
	pMonster->SetImage(pMonster->cDamaged.c_str());

	// Knockback
	sf::Vector2f fromPlayer = pMonster->GetPosition() - pMonster->mTarget->GetPosition();
	float length = std::sqrt(fromPlayer.x * fromPlayer.x + fromPlayer.y * fromPlayer.y);

	if (length != 0) {
		fromPlayer /= length; // Normaliser
	}

	pMonster->mKnockbackDirection = fromPlayer;
	pMonster->mKnockbackTimer = 0.15f; // Recul pendant 0.15 sec

}

void sDamaged_Action::Update(Monster* pMonster)
{
	if (pMonster->mKnockbackTimer > 0) {
		float dt = GameManager::Get()->GetDeltaTime();
		const float knockbackSpeed = 150.f; // Ajustable
		pMonster->SetPosition(
			pMonster->GetPosition().x + pMonster->mKnockbackDirection.x * knockbackSpeed * dt,
			pMonster->GetPosition().y + pMonster->mKnockbackDirection.y * knockbackSpeed * dt
		);
		pMonster->mKnockbackTimer -= dt;
	}

}

void sDamaged_Action::End(Monster* pMonster)
{

}

//----------------------  DIED  ---------------------------------------
void sDied_Action::Start(Monster* pMonster)
{

}

void sDied_Action::Update(Monster* pMonster)
{

}

void sDied_Action::End(Monster* pMonster)
{

}

//----------------------  VICTORY  ---------------------------------------
void sVictory_Action::Start(Monster* pMonster)
{

}

void sVictory_Action::Update(Monster* pMonster)
{

}

void sVictory_Action::End(Monster* pMonster)
{

}



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
	pMonster->DamageLife(pMonster->PlayerDamage);
}

void sDamaged_Action::Update(Monster* pMonster)
{

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
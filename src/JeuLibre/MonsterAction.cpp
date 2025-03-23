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

}

void sFollowPlayer_Action::End(Monster* pMonster) 
{

}

//----------------------  CHARGE  ---------------------------------------
void sCharge_Action::Start(Monster* pMonster)
{
	pMonster->isMoving = true;
}

void sCharge_Action::Update(Monster* pMonster)
{

}

void sCharge_Action::End(Monster* pMonster)
{

}

//----------------------  RUNAWAY  ---------------------------------------
void sRunAway_Action::Start(Monster* pMonster)
{
	pMonster->isMoving = true;
}

void sRunAway_Action::Update(Monster* pMonster)
{

}

void sRunAway_Action::End(Monster* pMonster)
{

}

//----------------------  ATTACK  ---------------------------------------
void sAttack_Action::Start(Monster* pMonster) 
{
	pMonster->isAttacking = true;
}

void sAttack_Action::Update(Monster* pMonster) 
{

}

void sAttack_Action::End(Monster* pMonster) 
{

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

}

//----------------------  GOBACK  ---------------------------------------
void sReturnToPosition_Action::Start(Monster* pMonster) 
{
	pMonster->isMoving = true;
}

void sReturnToPosition_Action::Update(Monster* pMonster) 
{

}

void sReturnToPosition_Action::End(Monster* pMonster) 
{

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
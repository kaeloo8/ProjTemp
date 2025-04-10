#pragma once

#include "Condition.h"
#include "Monster.h"

class IsAtAttackDistance : public Condition<Monster>
{
public:
	bool OnTest(Monster* pMonster) override;
};

class CanSeeThePlayer : public Condition<Monster>
{
public:
	bool OnTest(Monster* pMonster) override;
};

class IsAtInitialPosition : public Condition<Monster>
{
public:
	bool OnTest(Monster* pMonster) override;
};

class IsTargetAlive : public Condition<Monster>
{
public:
	bool OnTest(Monster* pMonster) override;
};

class IsTargettoClose : public Condition<Monster>
{
public:
	bool OnTest(Monster* pMonster) override;
};

class IsHitOver : public Condition<Monster>
{
public:
	bool OnTest(Monster* pMonster) override;
};
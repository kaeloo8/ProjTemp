#pragma once

#include "Condition.h"
#include "Monster.h"

class AttackDistance : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class CanSeeThePlayer : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class IsAtInitialPosition : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};


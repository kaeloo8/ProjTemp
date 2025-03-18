#pragma once

#include "Condition.h"
#include "Monster.h"

class RugbyManCondition_HaveTheBall : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class RugbyManCondition_TeamHasTheBall : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class RugbyManCondition_NearEnnemy : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class RugbyManCondition_NearMate : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class RugbyManCondition_EnnemieAveBall : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class RugbyManCondition_AllieAveBall : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class RugbyManCondition_DebugModeOn : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

class RugbyManCondition_devantlemecqualaballe : public Condition<Monster>
{
public:
	bool OnTest(Monster* owner) override;
};

#pragma once
#include "Util.h"

struct Position {
	Vector2f Pos;
};

struct Health {
	float HP;
};

struct Attack {
	float Damage;
};

struct Defence {
	float Protection;
};

struct Inventory {
	std::vector<Item> ItemsList;
};

struct Item {
	ItemInfo Items;
};

struct AI {
	enum Type { Passive, Aggressive, Defensive, None };
	Type behavior = None;
};

struct Speed {
	float SpeedLevel;
};

struct BoxColider {
	bool Solid;
};

struct CirColider {
	bool Solid;
};






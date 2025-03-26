#pragma once
#include <SFML/Graphics.hpp>

class Collider {
public:
    float x, y;
    bool Solid = false;
    virtual bool IsColliding(Collider* pOther) = 0;
};

class CircleCollider : public Collider {
public:
    float radius;
    bool IsColliding(Collider* pOther) override;
};

class AABBCollider : public Collider {
public:
    float xSize;
    float ySize;
    float xMin;
    float xMax;
    float yMin;
    float yMax;
    bool IsColliding(Collider* pOther) override;
};

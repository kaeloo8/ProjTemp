#pragma once
#include <SFML/Graphics.hpp>

class Collider {
public:
    float x, y;
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

class TriangleCollider : public Collider {
public:
    enum Orientation { BD, BG, HD, HG };
    Orientation type;
    float width, height;
    sf::Vector2f points[3];

    TriangleCollider(float x, float y, float w, float h, Orientation t);
    bool IsColliding(Collider* pOther) override;
    bool ContainsPoint(const sf::Vector2f& point);
};

class ModularCollider : public Collider {
public:
    std::vector<sf::Vector2f> points;
    ModularCollider(const std::vector<sf::Vector2f>& pts);
    bool IsColliding(Collider* pOther) override;
    bool SATCollision(ModularCollider* other);
};


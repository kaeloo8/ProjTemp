#pragma once
#include "pch.h"
#include "Collider.h"
#include <algorithm>
#include <cmath>

bool CircleCollider::IsColliding(Collider* pOther) {
    if (auto* circle = dynamic_cast<CircleCollider*>(pOther)) {
        float dx = x - circle->x;
        float dy = y - circle->y;
        float distanceSquared = dx * dx + dy * dy;
        float radiusSum = radius + circle->radius;
        return distanceSquared <= radiusSum * radiusSum;
    }
    else if (auto* aabb = dynamic_cast<AABBCollider*>(pOther)) {
        float closestX = std::clamp(x, aabb->xMin, aabb->xMax);
        float closestY = std::clamp(y, aabb->yMin, aabb->yMax);
        float dx = x - closestX;
        float dy = y - closestY;
        return dx * dx + dy * dy <= radius * radius;
    }
    return false;
}

bool AABBCollider::IsColliding(Collider* pOther) {
    if (auto* aabb = dynamic_cast<AABBCollider*>(pOther)) {
        return !(xMax < aabb->xMin || xMin > aabb->xMax ||
            yMax < aabb->yMin || yMin > aabb->yMax);
    }
    else if (auto* circle = dynamic_cast<CircleCollider*>(pOther)) {
        return circle->IsColliding(this);
    }
    return false;
}

TriangleCollider::TriangleCollider(float x, float y, float w, float h, Orientation t) {
    this->x = x;
    this->y = y;
    width = w;
    height = h;
    type = t;

    switch (type) {
    case BD:
        points[0] = { x, y };
        points[1] = { x + w, y + h };
        points[2] = { x, y + h };
        break;
    case BG:
        points[0] = { x, y };
        points[1] = { x + w, y };
        points[2] = { x, y + h };
        break;
    case HD:
        points[0] = { x, y };
        points[1] = { x + w, y };
        points[2] = { x + w, y + h };
        break;
    case HG:
        points[0] = { x + w, y };
        points[1] = { x + w, y + h };
        points[2] = { x, y + h };
        break;
    }
}

bool TriangleCollider::ContainsPoint(const sf::Vector2f& point) {
    auto Sign = [](sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
        };

    float d1 = Sign(point, points[0], points[1]);
    float d2 = Sign(point, points[1], points[2]);
    float d3 = Sign(point, points[2], points[0]);

    return (d1 >= 0 && d2 >= 0 && d3 >= 0) || (d1 <= 0 && d2 <= 0 && d3 <= 0);
}

bool TriangleCollider::IsColliding(Collider* pOther) {
    if (auto* aabb = dynamic_cast<AABBCollider*>(pOther)) {
        float left = aabb->xMin, right = aabb->xMax, top = aabb->yMin, bottom = aabb->yMax;
        return (aabb->xMin < right && aabb->xMax > left &&
            aabb->yMin < bottom && aabb->yMax > top);
    }
    return false;
}

ModularCollider::ModularCollider(const std::vector<sf::Vector2f>& pts) {
    points = pts;
}

bool ModularCollider::SATCollision(ModularCollider* other) {
    auto Project = [](const std::vector<sf::Vector2f>& verts, sf::Vector2f axis) {
        float min = verts[0].x * axis.x + verts[0].y * axis.y;
        float max = min;
        for (const auto& v : verts) {
            float projection = v.x * axis.x + v.y * axis.y;
            if (projection < min) min = projection;
            if (projection > max) max = projection;
        }
        return std::make_pair(min, max);
        };

    for (size_t i = 0; i < points.size(); i++) {
        sf::Vector2f edge = points[(i + 1) % points.size()] - points[i];
        sf::Vector2f axis = { -edge.y, edge.x };

        auto [minA, maxA] = Project(points, axis);
        auto [minB, maxB] = Project(other->points, axis);
        if (maxA < minB || maxB < minA)
            return false;
    }
    return true;
}

bool ModularCollider::IsColliding(Collider* pOther) {
    if (auto* modular = dynamic_cast<ModularCollider*>(pOther)) {
        return SATCollision(modular);
    }
    return false;
}
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

        bool verif = false;
        if (distanceSquared <= radiusSum * radiusSum)
            verif = true;

        return verif;
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
    }else         if (auto* circle = dynamic_cast<CircleCollider*>(pOther)) {

        return circle->IsColliding(this);
    }
    return false;
    return 0;
}


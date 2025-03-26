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
        // Calcul de la position la plus proche sur l'AABB
        float closestX = std::clamp(x, aabb->xMin, aabb->xMax);
        float closestY = std::clamp(y, aabb->yMin, aabb->yMax);

        // Calcul de la distance au carr� entre le cercle et l'AABB
        float dx = x - closestX;
        float dy = y - closestY;

        // Retourner si la distance au carr� est inf�rieure ou �gale au rayon au carr�
        return dx * dx + dy * dy <= radius * radius;
    }
    return false;
}


bool AABBCollider::IsColliding(Collider* pOther) {
    if (auto* aabb = dynamic_cast<AABBCollider*>(pOther)) {
        // V�rification de la collision AABB-AABB
        return !(xMax < aabb->xMin || xMin > aabb->xMax ||
            yMax < aabb->yMin || yMin > aabb->yMax);
    }
    else if (auto* circle = dynamic_cast<CircleCollider*>(pOther)) {
        // V�rification de la collision AABB-Cercle
        return circle->IsColliding(this);
    }
    return false;
}


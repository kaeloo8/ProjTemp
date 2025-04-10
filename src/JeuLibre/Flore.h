#pragma once
#include "Entity.h"
#include "Drop.h"
#include "Animator.h"

enum class FloreType {
    Tree,
    Stone
};

enum class StoneType {
    Stone,
    Coal,
    Iron,
    Gold,
    Diamond
};

class Flore : public Entity
{
public:
    Flore();
    ~Flore();

    int FloreLife;

    FloreType mFloreType;
    StoneType mStoneType;

    std::vector<Drop*> lDrop;

    void SetFloreLife(int _life);
    void HitFlore();
    void DeadTree();
    void DeadStone();

	void UpdateImagetype();

    void OnUpdate() override;
    void OnCollision(Entity* pCollidedWith) override;
    void SetImage(const char* path) override;
};

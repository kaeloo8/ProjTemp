#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace sf
{
    class Shape;
    class Color;
}

class Scene;

class Entity
{
    struct Target
    {
        sf::Vector2i position;
        float distance;
        bool isSet;
    };

protected:
    sf::CircleShape mShape;
    sf::Vector2f mDirection;
    sf::Texture mTexture;
    Target mTarget;
    bool haveHitbox;


public:
    int mHitboxWidth;
    int mHitboxHeight;

    std::string SceneName;
    sf::Sprite mSprite;
    Collider* mHitbox;

    bool isHide = false;
    float mX;
    float mY;
    float dirX;
    float dirY;
	float mSpeed;
    float mWidth;
    float mHeight;
    float mDefaultWidth;
    float mDefaultHeight;
    float timer;
    float timerAnnim;
    bool mToDestroy ;
    int mTag = -1;
    int Layout;

    int mLife;
    bool mIsAlive;
    bool mHasbeenHit = false;

	bool hasFixedLayout = false;

    void SetLife(int _Life);
    void HealLife(int _Heal);
    void DamageLife(int _Damage);

    void ChangeHide() { isHide = !isHide; }
    void SetHide(bool isVisible) { isHide = isVisible; }

    bool GoToDirection(float x, float y, float speed);
    bool GoToPosition(int x, int y, float speed);
    bool MoveHorizontal(int x, float speed);
    bool MoveVertical(int y, float speed);
    void StopGo();

    void SetPosition(float x, float y, float ratioX = 0.5f, float ratioY = 0.5f);
    void SetDirection(float x, float y, float speed = -1.f);
    void SetSpeed(float speed) { mSpeed = speed; }
    float GetSpeed();
    void SetTag(int tag) { mTag = tag; }
    void PlayAnimation(const char* path, float vitesseAnim);
    void SetScale(float sizeX, float sizeY);
    void SetSize(float width, float height);
    void AddRotation(float angle);
    void SetRotation(float angle);
    void GetSize();
    float GetDistanceTo(Entity* _Entity);
    float GetDistanceTo(float _x, float _y);
    void AddCircleHitbox();
    void AddAABBHitbox();
    void SolidHitbox();
    void SetHitboxSize(float x, float y);
    void SetHitboxSize(float _radius);
    void UpdateCollider();
    void DrawHitbox();
    void SetOrigin(float x, float y);
    float GetRadius() const { return mShape.getRadius(); }

    sf::Vector2f GetScale();
    sf::Vector2f GetPosition(float ratioX = 0.5f, float ratioY = 0.5f) const;
    sf::Shape* GetShape() { return &mShape; }
    sf::Sprite* GetSprite() { return &mSprite; }
    Collider* GetHitbox() { return mHitbox; }

    bool IsTag(int tag) const { return mTag == tag; }
    bool IsColliding(Entity* other) const;
    bool IsInsideCIRCLE(float x, float y) const;
    bool IsInsideAABB(float x, float y) const;

    void Destroy() { mToDestroy = true; }
    bool ToDestroy() const { return mToDestroy; }

    template<typename T>
    T* GetScene() const;

    Scene* GetScene() const;
    float GetDeltaTime() const;


    template<typename T>
    T* CreateEntity(float radius, const sf::Color& color);
    template<typename T>
    T* CreateEntity(const char* path);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
    virtual void OnInitialize() {};
    virtual void SetImage(const char* path);

private:
    void Update();
    void Initialize(float radius, const sf::Color& color);
    void Initialize(const char* path);

    friend class GameManager;
    friend Scene;
};

#include "Entity.inl"
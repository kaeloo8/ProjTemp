#include "pch.h"
#include "Entity.h"
#include "S0Menu.h"
#include "GameManager.h"
#include "Utils.h"
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Debug.h"

void Entity::Initialize(float radius, const sf::Color& color)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;
	mHitbox = nullptr;

	mShape.setRadius(radius);
	mShape.setFillColor(color);
	mDefaultWidth = radius * 2;
	mDefaultHeight = radius * 2;
	mWidth = mDefaultWidth;
	mHeight = mDefaultHeight;
	mHitboxWidth = mDefaultWidth;
	mHitboxHeight = mDefaultHeight;

	mTarget.isSet = false;
	SceneName = GetScene()->SceneName;
	haveHitbox = false;
}

void Entity::Initialize(const char* path)
{
	mDirection = sf::Vector2f(0.0f, 0.0f);
	mSpeed = 0.0f;
	mToDestroy = false;
	mTag = -1;
	mSprite.setTexture(GameManager::Get()->GetTexture(path));
	mHitbox = nullptr;

	mDefaultWidth = mSprite.getGlobalBounds().width;
	mDefaultHeight = mSprite.getGlobalBounds().height;
	mWidth = mDefaultWidth;
	mHeight = mDefaultHeight;
	mHitboxWidth = mDefaultWidth;
	mHitboxHeight = mDefaultHeight;

	mSprite.setOrigin(0.5f, 0.5f);

	mTarget.isSet = false;
	SceneName = GetScene()->SceneName;
	haveHitbox = false;
}

bool Entity::IsColliding(Entity* other) const {
	if (!mHitbox || !other->mHitbox)
		return false;

	return mHitbox->IsColliding(other->mHitbox);
}

bool Entity::IsInsideCIRCLE(float x, float y) const
{
	sf::Vector2f position = GetPosition();

	float dx = x - position.x;
	float dy = y - position.y;

	float radius = mShape.getRadius();

	return (dx * dx + dy * dy) < (radius * radius);
}

bool Entity::IsInsideAABB(float x, float y) const {
	sf::FloatRect bounds = mSprite.getGlobalBounds();
	return x >= bounds.left && x <= bounds.left + bounds.width &&
		y >= bounds.top && y <= bounds.top + bounds.height;
}

void Entity::SetPosition(float x, float y, float ratioX, float ratioY)
{
	x += (0.5f * mWidth) - (ratioX * mWidth);
	y += (0.5f * mHeight) - (ratioY * mHeight);

	mSprite.setPosition(x, y);
	mShape.setPosition(x, y);
}

sf::Vector2f Entity::GetPosition(float ratioX, float ratioY) const
{
	sf::Vector2f position = mShape.getPosition();

	position.x -= (0.5f * mWidth) - (ratioX * mWidth);
	position.y -= (0.5f * mHeight) - (ratioY * mHeight);

	return position;
}

void Entity::SetLife(int _Life)
{
	mIsAlive = true;
	mLife = _Life;
}

void Entity::HealLife(int _Heal)
{
	mLife = mLife + _Heal;
}

void Entity::DamageLife(int _Damage)
{
	mLife = mLife - _Damage;
}

bool Entity::GoToDirection(float x, float y, float speed)
{
	if (speed <= 0.f) {
		std::cerr << "GoToDirection: Speed must be positive." << std::endl;
		return false;
	}

	mSpeed = speed;

	sf::Vector2f position = GetPosition();
	sf::Vector2f direction = sf::Vector2f(x - position.x, y - position.y);

	bool success = Utils::Normalize(direction);
	if (!success) {
		return false;
	}

	mDirection = direction;
	return true;
}

bool Entity::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	sf::Vector2f position = GetPosition();

	mTarget.position = { x, y };
	mTarget.distance = Utils::GetDistance(position.x, position.y, x, y);
	mTarget.isSet = true;

	return true;
}

void Entity::StopGo()
{
	mDirection = { 0.f, 0.f };

	mTarget.isSet = false;
}

bool Entity::MoveHorizontal(int x, float speed)
{
	if (GoToDirection(x, GetPosition().y, speed) == false)
		return false;

	return true;
}

bool Entity::MoveVertical(int y, float speed)
{
	if (GoToDirection(GetPosition().x, y, speed) == false)
		return false;

	return true;
}

void Entity::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		mSpeed = speed;

	mDirection = sf::Vector2f(x, y);
}

float Entity::GetSpeed()
{
	return mSpeed;
}

void Entity::SetImage(const char* path)
{
	mSprite.setTexture(GameManager::Get()->GetTexture(path));
}

void Entity::PlayAnimation(const char* path, float vitesseAnim)
{

}

void Entity::SetScale(float scaleX, float scaleY)
{
	mSprite.setScale(scaleX, scaleY);
	mShape.setScale(scaleX, scaleY);

	mWidth = mDefaultWidth * scaleX;
	mHeight = mDefaultHeight * scaleY;
}

sf::Vector2f Entity::GetScale()
{
	float x = mWidth;
	float y = mHeight;
	sf::Vector2f scale = mSprite.getScale();
	return scale;
}

void Entity::SetSize(float width, float height)
{
	float scaleX = width / mDefaultWidth;
	float scaleY = height / mDefaultHeight;

	mSprite.setScale(scaleX, scaleY);
	mShape.setScale(scaleX, scaleY);

	mWidth = width;
	mHeight = height;

	mHitboxWidth = width;
	mHitboxHeight = height;
}

void Entity::AddRotation(float angle)
{
	mSprite.rotate(angle);
}

void Entity::SetRotation(float angle)
{
	mSprite.setRotation(angle);
}

void Entity::GetSize()
{
	sf::Vector2u sizeTexture = mTexture.getSize();
	mWidth = sizeTexture.x;
	mHeight = sizeTexture.y;
}

float Entity::GetDistanceTo(Entity* _Entity)
{
	float dx = GetPosition().x - _Entity->GetPosition().x;
	float dy = GetPosition().y - _Entity->GetPosition().y;
	float distanceSquared = dx * dx + dy * dy;

	return distanceSquared;
}

void Entity::AddCircleHitbox()
{
	mHitbox = new CircleCollider();
	if (mHitbox) {
		auto* circleCollider = dynamic_cast<CircleCollider*>(mHitbox);
		if (circleCollider) {
			circleCollider->x = GetPosition().x;
			circleCollider->y = GetPosition().y;
			circleCollider->radius = mWidth / 2;
		}
	}
	haveHitbox = true;
}

void Entity::AddAABBHitbox()
{
	mHitbox = new AABBCollider();
	if (mHitbox) {
		auto* aabbCollider = dynamic_cast<AABBCollider*>(mHitbox);
		if (aabbCollider) {
			sf::Vector2f position = GetPosition();

			int halfOffsetWidth = mHitboxWidth / 2;
			int halfOffsetHeight = mHitboxHeight / 2;

			aabbCollider->xMin = position.x - halfOffsetWidth;
			aabbCollider->yMin = position.y - halfOffsetHeight;
			aabbCollider->xMax = position.x + halfOffsetWidth;
			aabbCollider->yMax = position.y + halfOffsetHeight;
		}
	}
	haveHitbox = true;
}

void Entity::DrawHitbox() {
	if (auto* circleCollider = dynamic_cast<CircleCollider*>(mHitbox)) {
		// Centre du cercle ajusté par l'origine

		sf::Vector2f position = GetPosition();
	}

	if (auto* aabbCollider = dynamic_cast<AABBCollider*>(mHitbox)) {
		// Limites de l'AABB ajustées par l'origine

		sf::Vector2f position = GetPosition();

		int halfOffsetWidth = mHitboxWidth / 2;
		int halfOffsetHeight = mHitboxHeight / 2;

		aabbCollider->xMin = position.x - halfOffsetWidth;
		aabbCollider->yMin = position.y - halfOffsetHeight;
		aabbCollider->xMax = position.x + halfOffsetWidth;
		aabbCollider->yMax = position.y + halfOffsetHeight;

		aabbCollider->xSize = aabbCollider->xMax - aabbCollider->xMin;
		aabbCollider->ySize = aabbCollider->yMax - aabbCollider->yMin;

		Debug::DrawRectangle(aabbCollider->xMin, aabbCollider->yMin, aabbCollider->xSize, aabbCollider->ySize, sf::Color::Red);

	}
}

void Entity::SetOrigin(float x, float y)
{
	float originX = x * mDefaultWidth;

	float originY = y * mDefaultHeight;
	mSprite.setOrigin(originX, originY);
}

void Entity::SetHitboxSize(float width, float height)
{
	if (auto* aabbCollider = dynamic_cast<AABBCollider*>(mHitbox)) {

		mHitboxWidth = width;
		mHitboxHeight = height;

		sf::Vector2f position = GetPosition();

		int halfOffsetWidth = mHitboxWidth / 2;
		int halfOffsetHeight = mHitboxHeight / 2;

		aabbCollider->xMin = position.x - halfOffsetWidth;
		aabbCollider->yMin = position.y - halfOffsetHeight;
		aabbCollider->xMax = position.x + halfOffsetWidth;
		aabbCollider->yMax = position.y + halfOffsetHeight;
	}
}

void Entity::SetHitboxSize(float _radius)
{
	if (auto* circleCollider = dynamic_cast<CircleCollider*>(mHitbox)) {
		circleCollider->radius = _radius;

		sf::Vector2f position = GetPosition();
	}
}

void Entity::Update()
{
	float dt = GetDeltaTime();

	float distance = mSpeed * dt;

	sf::Vector2f normalizedDirection = mDirection;
	if (Utils::Normalize(normalizedDirection)) {
		sf::Vector2f translation = normalizedDirection * distance;

		mShape.move(translation);
		mSprite.move(translation);
	}

	if (mTarget.isSet)
	{
		mTarget.distance -= distance;

		if (mTarget.distance <= 0.f)
		{
			SetPosition(mTarget.position.x, mTarget.position.y);
			mDirection = sf::Vector2f(0.f, 0.f);
			mTarget.isSet = false;
		}
	}
	if (timerAnnim >= 0)
	{
		timerAnnim -= GetDeltaTime();
	}

	if (mLife <= 0 && mIsAlive == true)
	{
		Destroy();
	}

	if (haveHitbox) {
		DrawHitbox();
	}


	OnUpdate();

}

Scene* Entity::GetScene() const
{
	return GameManager::Get()->GetScene();
}

float Entity::GetDeltaTime() const
{
	return GameManager::Get()->GetDeltaTime();
}

void Entity::UpdateCollider()
{
	if (mHitbox) {

		if (auto* circleCollider = dynamic_cast<CircleCollider*>(mHitbox)) {

			sf::Vector2f position = GetPosition();

			circleCollider->x = position.x;
			circleCollider->y = position.y;
		}
		else if (auto* aabbCollider = dynamic_cast<AABBCollider*>(mHitbox)) {
			// Ajuste les limites de l'AABB en tenant compte de l'origine

			sf::Vector2f position = GetPosition();

			int halfOffsetWidth = mHitboxWidth / 2;
			int halfOffsetHeight = mHitboxHeight / 2;

			aabbCollider->xMin = position.x - halfOffsetWidth;
			aabbCollider->yMin = position.y - halfOffsetHeight;
			aabbCollider->xMax = position.x + halfOffsetWidth;
			aabbCollider->yMax = position.y + halfOffsetHeight;
		}
	}
}

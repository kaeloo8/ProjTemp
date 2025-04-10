#include "pch.h"
#include "Drop.h"

Drop::Drop() {
	mItemDrop = mSprite;
	mLifeTime = 300.0f;
	angle = static_cast<float>(rand() % 360);
}

bool Drop::IsCollected()
{
	return mIsCollected;
}

void Drop::SetVelocity(float speed)
{
	Velocity.x = (speed * cos(angle));
	Velocity.y = (speed * sin(angle));

}

void Drop::IsDroped()
{
	mIsDropped = true;
	
	// Réduit le temps de vie
	mLifeTime -= GetDeltaTime();
}

void Drop::OnCollision(Entity* pOther)
{
	if (pOther) {
		mIsCollected = true;
		std::cout << "Item Collected" << std::endl;
		Destroy();
	}
}

void Drop::SetImage(const char* path)
{
	mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

void Drop::OnUpdate()
{
	IsDroped();

	Velocity *= 0.9f;

	SetPosition(GetPosition().x + Velocity.x, GetPosition().y + Velocity.y);

	if (mLifeTime <= 0)
	{
		Destroy();
		return;
	}
}



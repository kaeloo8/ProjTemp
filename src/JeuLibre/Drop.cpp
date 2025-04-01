#include "pch.h"
#include "Drop.h"

Drop::Drop() {
	mItemDrop = mSprite;
	mLifeTime = 10.0f;
}

bool Drop::IsCollected()
{
	return mIsCollected;
}

void Drop::ItemDroped()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		if (!KeyGPressed) {
			mIsDropped = !mIsDropped;
			KeyGPressed = true;
			if (mIsDropped)
			{
				
			}
		}
		else
		{
			KeyGPressed = false;
		}
	}
	Velocity.x *= 0.98f;

	// Réduit le temps de vie
	mLifeTime -= GetDeltaTime();

}

void Drop::OnCollision(Entity* pOther)
{
	if (pOther) {
		mIsCollected = true;
		Destroy();
	}
}

void Drop::OnUpdate()
{
	ItemDroped();

	if (mLifeTime <= 0)
	{
		Destroy();
		return;
	}

	OnCollision();
}



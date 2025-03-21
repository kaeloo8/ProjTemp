#include "pch.h"
#include "UI.h"

UI::UI()
{
	mSprite = mImage;
}

bool UI::HandleClick(float mouseX, float mouseY)
{
	if (mSprite.getGlobalBounds().contains(mouseX, mouseY))
	{
		std::cout << "Retour Menu" << std::endl;
		GameManager::Get()->LaunchScene<S0Menu>();
	}
	
}

void UI::Open()
{

}

void UI::Close() 
{

}

void UI::SetPointer(Pointer* _pointer)
{
	 mPointer = _pointer;
}

void UI::HangToEntity(Entity* _parent)
{
	mParent = _parent;
}

void UI::GapX(float X)
{
	mGapX = X;
}

void UI::GapY(float Y)
{
	mGapY = Y;
}

void UI::SetGap(float X, float Y)
{
	mGapX = X;
	mGapY = Y;
}

void UI::OnUpdate()
{
	if (mParent != nullptr)
	{
		SetPosition(mParent->GetPosition().x + mGapX, mParent->GetPosition().y + mGapY);
	}
}

void UI::OnCollision(Entity* pCollidedWith)
{
	if (pCollidedWith = mPointer )
	{
		std::cout << "souris" << std::endl;
	}
}

void UI::SetImage(const char* path)
{
}

#include "pch.h"
#include "UI.h"

UI::UI()
{
	mDefaultImage = mSprite;
	//cDefaultImage =
	cHoverImage = cDefaultImage + "_pressed";
	IsClickable = false;
}

bool UI::HandleClick(float mouseX, float mouseY)
{
	if (IsClickable == false) { return 0; }

	if (mSprite.getGlobalBounds().contains(mouseX, mouseY))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

bool UI::HandleClick(sf::Vector2f MousePos)
{
	if (mSprite.getGlobalBounds().contains(MousePos))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return false;
}

bool UI::HandleHover(sf::Vector2f MousePos)
{
	if (mSprite.getGlobalBounds().contains(MousePos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UI::Open()
{
	std::cout << "Open" << std::endl;

}

void UI::Close() 
{
	std::cout << "Close" << std::endl;
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
	if (IsClickable)
	{
		if (HandleHover(mPointer->worldPos))
		{
			SetImage(cHoverImage.c_str());
		}
		else
		{
			SetImage(cDefaultImage.c_str());
		}
	}
}

void UI::OnCollision(Entity* pCollidedWith)
{
	if (pCollidedWith = mPointer )
	{

	}
}

void UI::SetImage(const char* path)
{
	mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

#include "pch.h"
#include "UI.h"

UI::UI()
{
	mSprite = mImage;
}

void UI::HandleClick(float mouseX, float mouseY)
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

void UI::OnUpdate()
{
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

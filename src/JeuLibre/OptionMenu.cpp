#include "pch.h"
#include "OptionMenu.h"

OptionMenu::OptionMenu()
{

}

bool OptionMenu::HandleClick(float mouseX, float mouseY)
{
	if (!MenuOpen) return 0;

	for (auto& element : uiElements) {
		//element->HandleClick(mouseX, mouseY);
	}
	return false;
}

void OptionMenu::AddUIElement(UI* element)
{
	uiElements.push_back(element);
}

void OptionMenu::Open()
{
	MenuOpen = true;
}

void OptionMenu::Close()
{
	MenuOpen = false;
}

void OptionMenu::OnUpdate() {

}

void OptionMenu::OnCollision(Entity* pCollidedWith) {

}

void OptionMenu::SetImage(const char* path) {

}

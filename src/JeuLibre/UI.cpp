#include "pch.h"
#include "UI.h"

UI::UI(){
	mDefaultImage = mSprite;
	//cDefaultImage =
	cHoverImage = cDefaultImage + "_pressed";
	IsClickable = true;
}

void UI::cBouton(sf::Vector2f pos, sf::Vector2f size, char* path) {
	Entity* E;	
	E = CreateEntity<Entity>(path);
	E->SetSize(size.x, size.y);
	E->SetPosition(pos.x, pos.y);
	E->Layout = 11;
	E->AddAABBHitbox();
	E->SetHitboxSize(size.x, size.y);
	element e;
	e.En = E;
	e.NameI = path;
	e.NumberI = 0;

}

void UI::cBouton(sf::Vector2f pos, int sx, int sy, char* path) {
	Entity* E;
	E = CreateEntity<Entity>(path);
	E->SetSize(sx, sy);
	E->SetPosition(pos.x, pos.y);
	E->Layout = 11;
	E->AddAABBHitbox();
	E->SetHitboxSize(sx, sy);
	element e;
	e.En = E;
	e.NameI = path;
	e.NumberI = 0;
}

void UI::cBouton(int x, int y, sf::Vector2f size, char* path) {
	Entity* E;
	E = CreateEntity<Entity>(path);
	E->SetSize(size.x, size.y);
	E->SetPosition(x, y);
	E->Layout = 11;
	E->AddAABBHitbox();
	E->SetHitboxSize(size.x, size.y);
	element e;
	e.En = E;
	e.NameI = path;
	e.NumberI = 0;
}

void UI::cBouton(int x, int y, int sx, int sy, char* path) {
	Entity* E;
	E = CreateEntity<Entity>(path);
	E->SetSize(sx, sy);
	E->SetPosition(x, y);
	E->Layout = 11;
	E->AddAABBHitbox();
	E->SetHitboxSize(sx, sy);
	element e;
	e.En = E;
	e.NameI = path;
	e.NumberI = 0;
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

void UI::SetPointer(Pointer* _pointer) {
	lPointer = _pointer;
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

void UI::Open() {

}

void UI::Close() {

}

void UI::OnUpdate() {

	if (IsClickable)
	{
		if (HandleHover(lPointer->worldPos))
		{
			SetImage(cHoverImage.c_str());
		}
		else
		{
			SetImage(cDefaultImage.c_str());
		}
	}
}

void UI::OnCollision(Entity* pCollidedWith) {

}

void UI::SetImage(const char* path) {
	mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}
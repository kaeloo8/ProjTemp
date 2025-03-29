#include "pch.h"
#include "UI.h"

UI::UI(){

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

void UI::SetPointer(Pointer* _pointer) {

}

void UI::Open() {

}

void UI::Close() {

}

void UI::OnUpdate() {

}

void UI::OnCollision(Entity* pCollidedWith) {

}

void UI::SetImage(const char* path) {

}
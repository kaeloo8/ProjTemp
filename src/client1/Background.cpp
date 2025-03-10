#include "pch.h"
#include "Background.h"
#include <iostream>
#include "ShootThemUp.h"

void Background::Update(float deltaTime) {
	this->SetPosition(GetScene<ShootThemUp>()->cam.GetPosX(), GetScene<ShootThemUp>()->cam.GetPosY());
	std::cout << "update BG" << std::endl;
}

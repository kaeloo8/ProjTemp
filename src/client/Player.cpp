#include "pch.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ShootThemUp.h"
#include "Debug.h"

#define MAXHP 100
#define PLAYERSPEED 100
#define COOLDOWNGUN 0.2

Player::Player() {
	MaxLife = MAXHP;
	PlayerSpeed = PLAYERSPEED;
	Life = MaxLife;
	CanShoot = true;

	SetPosition(0, 0);
}

Player::Player(sf::Vector2f PosPlayer)
{
	MaxLife = MAXHP;
	PlayerSpeed = PLAYERSPEED;
	Life = MaxLife;
	CanShoot = true;
	SetPosition(PosPlayer.x , PosPlayer.y);
}

void Player::OrientToMouse(sf::Vector2i mPos)
{
	sf::Vector2f playerPos = this->GetPosition();

	float deltaX = static_cast<float>(mPos.x) - playerPos.x;
	float deltaY = static_cast<float>(mPos.y) - playerPos.y;

	float angle = std::atan2(deltaY, deltaX) * 180 / 3.14159f;
	Angle = angle;
	this->SetRotation(angle); 
}

void Player::OrientTo(float rad) {
	this->SetRotation(rad);
}

void Player::SetSkin()
{
	
}

void Player::DamagePlayer(float damage)
{
	Life = Life - damage;
}

void Player::HealPlayer(float heal)
{
	Life = Life + heal;
}

void Player::OnUpdate()
{
	if (!CanShoot) {
		if (Cooldown > 0) {
			Cooldown -= GetDeltaTime();
		}
		else
		{
			CanShoot = true;
		}
	}
	if (this->mTag == ShootThemUp::Tag::tEnnemie) {
		this->SetPosition(GetScene<ShootThemUp>()->cam.GetPosX() + PosWorldX, GetScene<ShootThemUp>()->cam.GetPosY() + PosWorldY);
		Debug::DrawTextDE(GetScene<ShootThemUp>()->cam.GetPosX() + PosWorldX, GetScene<ShootThemUp>()->cam.GetPosY() + PosWorldY - 50, Name, 0.2, 0.2, sf::Color::White);
	}
	

}

bool Player::Shoot() {
	if (!CanShoot) {
		return false;
	}
	CanShoot = false;
	Cooldown = COOLDOWNGUN;
	return true;
}

void Player::SetLife(float l) {
	this->Life = l;
}

float Player::GetRad() {
	return Angle;
}

float Player::GetLife() {
	return Life;
}
std::string Player::GetName() {
	return Name;
}
void Player::SetName(std::string N) {
	Name = N;
}
#include "pch.h"
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "ShootThemUp.h"
#include <format>  

#define LIFETIME 3
#define SPEED 10

Bullet::Bullet() {
    LifeTime = LIFETIME;
    Speed = SPEED;
}

Bullet::Bullet(sf::Vector2f PosSpawn)
{
    LifeTime = LIFETIME;
    Speed = SPEED;
}
void Bullet::Init(float _x, float _y, float _tox, float _toy, Online* reseau) {
    tox = _tox;
    toy = _toy;
    posx = _x;
    posy = _y;

    OnLine = reseau;

    sf::Vector2f Pos = this->GetPosition();

    float deltaX = static_cast<float>(_tox) - Pos.x;
    float deltaY = static_cast<float>(_toy) - Pos.y;

    float angle = std::atan2(deltaY, deltaX) * 180 / 3.14159f;

    Angle = angle;

    this->SetRotation(angle);

    
}

void Bullet::OnUpdate() {
    sf::Vector2f direction(tox, toy);

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length;
    }

    posx += direction.x * Speed * 1.0f;
    posy += direction.y * Speed * 1.0f;

    this->SetPosition(posx + GetScene<ShootThemUp>()->cam.GetPosX(), posy + GetScene<ShootThemUp>()->cam.GetPosY());
    if (LifeTime <= 0) {
        this->Destroy();
    }
    LifeTime -= GetDeltaTime();
}

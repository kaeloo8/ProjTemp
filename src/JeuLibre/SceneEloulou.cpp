#include "pch.h"
#include "SceneEloulou.h"
#include "S1Ville.h"
#include "S0Menu.h"
#include <iostream>

void SceneEloulou::OnInitialize() {
    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);
    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.12) / 100, (Win->getSize().x * 0.12) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->Layout = 10;

    lPlayer = CreateEntity<Player>("base_idle_strip9");
    lPlayer->SetScale(3, 3);
    lPlayer->SetOrigin(0.5f, 0.5f);
    lPlayer->SetPosition((GetWindowWidth() / 2) - lPlayer->GetSprite()->getGlobalBounds().width, (GetWindowHeight() / 2));
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(25, 20);
    lPlayer->Layout = 1;
    lPlayer->mSpeed = 1;
}
void SceneEloulou::OnEvent(const sf::Event& event) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (!KeyEscPressed) {
            std::cout << "Retour Menu" << std::endl;
            GameManager::Get()->LaunchScene<S0Menu>();
        }
    }
    else {
        KeyEscPressed = false;
    }
}

void SceneEloulou::SetName() {
    SceneName = "SceneEloulou";
}

void SceneEloulou::OnUpdate() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x, mousePos.y);

    float velocityX = 0.f;
    float velocityY = 0.f;

    // Si on est en train de dasher, on bloque tout mouvement supplémentaire
    if (lPlayer->isDashing) {
        velocityX = lPlayer->dashVelocityX;
        velocityY = lPlayer->dashVelocityY;
        lPlayer->dashTimer -= 1.f / 60.f;

        // Arrêter le dash lorsque le timer est expiré
        if (lPlayer->dashTimer <= 0) {
            lPlayer->isDashing = false;
        }
        // Si le dash est en cours, on ne fait pas d'autres mouvements
        lPlayer->GoToPosition(lPlayer->GetPosition().x + velocityX * lPlayer->mSpeed,
            lPlayer->GetPosition().y + velocityY * lPlayer->mSpeed,
            500);
        return; // Retourner ici empêche le mouvement normal en dehors du dash
    }

    // Sinon, on continue avec le mouvement normal
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocityY -= 5.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocityY += 5.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocityX -= 5.f;
        lPlayer->GetSprite()->setScale(-std::abs(lPlayer->GetSprite()->getScale().x), lPlayer->GetSprite()->getScale().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocityX += 5.f;
        lPlayer->GetSprite()->setScale(std::abs(lPlayer->GetSprite()->getScale().x), lPlayer->GetSprite()->getScale().y);
    }

    // Normalisation du mouvement pour éviter des valeurs trop grandes
    float magnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY);
    if (magnitude > 0) {
        velocityX /= magnitude;
        velocityY /= magnitude;
    }

    // Stocke la dernière direction uniquement si on bouge
    if (velocityX != 0 || velocityY != 0) {
        lPlayer->lastVelocityX = velocityX;
        lPlayer->lastVelocityY = velocityY;

        // Gestion du sprint
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            lPlayer->mSpeed = 300;
            lPlayer->isSprinting = true;
        }
        else {
            lPlayer->mSpeed = 150;
            lPlayer->isSprinting = false;
        }
        lPlayer->isMoving = true;
    }
    else {
        lPlayer->isMoving = false;
    }

    // Réduction du cooldown au fil du temps
    if (lPlayer->dashCooldown > 0) {
        lPlayer->dashCooldown -= 1.f / 60.f; // Supposons 60 FPS
    }

    // DASH LOGIC avec cooldown
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !lPlayer->isDashing && lPlayer->dashCooldown <= 0) {
        lPlayer->isDashing = true;
        lPlayer->dashTimer = 0.5f;  // Durée du dash
        lPlayer->dashVelocityX = lPlayer->lastVelocityX * 30;  // Boost du dash
        lPlayer->dashVelocityY = lPlayer->lastVelocityY * 30;
        lPlayer->dashCooldown = lPlayer->maxDashCooldown; // Active le cooldown
    }

    // Déplacement normal si pas de dash
    if (!lPlayer->isDashing) {
        lPlayer->GoToPosition(lPlayer->GetPosition().x + velocityX * lPlayer->mSpeed,
            lPlayer->GetPosition().y + velocityY * lPlayer->mSpeed,
            lPlayer->mSpeed);
    }
}

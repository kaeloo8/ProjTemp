#include "pch.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr), mDashAnimator(nullptr), mState(PlayerState::Idle)
{
    // Cr�ation de l'entit� PlayerHair (cheveux du joueur)
    PlayerHair = CreateEntity<PlayerPart>(PlayerHaircut);
    PlayerHair->SetScale(3, 3);
    PlayerHair->SetOrigin(0.5, 0.5);
    PlayerHair->Layout = 10;

    // Cr�ation des animations de base
    mWalkAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_walk_strip8"),
        8,    // nombre de frames walk
        0.1f  // dur�e par frame walk
    );

    mIdleAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_idle_strip9"),
        9,    // nombre de frames idle
        0.2f  // dur�e par frame idle
    );

    mSprintAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_run_strip8"),
        8,    // nombre de frames sprint
        0.08f // dur�e par frame sprint
    );

    mDashAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_roll_strip10"),
        10,    // nombre de frames roll
        0.1f  // dur�e par frame roll
    );
}

Player::~Player()
{
    delete mWalkAnimator;
    delete mIdleAnimator;
    delete mSprintAnimator;
}

void Player::SetState(PlayerState state)
{
    if (mState != state)
    {
        mState = state;

        // Modification de l'image et r�initialisation de l'animation en fonction de l'�tat
        if (mState == PlayerState::Idle) {
            SetImage("base_idle_strip9");
            if (mIdleAnimator) mIdleAnimator->Reset();
        }
        else if (mState == PlayerState::Walking) {
            SetImage("base_walk_strip8");
            if (mWalkAnimator) mWalkAnimator->Reset();
        }
        else if (mState == PlayerState::Sprinting) {
            SetImage("base_run_strip8");
            if (mSprintAnimator) mSprintAnimator->Reset();
        }
        else if (mState == PlayerState::Dashing) {
            SetImage("base_roll_strip10");
            if (mDashAnimator) mDashAnimator->Reset();
        }
    }
}

void Player::FaceLeft()
{
    // Inverser l'orientation du sprite du joueur (gauche)
    GetSprite()->setScale(-std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(-std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::FaceRight()
{
    // Inverser l'orientation du sprite du joueur (droite)
    GetSprite()->setScale(std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::OnUpdate()
{
    PlayerHair->SetPosition(GetPosition().x, GetPosition().y);

    float velocityX = 0.f;
    float velocityY = 0.f;

	OnAnimationUpdate();
    // Gestion du dash
    if (isDashing) {
        velocityX = dashVelocityX;
        velocityY = dashVelocityY;
        dashTimer -= 1.f / 60.f;

        if (dashTimer <= 0) {
            isDashing = false;
        }

        GoToPosition(GetPosition().x + velocityX * mSpeed,
                      GetPosition().y + velocityY * mSpeed,
                      500);
        return;
    }

    // Gestion des d�placements classiques
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocityY -= 5.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocityY += 5.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocityX -= 5.f;
        FaceLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocityX += 5.f;
        FaceRight();
    }

    // Normalisation du mouvement
    float magnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY);
    if (magnitude > 0) {
        velocityX /= magnitude;
        velocityY /= magnitude;
    }

    if (velocityX != 0 || velocityY != 0) {
        lastVelocityX = velocityX;
        lastVelocityY = velocityY;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            mSpeed = 300;
            isSprinting = true;
        }
        else {
            mSpeed = 150;
            isSprinting = false;
        }
        isMoving = true;
    }
    else {
        isMoving = false;
    }

    // Cooldown du dash
    if (dashCooldown > 0) {
        dashCooldown -= 1.f / 60.f; // 60 FPS suppos�s
    }

    // Logique du dash
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isDashing && dashCooldown <= 0) {
        isDashing = true;
        dashTimer = 0.5f;  // Dur�e du dash
        dashVelocityX = lastVelocityX * 30;
        dashVelocityY = lastVelocityY * 30;
        dashCooldown = maxDashCooldown;
    }

    if (!isDashing) {
        GoToPosition(GetPosition().x + velocityX * mSpeed,
                      GetPosition().y + velocityY * mSpeed,
                      mSpeed);
    }

}

void Player::OnAnimationUpdate()
{
    float dt = GetDeltaTime();
    // Gestion des �tats (Idle, Walking, Sprinting, Dashing)
    if (isDashing) {
        PlayerHair->SetState(PlayerPartState::Dashing);
        SetState(PlayerState::Dashing);
    }
    else if (isMoving) {
        if (isSprinting) {
            PlayerHair->SetState(PlayerPartState::Sprinting);
            SetState(PlayerState::Sprinting);
        }
        else {
            PlayerHair->SetState(PlayerPartState::Walking);
            SetState(PlayerState::Walking);
        }
    }
    else {
        PlayerHair->SetState(PlayerPartState::Idle);
        SetState(PlayerState::Idle);
    }

    // Mise � jour des animations selon l'�tat
    if (mState == PlayerState::Walking && mWalkAnimator) {
        mWalkAnimator->Update(dt);
    }
    else if (mState == PlayerState::Idle && mIdleAnimator) {
        mIdleAnimator->Update(dt);
    }
    else if (mState == PlayerState::Sprinting && mSprintAnimator) {
        mSprintAnimator->Update(dt);
    }
    else if (mState == PlayerState::Dashing && mDashAnimator) {
        mDashAnimator->Update(dt);
    }
}

void Player::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

void Player::OnCollision(Entity* pCollidedWith)
{
    // Gestion des collisions...
}

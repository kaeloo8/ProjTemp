#include "pch.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr), mDashAnimator(nullptr), mAttackAnimator(nullptr), mState(PlayerState::Idle)
{

    mLife = 100;
    mIsAlive = true;
    // INITIALISATION CHEVEUX 
    PlayerHair = CreateEntity<PlayerPart>("0");
    PlayerHair->InitBodyPart("bowlhair");
    PlayerHair->SetScale(3, 3);
    PlayerHair->SetOrigin(0.5, 0.5);
    PlayerHair->Layout = 10;

    // INITIALISATION MAIN
    PlayerHand = CreateEntity<PlayerPart>("0");
    PlayerHand->InitBodyPart("tools");
    PlayerHand->SetScale(3, 3);
    PlayerHand->SetOrigin(0.5, 0.5);
    PlayerHand->Layout = 11;


    // Création des animations de base
    mWalkAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_walk_strip8"),
        8,    // nombre de frames walk
        0.1f  // durée par frame walk
    );

    mIdleAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_idle_strip9"),
        9,    // nombre de frames idle
        0.2f  // durée par frame idle
    );

    mSprintAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_run_strip8"),
        8,    // nombre de frames sprint
        0.08f // durée par frame sprint
    );

    mDashAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_roll_strip10"),
        10,    // nombre de frames roll
        0.1f  // durée par frame roll
    );

    mAttackAnimator = new Animator(
        &mSprite,
        *GameManager::Get()->GetAssetManager(),
        std::string("base_attack_strip10"),
        10,    // nombre de frames roll
        0.07f  // durée par frame roll
    );
}

Player::~Player()
{
    delete mWalkAnimator;
    delete mIdleAnimator;
    delete mSprintAnimator;
    delete mDashAnimator;
    delete mAttackAnimator;
}


void Player::SetState(PlayerState state)
{
    if (mState != state)
    {
        mState = state;

        // Modification de l'image et réinitialisation de l'animation en fonction de l'état
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
        else if (mState == PlayerState::Attacking) {
            SetImage("base_attack_strip10"); 
            if (mAttackAnimator) mAttackAnimator->Reset();
        }

    }
}

void Player::FaceLeft()
{
    // Inverser l'orientation du sprite du joueur (gauche)
    GetSprite()->setScale(-std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(-std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
    PlayerHand->GetSprite()->setScale(-std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::FaceRight()
{
    // Inverser l'orientation du sprite du joueur (droite)
    GetSprite()->setScale(std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
    PlayerHand->GetSprite()->setScale(std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::OnUpdate()
{
    //std::cout << mLife << std::endl;

    PlayerHair->SetPosition(GetPosition().x, GetPosition().y);
    PlayerHand->SetPosition(GetPosition().x, GetPosition().y);

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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !isAttacking && !BuildingMode) {
        isAttacking = true;
        attackTimer = attackDuration; // Durée de l'attaque
        SetState(PlayerState::Attacking); // Changer l'état du joueur
    }

    // Mettre à jour le timer de l'attaque
    if (isAttacking) {
        attackTimer -= GetDeltaTime(); 
        if (attackTimer <= 0) {
            isAttacking = false; 
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        ToogleMode();
    }

    // Gestion des déplacements classiques
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
        if (isAttacking)
        {
            mSpeed = 15;
        } 
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
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
        dashCooldown -= 1.f / 60.f; // 60 FPS supposés
    }

    // Logique du dash
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isDashing && dashCooldown <= 0 && !isAttacking) {
        isDashing = true;
        dashTimer = 0.5f;  // Durée du dash
        dashVelocityX = lastVelocityX * 30;
        dashVelocityY = lastVelocityY * 30;
        dashCooldown = maxDashCooldown;
    }

    if (!isDashing) {
        GoToPosition(GetPosition().x + velocityX * mSpeed,
                      GetPosition().y + velocityY * mSpeed,
                      mSpeed);
    }

    // Gestion des états (Idle, Walking, Sprinting, Dashing)
    if (isAttacking)
    {
        PlayerHair->SetState(PlayerPartState::Attacking);
        PlayerHand->SetState(PlayerPartState::Attacking);
        SetState(PlayerState::Attacking);
        return;
    }
    if (isDashing) {
        PlayerHair->SetState(PlayerPartState::Dashing);
        PlayerHand->SetState(PlayerPartState::Dashing);
        SetState(PlayerState::Dashing);
    }
    else if (isMoving) {
        if (isSprinting) {
            PlayerHair->SetState(PlayerPartState::Sprinting);
            PlayerHand->SetState(PlayerPartState::Sprinting);
            SetState(PlayerState::Sprinting);
        }
        else {
            PlayerHair->SetState(PlayerPartState::Walking);
            PlayerHand->SetState(PlayerPartState::Walking);
            SetState(PlayerState::Walking);
        }
    }
    else {
        PlayerHair->SetState(PlayerPartState::Idle);
        PlayerHand->SetState(PlayerPartState::Idle);
        SetState(PlayerState::Idle);
    }
}

void Player::OnAnimationUpdate()
{
    float dt = GetDeltaTime();

    // Mise à jour des animations selon l'état
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
    else if (mState == PlayerState::Attacking && mAttackAnimator) {
        mAttackAnimator->Update(dt);
    }


}

void Player::SetImage(const char* path)
{
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

void Player::ChangeHaircut(const char* haircut)
{
	PlayerHair->InitBodyPart(haircut);
}

void Player::ToogleMode()
{
    BuildingMode = !BuildingMode;
}

void Player::OnCollision(Entity* pCollidedWith)
{
    //
}

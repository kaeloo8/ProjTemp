#include "pch.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr), mDashAnimator(nullptr), mAttackAnimator(nullptr), mState(PlayerState::sIdle)
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

    mTag = GameManager::Tag::tPlayer;
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
        if (mState == PlayerState::sIdle) {
            SetImage("base_idle_strip9");
            if (mIdleAnimator) mIdleAnimator->Reset();
        }
        else if (mState == PlayerState::sWalking) {
            SetImage("base_walk_strip8");
            if (mWalkAnimator) mWalkAnimator->Reset();
        }
        else if (mState == PlayerState::sSprinting) {
            SetImage("base_run_strip8");
            if (mSprintAnimator) mSprintAnimator->Reset();
        }
        else if (mState == PlayerState::sDashing) {
            SetImage("base_roll_strip10");
            if (mDashAnimator) mDashAnimator->Reset();
        }
        else if (mState == PlayerState::sAttacking) {
            SetImage("base_attack_strip10"); 
            if (mAttackAnimator) mAttackAnimator->Reset();
        }

    }
}

void Player::FaceLeft()
{
    isTurn = true;
    // Inverser l'orientation du sprite du joueur (gauche)
    GetSprite()->setScale(-std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(-std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
    PlayerHand->GetSprite()->setScale(-std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::FaceRight()
{
    isTurn = false;
    // Inverser l'orientation du sprite du joueur (droite)
    GetSprite()->setScale(std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
    PlayerHand->GetSprite()->setScale(std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::OnUpdate()
{
    if (AttackArea != NULL) {
        if (isTurn) {
            AttackArea->SetPosition(this->GetPosition().x - DamageDistance, this->GetPosition().y - DamageDistance / 2);
        }
        else {
            AttackArea->SetPosition(this->GetPosition().x + DamageDistance, this->GetPosition().y - DamageDistance / 2);
        }
    }

    //std::cout << mLife << std::endl;
    if (tBeforSwitch > 0)
        tBeforSwitch -= GameManager::Get()->GetDeltaTime();

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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !isAttacking) {
        isAttacking = true;
        attackTimer = attackDuration; // Durée de l'attaque
        SetState(PlayerState::sAttacking); // Changer l'état du joueur
        cAttack();
    }

    // Mettre à jour le timer de l'attaque
    if (isAttacking) {
        attackTimer -= GetDeltaTime(); 
        if (attackTimer <= 0) {
            isAttacking = false; 
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)&& tBeforSwitch <=0) {
        ToogleMode();
        tBeforSwitch = 2;
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
        SetState(PlayerState::sAttacking);
        return;
    }
    if (isDashing) {
        PlayerHair->SetState(PlayerPartState::Dashing);
        PlayerHand->SetState(PlayerPartState::Dashing);
        SetState(PlayerState::sDashing);
    }
    else if (isMoving) {
        if (isSprinting) {
            PlayerHair->SetState(PlayerPartState::Sprinting);
            PlayerHand->SetState(PlayerPartState::Sprinting);
            SetState(PlayerState::sSprinting);
        }
        else {
            PlayerHair->SetState(PlayerPartState::Walking);
            PlayerHand->SetState(PlayerPartState::Walking);
            SetState(PlayerState::sWalking);
        }
    }
    else {
        PlayerHair->SetState(PlayerPartState::Idle);
        PlayerHand->SetState(PlayerPartState::Idle);
        SetState(PlayerState::sIdle);
    }
}

void Player::OnAnimationUpdate()
{
    float dt = GetDeltaTime();

    // Mise à jour des animations selon l'état
    if (mState == PlayerState::sWalking && mWalkAnimator) {
        mWalkAnimator->Update(dt);
    }
    else if (mState == PlayerState::sIdle && mIdleAnimator) {
        mIdleAnimator->Update(dt);
    }
    else if (mState == PlayerState::sSprinting && mSprintAnimator) {
        mSprintAnimator->Update(dt);
    }
    else if (mState == PlayerState::sDashing && mDashAnimator) {
        mDashAnimator->Update(dt);
    }
    else if (mState == PlayerState::sAttacking && mAttackAnimator) {
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
    GetScene()->IsInBuildingMode = !GetScene()->IsInBuildingMode;
    std::cout << GetScene()->IsInBuildingMode << std::endl;
}

void Player::OnCollision(Entity* pCollidedWith)
{
    // On suppose que l'autre entité est solide
    if (pCollidedWith->mHitbox->Solid)
    {
        // On tente de récupérer les AABBCollider pour le joueur et l'objet
        AABBCollider* playerCollider = dynamic_cast<AABBCollider*>(this->mHitbox);
        AABBCollider* otherCollider = dynamic_cast<AABBCollider*>(pCollidedWith->mHitbox);
        if (!playerCollider || !otherCollider)
            return; // Assurez-vous que les cast sont valides

        // Calculer l'intersection sur l'axe horizontal et vertical
        float intersectWidth = std::max(0.f, std::min(playerCollider->xMax, otherCollider->xMax) -
            std::max(playerCollider->xMin, otherCollider->xMin));
        float intersectHeight = std::max(0.f, std::min(playerCollider->yMax, otherCollider->yMax) -
            std::max(playerCollider->yMin, otherCollider->yMin));

        if (intersectWidth > 0.f && intersectHeight > 0.f)
        {
            sf::Vector2f pos = GetPosition();

            if (intersectWidth < intersectHeight)
            {
                if (playerCollider->xMin < otherCollider->xMin)
                {
                    float offset = playerCollider->xMax - otherCollider->xMin;
                    pos.x -= offset;
                }
                else
                {
                    float offset = otherCollider->xMax - playerCollider->xMin;
                    pos.x += offset;
                }
            }
            else
            {
                if (playerCollider->yMin < otherCollider->yMin)
                {
                    float offset = playerCollider->yMax - otherCollider->yMin;
                    pos.y -= offset;
                }
                else
                {
                    float offset = otherCollider->yMax - playerCollider->yMin;
                    pos.y += offset;
                }
            }
            SetPosition(pos.x, pos.y);
        }
    }
}





void Player::cAttack() {
    AttackArea = CreateEntity<DamageZone>("0");
    AttackArea->Layout = -1;
    AttackArea->AddAABBHitbox();
    AttackArea->SetHitboxSize(100, 100);
    AttackArea->LifeTime = 0.5;
    AttackArea->IgnoreTag(GameManager::Tag::tPlayer);   
}
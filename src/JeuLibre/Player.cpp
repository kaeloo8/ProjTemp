#include "pch.h"
#include "Player.h"
#include "GameManager.h"

Player::Player()
    : mWalkAnimator(nullptr), mIdleAnimator(nullptr), mSprintAnimator(nullptr),
    mDashAnimator(nullptr), mAttackAnimator(nullptr), mState(PlayerState::sIdle)
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

    mIdleAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_idle_strip9"), 9, 0.2f);
    mWalkAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_walk_strip8"), 8, 0.1f);
    mSprintAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_run_strip8"), 8, 0.08f);
    mAttackAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_attack_strip10"), 10, 0.07f);
    mDashAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_roll_strip10"), 10, 0.07f);
    mHurtAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_hurt_strip8"), 8, 0.1f);
    // PECHE
    mCastingAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_casting_strip15"), 15, 0.1f);
    mWatteringAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_reeling_strip13"), 13, 0.1f);
    mReelingAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_reeling_strip13"), 13, 0.1f);
    mCaughtAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_caught_strip10"), 10, 0.1f);
    // MINE
    mDigAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_dig_strip13"), 13, 0.1f);
    mAxeAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_axe_strip10"), 10, 0.1f);
    mMiningAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_mining_strip10"), 10, 0.1f);

    mTag = GameManager::Tag::tPlayer;
    mSpeed = 100;
}

Player::~Player()
{
    delete mIdleAnimator;
    delete mWalkAnimator;
    delete mSprintAnimator;
    delete mAttackAnimator;
    delete mDashAnimator;
    delete mHurtAnimator;

    delete mCastingAnimator;
    delete mWatteringAnimator;
    delete mReelingAnimator;
    delete mCaughtAnimator;

    delete mDigAnimator;
    delete mAxeAnimator;
    delete mMiningAnimator;
}

void Player::SetState(PlayerState state)
{
    if (mState != state)
    {
        mState = state;
        switch (state)
        {
        case PlayerState::sIdle:
            mSpeed = 0;
            SetImage("base_idle_strip9");
            PlayerHair->SetState(PlayerPartState::sIdle);
            PlayerHand->SetState(PlayerPartState::sIdle);
            if (mIdleAnimator) mIdleAnimator->Reset();
            break;
        case PlayerState::sWalking:
            mSpeed = 150;
            SetImage("base_walk_strip8");
            PlayerHair->SetState(PlayerPartState::sWalking);
            PlayerHand->SetState(PlayerPartState::sWalking);
            if (mWalkAnimator) mWalkAnimator->Reset();
            break;
        case PlayerState::sSprinting:
            mSpeed = 250;
            SetImage("base_run_strip8");
            PlayerHair->SetState(PlayerPartState::sSprinting);
            PlayerHand->SetState(PlayerPartState::sSprinting);
            if (mSprintAnimator) mSprintAnimator->Reset();
            break;
        case PlayerState::sDashing:
            mSpeed = 400;
            SetImage("base_roll_strip10");
            PlayerHair->SetState(PlayerPartState::sDashing);
            PlayerHand->SetState(PlayerPartState::sDashing);
            if (mDashAnimator) mDashAnimator->Reset();
            break;
        case PlayerState::sGoToWork:
            mSpeed = 150;
            SetImage("base_walk_strip8");
            PlayerHair->SetState(PlayerPartState::sWalking);
            PlayerHand->SetState(PlayerPartState::sWalking);
            if (mWalkAnimator) mWalkAnimator->Reset();
            break;
        case PlayerState::sAttacking:
            mSpeed = 15;
            SetImage("base_attack_strip10");
            PlayerHair->SetState(PlayerPartState::sAttacking);
            PlayerHand->SetState(PlayerPartState::sAttacking);
            if (mAttackAnimator) mAttackAnimator->Reset();
            break;
        case PlayerState::sHurt:
            mSpeed = 0;
            SetImage("base_hurt_strip8");
            PlayerHair->SetState(PlayerPartState::sHurt);
            PlayerHand->SetState(PlayerPartState::sHurt);
            if (mHurtAnimator) mHurtAnimator->Reset();
            break;
        case PlayerState::sMining:
            mSpeed = 15;
            SetImage("base_mining_strip10");
            PlayerHair->SetState(PlayerPartState::sMining);
            PlayerHand->SetState(PlayerPartState::sMining);
            if (mMiningAnimator) mMiningAnimator->Reset();
            break;
        case PlayerState::sAxe:
            mSpeed = 15;
            SetImage("base_axe_strip10");
            PlayerHair->SetState(PlayerPartState::sAxe);
            PlayerHand->SetState(PlayerPartState::sAxe);
            if (mAxeAnimator) mAxeAnimator->Reset();
            break;
        case PlayerState::sDig:
            mSpeed = 15;
            SetImage("base_dig_strip13");
            PlayerHair->SetState(PlayerPartState::sDig);
            PlayerHand->SetState(PlayerPartState::sDig);
            if (mDigAnimator) mDigAnimator->Reset();
            break;
        default:
            break;
        }
    }
}


void Player::FaceLeft()
{
    Face_Left = true;
    GetSprite()->setScale(-std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(-std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
    PlayerHand->GetSprite()->setScale(-std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::SetActionPoint(float _x, float _y)
{
    ActionPoint.x = _x;
    ActionPoint.y = _y;
}

void Player::FaceRight()
{
    Face_Left = false;
    GetSprite()->setScale(std::abs(GetSprite()->getScale().x), GetSprite()->getScale().y);
    PlayerHair->GetSprite()->setScale(std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
    PlayerHand->GetSprite()->setScale(std::abs(PlayerHair->GetSprite()->getScale().x), PlayerHair->GetSprite()->getScale().y);
}

void Player::OnUpdate()
{
    float dt = GetDeltaTime();
    float velocityX = 0.f;
    float velocityY = 0.f;
    bool movingInput = false;

    Debug::DrawText(GetPosition().x, GetPosition().y + 30, GetCurrentStateName(), sf::Color::Yellow);
    ChangeMod();
    ChangeActionMod(); 
    StateActionMod();

    // Récupération des touches de déplacement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        velocityY -= 5.f;
        movingInput = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        velocityY += 5.f;
        movingInput = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocityX -= 5.f;
        FaceLeft();
        movingInput = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocityX += 5.f;
        FaceRight();
        movingInput = true;
    }

    if (velocityX != 0 || velocityY != 0)
    {
        lastVelocityX = velocityX;
        lastVelocityY = velocityY;
    }
    

    
    // Dash avec barre espace (le dash se joue sur toute la durée de l'animation)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!isDashing && dashCooldown <= 0 && mState != PlayerState::sHurt && mState != PlayerState::sAttacking)
        {
            // Capture la direction actuelle (si aucune direction, lastVelocity devrait être déjà définie)
            dashVelocityX = lastVelocityX * 10;
            dashVelocityY = lastVelocityY * 10;
            dashTimer = 0.7;  // Durée du dash
            dashCooldown = maxDashCooldown;
            isDashing = true;
            SetState(PlayerState::sDashing);
        }
    }
    // Sprint avec LShift (priorité si le joueur se déplace)
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        if (movingInput &&
            mState != PlayerState::sAttacking &&
            mState != PlayerState::sDig &&
            mState != PlayerState::sAxe &&
            mState != PlayerState::sMining &&
            mState != PlayerState::sDashing &&
            mState != PlayerState::sHurt)
        {
            SetState(PlayerState::sSprinting);
        }
    }
    // Sinon, si le joueur se déplace, on passe en marche
    else if (movingInput)
    {
        if (mState != PlayerState::sAttacking &&
            mState != PlayerState::sDig &&
            mState != PlayerState::sAxe &&
            mState != PlayerState::sMining &&
            mState != PlayerState::sDashing &&
            mState != PlayerState::sHurt)
        {
            SetState(PlayerState::sWalking);
        }
    }
    // Sinon, si aucune touche n'est active, on passe en idle
    else
    {
        if (mState != PlayerState::sAttacking &&
            mState != PlayerState::sDig &&
            mState != PlayerState::sAxe &&
            mState != PlayerState::sMining &&
            mState != PlayerState::sDashing &&
            mState != PlayerState::sGoToWork &&
            mState != PlayerState::sHurt)
        {
            SetState(PlayerState::sIdle);
        }
    }

    // Gestion du dash : pendant le dash, on ignore les nouvelles entrées
    if (isDashing)
    {
        dashTimer -= dt;
        GoToPosition(GetPosition().x + dashVelocityX * mSpeed,
            GetPosition().y + dashVelocityY * mSpeed,
            mSpeed);
        if (dashTimer <= 0)
        {
            isDashing = false;
            SetState(PlayerState::sIdle);
        }
    }
    else
    {
        GoToPosition(GetPosition().x + velocityX * mSpeed,
            GetPosition().y + velocityY * mSpeed,
            mSpeed);
    }

    // Mise à jour de l'animation selon l'état
    OnAnimationUpdate();

    // Mise à jour des positions des parties du joueur
    PlayerHair->SetPosition(GetPosition().x, GetPosition().y);
    PlayerHand->SetPosition(GetPosition().x, GetPosition().y);

    // Réduction du cooldown du dash
    if (dashCooldown > 0 && !isDashing)
        dashCooldown -= dt;
}

void Player::OnAnimationUpdate()
{
    float dt = GetDeltaTime();
    switch (mState)
    {
    case PlayerState::sIdle:
        if (mIdleAnimator) mIdleAnimator->Update(dt);
        break;
    case PlayerState::sWalking:
        if (mWalkAnimator) mWalkAnimator->Update(dt);
        break;
    case PlayerState::sSprinting:
        if (mSprintAnimator) mSprintAnimator->Update(dt);
        break;
    case PlayerState::sDashing:
        if (mDashAnimator)
        {
            mDashAnimator->Update(dt);
            if (mDashAnimator->IsFinished())
                SetState(PlayerState::sIdle);
        }
        break;
    case PlayerState::sGoToWork:
        if (mWalkAnimator) mWalkAnimator->Update(dt);
        break;
    case PlayerState::sAttacking:
        if (mAttackAnimator)
        {
            mAttackAnimator->Update(dt);
            if (mAttackAnimator->IsFinished())
                SetState(PlayerState::sIdle);
        }
        break;
    case PlayerState::sMining:
        if (mMiningAnimator)
        {
            mMiningAnimator->Update(dt);
            if (mMiningAnimator->IsFinished())
                SetState(PlayerState::sIdle);
        }
        break;
    case PlayerState::sAxe:
        if (mAxeAnimator)
        {
            mAxeAnimator->Update(dt);
            if (mAxeAnimator->IsFinished())
                SetState(PlayerState::sIdle);
        }
        break;
    case PlayerState::sDig:
        if (mDigAnimator)
        {
            mDigAnimator->Update(dt);
            if (mDigAnimator->IsFinished())
                SetState(PlayerState::sIdle);
        }
        break;
    case PlayerState::sHurt:
        if (mHurtAnimator) mHurtAnimator->Update(dt);
        break;
    default:
        break;
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

void Player::ChangeMod()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        mMode = PlayerMode::Attack;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        mMode = PlayerMode::Dig;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        mMode = PlayerMode::Pickaxe;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        mMode = PlayerMode::Axe;
    }
}

void Player::ChangeActionMod()
{
    if (mMode == PlayerMode::Attack)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (mState != PlayerState::sAttacking &&
                mState != PlayerState::sDashing &&
                mState != PlayerState::sHurt)
            {
                SetState(PlayerState::sAttacking);
            }
        }
    }
    if (mMode == PlayerMode::Dig)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (mState != PlayerState::sAttacking &&
                mState != PlayerState::sDashing &&
                mState != PlayerState::sHurt)
            {
                SetState(PlayerState::sGoToWork);

                
            }
        }
    }
    if (mMode == PlayerMode::Axe)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (mState != PlayerState::sAttacking &&
                mState != PlayerState::sDashing &&
                mState != PlayerState::sHurt)
            {
                SetState(PlayerState::sGoToWork);
            }
        }
    }
    if (mMode == PlayerMode::Pickaxe)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (mState != PlayerState::sAttacking &&
                mState != PlayerState::sDashing &&
                mState != PlayerState::sHurt)
            {
                SetState(PlayerState::sGoToWork);
            }
        }
    }
}

void Player::StateActionMod()
{
    if (mState == PlayerState::sGoToWork)
    {
        if (GetDistanceTo(ActionPoint.x, ActionPoint.y) > 50)
        {
            if (ActionPoint.x > GetPosition().x)
            {
                FaceRight();
                GoToDirection(ActionPoint.x - 50, ActionPoint.y, mSpeed);
            }
            else {
                FaceLeft();
                GoToDirection(ActionPoint.x + 50, ActionPoint.y, mSpeed);
            }
        
        }
        else
        {
            SetState(PlayerState::sDig);
        }
    }

    if (mState == PlayerState::sDig)
    {
        int digframe = mDigAnimator->GetFrameNumber();

        if (digframe == 6)
        {
            HasDug = true;
        }
        else
        {
            HasDug = false;
        }
    }
    if (mState == PlayerState::sAttacking)
    {
        int atkframe = mAttackAnimator->GetFrameNumber();

        if (atkframe == 6)
        {
            cAttack();
        }
    }
}

void Player::OnCollision(Entity* pCollidedWith)
{
    if (pCollidedWith->mHitbox->Solid)
    {
        AABBCollider* playerCollider = dynamic_cast<AABBCollider*>(this->mHitbox);
        AABBCollider* otherCollider = dynamic_cast<AABBCollider*>(pCollidedWith->mHitbox);
        if (!playerCollider || !otherCollider)
            return;

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
    AttackArea->setDamage(PlayerDamage);
    if (Face_Left)
    {
        AttackArea->SetPosition(GetPosition().x - 50, GetPosition().y);
    }
    else {
        AttackArea->SetPosition(GetPosition().x + 50, GetPosition().y);
    }
    AttackArea->Layout = -1;
    AttackArea->AddCircleHitbox();
    AttackArea->SetHitboxSize(60, 60);
    AttackArea->LifeTime = 0.1;
    AttackArea->IgnoreTag(GameManager::Tag::tPlayer);
}

std::string Player::GetCurrentStateName() {
    switch (mState) { // Utilisation correcte de la variable de classe
    case PlayerState::sIdle:      return "Idle";
    case PlayerState::sWalking:   return "Walking";
    case PlayerState::sSprinting: return "Sprinting";
    case PlayerState::sAttacking: return "Attacking";
    case PlayerState::sDashing:   return "Dashing";
    case PlayerState::sHurt:      return "Hurt";
    case PlayerState::sCasting:   return "Casting";
    case PlayerState::sWattering: return "Wattering";
    case PlayerState::sReeling:   return "Reeling";
    case PlayerState::sCaught:    return "Caught";
    case PlayerState::sGoToWork:  return "Going to Work";
    case PlayerState::sDig:       return "Digging";
    case PlayerState::sAxe:       return "Using Axe";
    case PlayerState::sMining:    return "Mining";
    default: return "Unknown";
    }
}

#include "pch.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneEloulou.h"

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
    PlayerHair->SetOwner(this); 

    PlayerHand = CreateEntity<PlayerPart>("0");
    PlayerHand->InitBodyPart("tools");
    PlayerHand->SetScale(3, 3);
    PlayerHand->SetOrigin(0.5, 0.5);
    PlayerHand->Layout = 11;
    PlayerHand->SetOwner(this);


    mIdleAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_idle_strip9"), 9, 0.2f);
    mWalkAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_walk_strip8"), 8, 0.1f);
    mSprintAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_run_strip8"), 8, 0.08f);
	mSwimAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_swimming_strip12"), 12, 0.1f);
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
	delete mSwimAnimator;
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
        case PlayerState::sSwim:
            mSpeed = 100;
            SetImage("base_swimming_strip12");
            PlayerHair->SetState(PlayerPartState::sSwim);
            PlayerHand->SetState(PlayerPartState::sSwim);
            if (mSwimAnimator) mSwimAnimator->Reset();
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
    PlayerHair->SetPosition(GetPosition().x, GetPosition().y);
    PlayerHand->SetPosition(GetPosition().x, GetPosition().y);

    float dt = GetDeltaTime();
    float velocityX = 0.f;
    float velocityY = 0.f;
    bool movingInput = false;

    Debug::DrawText(GetPosition().x, GetPosition().y + 30, GetCurrentStateName(), sf::Color::Yellow);
    //ChangeMod();
    if (isInWater == false)
    {
        ChangeActionMod();
        StateActionMod();
    }

    // R�cup�ration des touches de d�placement
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
    if (!GameManager::Get()->NoMap){
        int CollideMap = 0;
        if (GameManager::Get()->InDonjon) {
            CollideMap = 2;
        }
        else {
            CollideMap = 1;
        }

        if (GameManager::Get()->GetTileMap(CollideMap)) {
            auto map = GameManager::Get()->GetTileMap(CollideMap);
            int tilleline = mHitboxWidth / 2;
            int xDir = 0;
            int yDir = 0;
            if (velocityX > 0) {
                xDir = 1;
            }
            if (velocityX < 0) {
                xDir = -1;
            }
            if (velocityY > 0) {
                yDir = 1;
            }
            if (velocityY < 0) {
                yDir = -1;
            }
            int x = (GetPosition().x + (tilleline * xDir)) / 50;
            int y = (GetPosition().y + (tilleline * yDir)) / 50;
            int posX = GetPosition().x / 50;
            int posY = GetPosition().y / 50;

            Debug::DrawCircle(GetPosition().x + (tilleline * xDir), GetPosition().y + (tilleline * yDir), 3, sf::Color::Red);

            if (map->lTile[(posY * map->width) + x].type == TileType::Solid) {
                isInWater = false;
                velocityX = 0;
                lastVelocityX = 0;
            }

            if (map->lTile[(y * map->width) + posX].type == TileType::Solid) {
                isInWater = false;
                velocityY = 0;
                lastVelocityY = 0;
            }

            if (map->lTile[(posY * map->width) + posX].type == TileType::Swimmable) {
                isInWater = true;
            }
            else
            {
                isInWater = false;
            }
        }

    }

    if (velocityX != 0 || velocityY != 0)
    {
        lastVelocityX = velocityX;
        lastVelocityY = velocityY;
    }

    
    
    // Dash avec barre espace (le dash se joue sur toute la dur�e de l'animation)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isInWater == false)
    {
        if (!isDashing && dashCooldown <= 0 && mState != PlayerState::sHurt && mState != PlayerState::sAttacking)
        {
            // Capture la direction actuelle (si aucune direction, lastVelocity devrait �tre d�j� d�finie)
            dashVelocityX = lastVelocityX * 10;
            dashVelocityY = lastVelocityY * 10;
            dashTimer = 0.7;  // Dur�e du dash
            dashCooldown = maxDashCooldown;
            isDashing = true;
            SetState(PlayerState::sDashing);
        }
    }
    // Sprint avec LShift (priorit� si le joueur se d�place)
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
            if (isInWater)
            {
                SetState(PlayerState::sSwim);
                mSpeed = 150;
            }
            else {
                SetState(PlayerState::sSprinting);
            }
        }
    }
    // Sinon, si le joueur se d�place, on passe en marche
    else if (movingInput)
    {
        if (mState != PlayerState::sAttacking &&
            mState != PlayerState::sDig &&
            mState != PlayerState::sAxe &&
            mState != PlayerState::sMining &&
            mState != PlayerState::sDashing &&
            mState != PlayerState::sHurt)
        {
            if (isInWater)
            {
                SetState(PlayerState::sSwim);
				mSpeed = 100;
            }
            else {
                SetState(PlayerState::sWalking);
            }
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
            if (isInWater)
            {
                SetState(PlayerState::sSwim);
                mSpeed = 0;
            }
            else {
                SetState(PlayerState::sIdle);
            }
        }
    }
    // Gestion du dash : pendant le dash, on ignore les nouvelles entr�es
    if (isDashing)
    {
        if (isInWater)
        {
            isDashing = false;
            dashVelocityX = 0;
            dashVelocityY = 0;
            SetState(isInWater ? PlayerState::sSwim : PlayerState::sIdle);
        }
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

    // Mise � jour de l'animation selon l'�tat
    OnAnimationUpdate();

    // Mise � jour des positions des parties du joueur
    PlayerHair->SetPosition(GetPosition().x, GetPosition().y);
    PlayerHand->SetPosition(GetPosition().x, GetPosition().y);

    // R�duction du cooldown du dash
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
    case PlayerState::sSwim:
        if (mSwimAnimator) mSwimAnimator->Update(dt);
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
			if (mMode == PlayerMode::Attack)
			{
				SetState(PlayerState::sAttacking);
			}
			else if (mMode == PlayerMode::Axe)
			{
				SetState(PlayerState::sAxe);
			}
			else if (mMode == PlayerMode::Dig)
			{
				SetState(PlayerState::sDig);
			}
			else if (mMode == PlayerMode::Pickaxe)
			{
				SetState(PlayerState::sMining);
			}
		}
    }

    if (mState == PlayerState::sAxe)
    {
        int axeframe = mAxeAnimator->GetFrameNumber();

        if (axeframe < 6)

            HasAxe = false; // reset quand on revient au d�but de l'anim

        if (axeframe == 6 && !HasAxe)
        {
            SceneEloulou* scene = dynamic_cast<SceneEloulou*>(GetScene());
            if (scene)
            {
                scene->cutTree();
                HasAxe = true;
            }
        }
    }

    if (mState == PlayerState::sMining)
    {
        int mineframe = mMiningAnimator->GetFrameNumber();

        if (mineframe < 6)

            HasMine = false; // reset quand on revient au d�but de l'anim

        if (mineframe == 6 && !HasMine)
        {
            SceneEloulou* scene = dynamic_cast<SceneEloulou*>(GetScene());
            if (scene)
            {
                scene->mineStone();
                HasMine = true;
            }
        }
    }

    if (mState == PlayerState::sDig)
    {
        int digframe = mDigAnimator->GetFrameNumber();

        // Reset si on est revenu au d�but de l'anim (par s�curit�)
        if (digframe < 6)
            HasDug = false;

        if (digframe == 6 && !HasDug)
        {
            SceneEloulou* scene = dynamic_cast<SceneEloulou*>(GetScene());
            if (scene)
            {
                scene->addHole();
                HasDug = true;
            }
        }
    }


    if (mState == PlayerState::sAttacking)
    {
        int atkframe = mAttackAnimator->GetFrameNumber();

        if (atkframe == 4 && AtckActive == false)
        {
            cAttack();
        }
        if (AttackArea != nullptr && AttackArea->LifeTime <= 0)
        {
            AttackArea = nullptr; // <-- Ajout� pour �viter un pointeur dangling
        }
        if (AttackArea == nullptr)
        {
            AtckActive = false;
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
            PlayerHair->SetPosition(pos.x, pos.y);
            PlayerHand->SetPosition(pos.x, pos.y);
        }
    }
}

void Player::cAttack() {
    AtckActive = true;
    AttackArea = CreateEntity<DamageZone>("0");
    AttackArea->setDamage(PlayerDamage);
    if (Face_Left)
    {
        AttackArea->SetPosition(GetPosition().x - 40, GetPosition().y - 20);
    }
    else {
        AttackArea->SetPosition(GetPosition().x + 40, GetPosition().y - 20);
    }
    AttackArea->Layout = -1;
    AttackArea->AddCircleHitbox();
    AttackArea->SetHitboxSize(40);
    AttackArea->LifeTime = 0.1;
    AttackArea->IgnoreTag(GameManager::Tag::tPlayer);
}

std::string Player::GetCurrentStateName() {
    switch (mState) { // Utilisation correcte de la variable de classe
    case PlayerState::sIdle:      return "Idle";
    case PlayerState::sWalking:   return "Walking";
    case PlayerState::sSprinting: return "Sprinting";
    case PlayerState::sSwim:      return "Swim";
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

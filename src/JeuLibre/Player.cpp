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

    mIdleAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_idle_strip9"), 9, 0.2f);
    mWalkAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_walk_strip8"), 8, 0.1f);
    mSprintAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_run_strip8"), 8, 0.08f);
    mAttackAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_attack_strip10"), 10, 0.07f);
    mDashAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_roll_strip10"), 10, 0.1f);
    mHurtAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_hurt_strip8"), 8, 0.1f);
    //PECHE
    mCastingAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_casting_strip15"), 15, 0.1f);
    mWatteringAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_reeling_strip13"), 13, 0.1f);
    mReelingAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_reeling_strip13"), 13, 0.1f);
    mCaughtAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_caught_strip10"), 10, 0.1f);
    //MINE
    mDigAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_dig_strip13"), 13, 0.1f);
    mAxeAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_axe_strip10"), 10, 0.1f);
    mMiningAnimator = new Animator(&mSprite, *GameManager::Get()->GetAssetManager(), std::string("base_mining_strip10"), 10, 0.1f);

    mTag = GameManager::Tag::tPlayer;
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
            SetImage("base_idle_strip9");
            if (mIdleAnimator) mIdleAnimator->Reset();
            break;
        case PlayerState::sWalking:
            SetImage("base_walk_strip8");
            if (mWalkAnimator) mWalkAnimator->Reset();
            break;
        case PlayerState::sMining:
            SetImage("base_mining_strip10"); // nom de la texture pour miner
            if (mMiningAnimator) mMiningAnimator->Reset();
            break;
        case PlayerState::sAxe:
            SetImage("base_axe_strip10"); // texture pour l'animation axe
            if (mAxeAnimator) mAxeAnimator->Reset();
            break;
        case PlayerState::sDig:
            SetImage("base_dig_strip13"); // texture pour creuser
            if (mDigAnimator) mDigAnimator->Reset();
            break;
        case PlayerState::sHurt:
            SetImage("base_hurt_strip8"); // texture pour l'état hurt
            if (mHurtAnimator) mHurtAnimator->Reset();
            break;
            // Ajoute d'autres cas si nécessaire
        default:
            break;
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
    float dt = GetDeltaTime();
    float velocityX = 0.f;
    float velocityY = 0.f;
    bool movingInput = false;

    // Gestion des déplacements
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

    // Si le joueur est en train d'effectuer une action (mining, axe ou dig) et se déplace, annuler l'action pour passer à l'état walk.
    if (movingInput && (mState == PlayerState::sMining || mState == PlayerState::sAxe || mState == PlayerState::sDig))
    {
        SetState(PlayerState::sWalking);
    }

    // Gestion des actions prioritaires : Hurt est ininterruptible
    if (mState == PlayerState::sHurt)
    {
        // On laisse l'animation hurt se jouer
        if (mHurtAnimator && mHurtAnimator->IsFinished())
            SetState(PlayerState::sIdle);
    }
    else
    {
        // Lancer l'action mining avec G
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        {
            if (mState != PlayerState::sMining)
                SetState(PlayerState::sMining);
        }
        // Lancer l'action axe avec H
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            if (mState != PlayerState::sAxe)
                SetState(PlayerState::sAxe);
        }
        // Lancer l'action creuser avec J
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        {
            if (mState != PlayerState::sDig)
                SetState(PlayerState::sDig);
        }
        // Si aucune action spécifique n'est lancée, on bascule sur walk si le joueur se déplace
        else if (movingInput)
        {
            if (mState != PlayerState::sWalking)
                SetState(PlayerState::sWalking);
        }
        // Sinon, état idle
        else
        {
            if (mState != PlayerState::sIdle)
                SetState(PlayerState::sIdle);
        }
    }

    // Mise à jour de la position si pas d'action bloquante (ici on peut ajouter d'autres vérifications selon tes besoins)
    if (mState == PlayerState::sWalking || mState == PlayerState::sIdle)
    {
        // Normalisation du vecteur de déplacement
        float magnitude = std::sqrt(velocityX * velocityX + velocityY * velocityY);
        if (magnitude > 0)
        {
            velocityX /= magnitude;
            velocityY /= magnitude;
        }
        GoToPosition(GetPosition().x + velocityX * mSpeed,
            GetPosition().y + velocityY * mSpeed,
            mSpeed);
    }

    // Mise à jour de l'animation en fonction de l'état
    OnAnimationUpdate();

    // Màj de la position des parties du joueur (cheveux, main, etc.)
    PlayerHair->SetPosition(GetPosition().x, GetPosition().y);
    PlayerHand->SetPosition(GetPosition().x, GetPosition().y);
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
    case PlayerState::sMining:
        if (mMiningAnimator) {
            mMiningAnimator->Update(dt);
            if (mMiningAnimator->IsFinished())
                SetState(PlayerState::sIdle);
        }
        break;
    case PlayerState::sAxe:
        if (mAxeAnimator) {
            mAxeAnimator->Update(dt);
            if (mAxeAnimator->IsFinished())
                SetState(PlayerState::sIdle);
        }
        break;
    case PlayerState::sDig:
        if (mDigAnimator) {
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
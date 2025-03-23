#include "pch.h"
#include "Animator.h"
#include <stdexcept>

Animator::Animator(sf::Sprite* targetSprite,
    AssetManager& assetManager,
    const std::string& textureName,
    int frameCount,
    float frameDuration)
    : mSprite(targetSprite),
    mFrameCount(frameCount),
    mFrameDuration(frameDuration),
    mElapsedTime(0.f),
    mCurrentFrame(0)
{
    // R�cup�ration de la texture via l'AssetManager
    try {
        mTexture = &assetManager.GetTexture(textureName);
    }
    catch (const std::runtime_error& e) {
        throw std::runtime_error("Animator::Animator() - Erreur chargement texture : " + std::string(e.what()));
    }

    // Associer la texture au sprite
    mSprite->setTexture(*mTexture);

    // Calcul de la taille d'une frame
    mFrameWidth = mTexture->getSize().x / mFrameCount;
    mFrameHeight = mTexture->getSize().y;

    // Rectangle de la premi�re frame (frame 0)
    mFrameRect = sf::IntRect(0, 0, mFrameWidth, mFrameHeight);
    mSprite->setTextureRect(mFrameRect);
}

void Animator::Update(float deltaTime)
{
    mElapsedTime += deltaTime;

    // On change de frame quand on d�passe la dur�e d'une frame
    if (mElapsedTime >= mFrameDuration) {
        mElapsedTime = 0.f;
        mCurrentFrame = (mCurrentFrame + 1) % mFrameCount;

        // Mise � jour du rectangle de d�coupage
        mFrameRect.left = mCurrentFrame * mFrameWidth;
        mSprite->setTextureRect(mFrameRect);
    }
}

int Animator::GetFrameNumber()
{
    return mCurrentFrame;
}

void Animator::Reset()
{
    mCurrentFrame = 0;
    mElapsedTime = 0.f;
    mFrameRect.left = 0;
    mSprite->setTextureRect(mFrameRect);
}

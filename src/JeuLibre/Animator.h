#pragma once

#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Animator {
private:
    sf::Sprite* mSprite;       // Sprite � animer
    sf::Texture* mTexture;     // Pointeur vers la texture (charg�e via AssetManager)
    sf::IntRect mFrameRect;    // Rectangle de d�coupage
    int mFrameCount;           // Nombre de frames total
    int mCurrentFrame;         // Frame actuelle
    float mFrameDuration;      // Dur�e d'affichage d'une frame
    float mElapsedTime;        // Temps �coul� depuis le dernier changement de frame

    int mFrameWidth;           // Largeur d'une frame
    int mFrameHeight;          // Hauteur d'une frame

public:
    // Constructeur : on passe le sprite cible, l'AssetManager, le nom de la texture, le nb de frames, la dur�e d'une frame
    Animator(sf::Sprite* targetSprite,
        AssetManager& assetManager,
        const std::string& textureName,
        int frameCount,
        float frameDuration);

    // Met � jour l'animation (appel� chaque frame)
    void Update(float deltaTime);

    int GetFrameNumber();
    bool IsFinished() const;
    void Reset();
};

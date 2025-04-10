#pragma once
#include "AssetManager.h"
#include "GameManager.h"

#include <vector>
#include <string>

class Text {
private:
    sf::Text ActualText;
    int CharacterSize;

    std::vector<sf::Text> lTexts;

public:
    Text();

    bool HoveredText(const std::string& text);

    void Draw(sf::RenderWindow* pRenderWindow);
    void DrawText(float posX, float posY, const std::string& text, const sf::Color& color);
    void DrawText(float posX, float posY, const std::string& text, float ratioX, float ratioY, const sf::Color& color);
    void TextOnClick(const std::string& text);

    float GetLetterSpacing(int size);
    float GetUnderLinePosition(int size);

    static Text* Get();
};

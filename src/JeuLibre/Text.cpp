#include "pch.h"
#include "Text.h"

#include <SFML/Graphics/RenderWindow.hpp>

Text::Text() {
    ActualText.setFont(GameManager::Get()->GetFont());
    CharacterSize = 20;
}


Text* Text::Get()
{
    static Text mInstance;

    return &mInstance;
}


bool Text::HoveredText(const std::string& text)
{
    for (auto& t : lTexts) {
        if (t.getString() == text) {
            sf::Vector2i mouse = sf::Mouse::getPosition(*GameManager::Get()->Window);
            if (t.getGlobalBounds().contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                t.setFillColor(sf::Color::Red);  // Couleur hover
                return true;
            }
        }
    }
    return false;
}


void Text::Draw(sf::RenderWindow* pRenderWindow)
{
    //for (Line& line : mLines)
    //{
    //    pRenderWindow->draw(&line.start, 2, sf::Lines);
    //}

    //mLines.clear();

    for (sf::Text& text : lTexts)
    {
        pRenderWindow->draw(text);
    }

    lTexts.clear();
}


void Text::DrawText(float posX, float posY, const std::string& text, const sf::Color& color) {
    DrawText(posX, posY, text, 0.f, 0.f, color);
}


void Text::DrawText(float x, float y, const std::string& text, float ratioX, float ratioY, const sf::Color& color) {
    _ASSERT(ratioX >= 0.f && ratioX <= 1.f);
    _ASSERT(ratioY >= 0.f && ratioY <= 1.f);

    ActualText.setFont(GameManager::Get()->GetFont());
    ActualText.setString(text);
    ActualText.setCharacterSize(20);
    ActualText.setFillColor(color);
    ActualText.setPosition(x, y);

    const sf::FloatRect& bounds = ActualText.getLocalBounds();
    ActualText.setOrigin(bounds.width * ratioX, bounds.height * ratioY);

    lTexts.push_back(ActualText);
}

void Text::TextOnClick(const std::string& text)
{
    for (auto& t : lTexts) {
        if (t.getString() == text) {
            sf::Vector2i mouse = sf::Mouse::getPosition(*GameManager::Get()->Window);
            if (t.getGlobalBounds().contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y))) {
                if (HoveredText("Quitter"))
                {
                    GameManager::Get()->GetWindow()->close();
                }
            }
        }
    }
}


float Text::GetLetterSpacing(int size)
{
    ActualText.setCharacterSize(CharacterSize);
    return ActualText.getLetterSpacing();
}


float Text::GetUnderLinePosition(int size)
{
    return GameManager::Get()->GetFont().getUnderlinePosition(CharacterSize);
}
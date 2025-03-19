#include "pch.h"
#include "SceneGorille.h"
#include "S0Menu.h"


void SceneGorille::OnInitialize()
{
    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(true);
    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.13) / 100, (Win->getSize().x * 0.13) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->Layout = 200;

    lPlayer = CreateEntity<Player>("base_idle_strip9");
    lPlayer->SetScale(3, 3);
    lPlayer->SetOrigin(0.5f, 0.5f);
    lPlayer->SetPosition((GetWindowWidth() / 2) - lPlayer->GetSprite()->getGlobalBounds().width, (GetWindowHeight() / 2));
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(25, 20);
    lPlayer->Layout = 1;

    Button = CreateEntity<UI>("cancel");
    Button->SetScale(3,3);
    Button->SetOrigin(0.5f, 0.5f);
    Button->SetPosition((GetWindowWidth() / 2), (GetWindowHeight() / 2));
    Button->AddAABBHitbox();
    Button->Layout = 1;

    Button2 = CreateEntity<UI>("greenbar_06");
    Button2->SetScale(3, 3);
    Button2->SetOrigin(0.5f, 0.5f);
    Button2->SetPosition((GetWindowWidth() / 4), (GetWindowHeight() / 4));
    Button2->AddAABBHitbox();
    Button2->Layout = 1;
    Button2->HangToEntity(lPlayer);
    Button2->SetGap(0, GameManager::Get()->Window->getSize().y / 20);

}

void SceneGorille::OnEvent(const sf::Event& event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (!KeyEscPressed) {
            std::cout << "Retour Menu" << std::endl;
            GameManager::Get()->LaunchScene<S0Menu>();
        }
    }
    else {
        KeyEscPressed = false;
    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = Win->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        Button->HandleClick(mousePos.x, mousePos.y);
        Button2->HandleClick(mousePos.x, mousePos.y);
    }
}

void SceneGorille::OnUpdate()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*Win);
    lPointer->SetPosition(mousePos.x, mousePos.y);
}

void SceneGorille::SetName()
{
    SceneName = "Scene Gorille";
}

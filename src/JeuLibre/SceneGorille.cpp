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

    ButtonCancel = CreateEntity<UI>("cancel");
    ButtonCancel->SetScale(3,3);
    ButtonCancel->SetOrigin(0.5f, 0.5f);
    ButtonCancel->SetPosition((GetWindowWidth() / 2), (GetWindowHeight() / 2));
    ButtonCancel->AddAABBHitbox();
    ButtonCancel->Layout = 1;

    ButtonValid = CreateEntity<UI>("confirm");
    ButtonValid->SetScale(3, 3);
    ButtonValid->SetOrigin(0.5f, 0.5f);
    ButtonValid->SetPosition((GetWindowWidth() / 3), (GetWindowHeight() / 2));
    ButtonValid->AddAABBHitbox();
    ButtonValid->Layout = 1;

    LifeBar = CreateEntity<UI>("greenbar_06");
    LifeBar->SetScale(3, 3);
    LifeBar->SetOrigin(0.5f, 0.5f);
    LifeBar->SetPosition((GetWindowWidth() / 4), (GetWindowHeight() / 4));
    LifeBar->Layout = 1;
    LifeBar->HangToEntity(lPlayer);
    LifeBar->SetGap(0, GameManager::Get()->Window->getSize().y / 20);

   
    //optionsMenu->AddUIElement(ButtonCancel);
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        if (!KeyMPressed) {
            std::cout << "Options Ouvert" << std::endl;
            KeyMPressed = true;
        };
    }
    else
    {
        KeyMPressed = false;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = Win->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        
        if (ButtonCancel->HandleClick(mousePos)) {
            std::cout << "Jean" << std::endl;
        };
        if (ButtonValid->HandleClick(mousePos))
        {
            std::cout << "Julian" << std::endl;
        }
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

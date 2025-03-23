#include "pch.h"
#include "SceneGorille.h"
#include "S0Menu.h"


void SceneGorille::OnInitialize()
{
    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(true);

    cam = CreateEntity<CameraSys>("0");
    cam->Layout = -1;

    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.13) / 100, (Win->getSize().x * 0.13) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->Layout = 200;

    lPlayer = CreateEntity<Player>("base_idle_strip9");
    lPlayer->SetScale(3, 3);
    lPlayer->SetOrigin(0.5f, 0.5f);
    lPlayer->SetPosition((GetWindowWidth() / 2) - lPlayer->GetSprite()->getGlobalBounds().width, (GetWindowHeight() / 2));
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(lPlayer->mSprite.getGlobalBounds().width / 6, lPlayer->mSprite.getGlobalBounds().height / 4);
    lPlayer->Layout = 2;

    ButtonCancel = CreateEntity<UI>("cancel");
    ButtonCancel->SetScale(3,3);
    ButtonCancel->SetOrigin(0.5f, 0.5f);
    ButtonCancel->SetPosition((GetWindowWidth() / 2), (GetWindowHeight() / 2));
    ButtonCancel->AddAABBHitbox();
    ButtonCancel->Layout = 1;

    Background2 = CreateEntity<UI>("LoadingScreen");
    Background2->SetOrigin(0.5f, 0.5f);
    Background2->SetScale(Win->getSize().x, Win->getSize().y);
    Background2->Layout = 4;
    
    Background = CreateEntity<UI>("FondEcran");
    Background->SetOrigin(0.5f, 0.5f);
    Background->SetPosition((GetWindowWidth() / 2), (GetWindowHeight() / 2));
    Background->Layout = 2;
    //optionsMenu->AddUIElement(ButtonCancel);

    ButtonCancel = CreateEntity<UI>("cancel");
    ButtonCancel->AddCircleHitbox();
    ButtonCancel->SetPosition((GetWindowWidth() / 3), (GetWindowHeight() / 2));

    ButtonValid = CreateEntity<UI>("confirm");
    ButtonValid->AddCircleHitbox();;
    ButtonValid->SetPosition((GetWindowWidth() / 3), (GetWindowHeight() / 2));
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
            mOpen = !mOpen;
            KeyMPressed = true;
            if (mOpen) {
                // Afficher le menu
                std::cout << "Options Ouvert" << std::endl;
                ButtonCancel->Layout = 5;
                Background->Layout = 4;
                ButtonCancel->SetPosition(Background->GetPosition().x, Background->GetPosition().y);
            }
            else {
                // Cacher le menu
                std::cout << "Options Ferme" << std::endl;
                ButtonCancel->Layout = 1;
                Background->Layout = 1;
            }
        };
    }
    else
    {
        KeyMPressed = false;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = Win->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
        
        if (mOpen && ButtonCancel->HandleClick(mousePos)) {
            mOpen = false;
            ButtonCancel->Layout = 1;
            Background->Layout = 1;
            
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
    lPointer->SetPosition(mousePos.x + lPlayer->GetPosition().x - GameManager::Get()->Window->getSize().x / 2,mousePos.y + lPlayer->GetPosition().y - GameManager::Get()->Window->getSize().y / 2);
}

void SceneGorille::SetName()
{
    SceneName = "Scene Gorille";
}

#include "pch.h"
#include "SceneGorille.h"
#include "S0Menu.h"


//void SceneGorille::OnInitialize()
//{
//    Win = GameManager::Get()->Window;
//    Win->setMouseCursorVisible(true);
//
//    cam = CreateEntity<CameraSys>("0");
//    cam->Layout = -1;
//
//    lPointer = CreateEntity<Pointer>("Pointer");
//    lPointer->SetScale((Win->getSize().x * 0.13) / 100, (Win->getSize().x * 0.13) / 100);
//    lPointer->SetOrigin(0, 0);
//    lPointer->Layout = 200;
//
//    TEST = CreateEntity<UI>("BButton");
//    TEST->SetPointer(lPointer);
//    TEST->SetOrigin(0.5, 0.5);
//    TEST->SetScale(3, 3);
//    TEST->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2);
//    TEST->IsClickable = false;
//    TEST->Layout = 100;
//
//    ButtonCancel = CreateEntity<UI>("cancel");
//    ButtonCancel->SetPointer(lPointer);
//    ButtonCancel->SetScale(3,3);
//    ButtonCancel->SetOrigin(0.5f, 0.5f);
//    ButtonCancel->SetPosition((Win->getPosition().x / 2), (Win->getPosition().y / 2));
//    ButtonCancel->AddAABBHitbox();
//    ButtonCancel->Layout = 1;
//
//    Background2 = CreateEntity<UI>("BButton_pressed");
//    Background2->SetPointer(lPointer);
//    Background2->SetOrigin(0.5f, 0.5f);
//    Background2->SetScale(Win->getSize().x, Win->getSize().y);
//    Background2->Layout = 4;
//    
//    Background = CreateEntity<UI>("FondEcran");
//    Background->SetPointer(lPointer);
//    Background->SetOrigin(0.5f, 0.5f);
//    Background->SetPosition(500, 500);
//    Background->SetSize(400, 600);
//    Background->Layout = -1;
//    //optionsMenu->AddUIElement(ButtonCancel);
//}
//
//void SceneGorille::OnEvent(const sf::Event& event)
//{
//    sf::Vector2f mousePos = Win->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
//        if (!KeyEscPressed) {
//            std::cout << "Retour Menu" << std::endl;
//            GameManager::Get()->LaunchScene<S0Menu>();
//        }
//    }
//    else {
//        KeyEscPressed = false;
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
//        if (!KeyMPressed) {
//            mOpen = !mOpen;
//            KeyMPressed = true;
//            if (mOpen) {
//                // Afficher le menu
//                ButtonCancel->Layout = 5;
//                Background->Layout = 4;
//                Image->Layout = 5;
//                TEST->Layout = 5;
//                ButtonCancel->SetPosition(Background->GetPosition().x + 130 , Background->GetPosition().y - 250);
//                TEST->HandleHover(mousePos);
//            }
//            else {
//                // Cacher le menu
//                ButtonCancel->Layout = -1;
//                Background->Layout = -1;
//                TEST->Layout = -1;
//            }
//        };
//    }
//    else
//    {
//        KeyMPressed = false;
//    }
//
//    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
//
//        if (mOpen && ButtonCancel->HandleClick(mousePos)) {
//            mOpen = false;
//            ButtonCancel->Layout = -1;
//            Background->Layout = -1;
//            TEST->Layout = -1;
//        };
//    }
//}
//
//void SceneGorille::OnUpdate()
//{
//}
//
//void SceneGorille::SetName()
//{
//    SceneName = "Scene Gorille";
//}

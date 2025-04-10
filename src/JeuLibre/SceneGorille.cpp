#include "pch.h"
#include "SceneGorille.h"
#include "S0Menu.h"


void SceneGorille::OnInitialize()
{
    Win = GameManager::Get()->Window;
    Win->setMouseCursorVisible(false);

    cam = CreateEntity<CameraSys>("0");
    cam->Layout = -1;

    GameManager::Get()->NoMap = true;

    lText = Text::Get();

    lUI = CreateEntity<UI>("0");
    lUI->Layout = -1;

    lPointer = CreateEntity<Pointer>("Pointer");
    lPointer->SetScale((Win->getSize().x * 0.12) / 100, (Win->getSize().x * 0.12) / 100);
    lPointer->SetOrigin(0, 0);
    lPointer->AddCircleHitbox();
    lPointer->SetHitboxSize(1);
    lPointer->Layout = 20;

    lPlayer = CreateEntity<Player>("base_idle_strip9");
    lPlayer->SetScale(3, 3);
    lPlayer->SetOrigin(0.5f, 0.5f);
    lPlayer->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2);
    lPlayer->AddAABBHitbox();
    lPlayer->SetHitboxSize(25, 20);
    lPlayer->Layout = 5;

    Menu = CreateEntity<UI>("Menu");
    Menu->SetOrigin(0.5f, 0.5f);
    Menu->pos = { GetWindowWidth() / 2 , GetWindowHeight() / 2 };
    Menu->SetSize(350, 400);
    Menu->SetHide(true);
    Menu->Layout = 11;

    lUI->CreateButton(Menu->GetPosition().x - 70, Menu->GetPosition().y - 100, 30, 30, "Cancel", "Popup_0000", "Popup_0000");
    lUI->CreateButton(GetWindowWidth() / 2, GetWindowHeight() / 2 + 250, 30, 30, "Cancel", "Popup_0000", "Popup_0000");
    lUI->CreateButton(GetWindowWidth() / 2, GetWindowHeight() / 2 + 50, 150, 30, "Histoire", "Bouton_0000", "Bouton_0001");
    lUI->CreateButton(GetWindowWidth() / 2, GetWindowHeight() / 2 , 70, 30, "Controls", "Bouton_0002", "Bouton_0003");
    lUI->CreateButton(GetWindowWidth() / 2, GetWindowHeight() / 2 - 50, 150, 30, "Credits", "Bouton_0004", "Bouton_0005");
    lUI->CreateButton(GetWindowWidth() / 2, GetWindowHeight() / 2 - 250, 150, 30, "Quitter", "Bouton_0006", "Bouton_0007");
    lUI->SetHide(true);
    lUI->SetOrigin(0.5f, 0.5f);

    BackgroundScene = CreateEntity<UI>("LoadingScreen");
    BackgroundScene->SetOrigin(0.5f, 0.5f);
    BackgroundScene->pos = { GetWindowWidth() / 2 , GetWindowHeight() / 2 };
    BackgroundScene->SetSize(GetWindowWidth(), GetWindowHeight());
    BackgroundScene->Layout = 1;
}

void SceneGorille::OnEvent(const sf::Event& event)
{
    sf::Vector2f mousePos = Win->mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (!KeyEscPressed) {
            std::cout << "Retour Menu" << std::endl;

            GameManager::Get()->NoMap = false;
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
                Menu->ChangeHide();
                lUI->GetButton("Cancel")->isHide = false;
                
            }
            else {
                // Cacher le menu
                lUI->GetButton("Cancel")->isHide = true;
                Menu->ChangeHide();
            }
        };
    }
    else
    {
        KeyMPressed = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {
        if (!KeyGPressed) {
            KeyGPressed = true;

            std::cout << "Item Drop" << std::endl;

            Drop* Item1 = CreateEntity<Drop>("Tools_0000");
            Item1->SetOrigin(0.5f, 0.5f);
            Item1->SetPosition(lPlayer->GetPosition().x, lPlayer->GetPosition().y);
            Item1->SetScale(2, 2);
            Item1->Layout = 5;
            Item1->SetVelocity(5);
            Item1->IsDroped();
            lDrop.push_back(Item1);

            Drop* Item2 = CreateEntity<Drop>("Tools_0003");
            Item2->SetOrigin(0.5f, 0.5f);
            Item2->SetPosition(lPlayer->GetPosition().x, lPlayer->GetPosition().y);
            Item2->SetScale(2, 2);
            Item2->Layout = 5;
            Item2->SetVelocity(4);
            Item2->IsDroped();
            lDrop.push_back(Item2);

            std::cout << lDrop.size() << std::endl;
        };
    }
    else
    {
        KeyGPressed = false;
    }

    lText->TextOnClick("Quitter");

}

void SceneGorille::OnUpdate()
{
    std::vector<Drop*> lT;
    for (auto e : lDrop)
    {
        if (!e->mToDestroy) {
            lT.push_back(e);
        }
    }
    lDrop.clear();
    lDrop = lT;

    if (lUI->IsHovering("Cancel") && lUI->IsClicked("Cancel")) {
        if (mOpen) {
            mOpen = false;
            lUI->ChangeHide();
            Menu->ChangeHide();
            lUI->pos = { GetWindowWidth() / 2, GetWindowHeight() / 2 };
        };
    }

    if (mOpen)
    {
        lText->DrawText(Menu->GetPosition().x - 70, Menu->GetPosition().y - 100, "Histoire", sf::Color::Black);
        lText->HoveredText("Histoire");
        
        lText->DrawText(Menu->GetPosition().x - 70, Menu->GetPosition().y - 15, "Controls", sf::Color::Black);
        lText->HoveredText("Controls");

        lText->DrawText(Menu->GetPosition().x - 70, Menu->GetPosition().y + 65, "Credits", sf::Color::Black);
        lText->HoveredText("Credits");

        lText->DrawText(Menu->GetPosition().x - 70, Menu->GetPosition().y + 145, "Quitter", sf::Color::Black);
        lText->HoveredText("Quitter");
    }   
} 

void SceneGorille::SetName()
{
    SceneName = "Scene Gorille";
}

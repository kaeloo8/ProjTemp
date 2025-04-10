#include "pch.h"
#include "UI.h"
#include "GameManager.h"

UI::UI() {
    pos = { 0, 0 };
    mFont = GameManager::Get()->GetFont();
}

void UI::CreateButton(const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& name, const char* path, const char* pathHover) {
    CreateButton(pos.x, pos.y, size.x, size.y, name, path, pathHover);
}

void UI::CreateButton(float x, float y, int sx, int sy, const std::string& name, const char* path, const char* pathHover) {
    Bouton* bouton = CreateEntity<Bouton>(path);
    bouton->SetTextures(path, pathHover);
    bouton->SetSize(sx, sy);
    bouton->SetPosition(x, y);
    bouton->SetOrigin(0.5f, 0.5f);
    bouton->Layout = 12;
    bouton->AddAABBHitbox();
    bouton->SetHitboxSize(sx, sy);
    bouton->SetTag(GameManager::Tag::tHoverable);
    bouton->mLocalPos = { x, y };
    lBoutons[name] = bouton;
}

void UI::SetGap(float gapX, float gapY) {
    mGapX = gapX;
    mGapY = gapY;
}

void UI::SetPointer(Pointer* pointer) {
    lPointer = pointer;
}

bool UI::IsHovering(const std::string& name) const {
    auto it = lBoutons.find(name);
    return it != lBoutons.end() ? it->second->IsHovering() : false;
}

bool UI::IsClicked(const std::string& name) const {
    auto it = lBoutons.find(name);
    return it != lBoutons.end() ? it->second->IsClicked() : false;
}

Bouton* UI::GetButton(const std::string& name) {
    auto it = lBoutons.find(name);
    return it != lBoutons.end() ? it->second : nullptr;
}

void UI::OnUpdate() {
    sf::Vector2f viewCenter = GameManager::Get()->GetWindow()->getView().getCenter();
    sf::Vector2f viewSize = GameManager::Get()->GetWindow()->getView().getSize();

    for (auto& [name, bouton] : lBoutons) {
        bouton->SetPosition(viewCenter.x + bouton->mLocalPos.x - (viewSize.x / 2),
            viewCenter.y + bouton->mLocalPos.y - (viewSize.y / 2));
    }

    SetPosition(viewCenter.x + pos.x - (viewSize.x / 2),
        viewCenter.y + pos.y - (viewSize.y / 2));
}

void UI::OnCollision(Entity* other) {
    // À remplir selon besoin
}

void UI::SetImage(const char* path) {
    mSprite.setTexture(GameManager::Get()->GetAssetManager()->GetTexture(path));
}

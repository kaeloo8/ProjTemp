#pragma once

#include <list>
#include "AssetManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

class Entity;
class Scene;

namespace sf
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;

	sf::Font mFont;

	Scene* mpScene;

	float DeltaTime;

	int widthWin;
	int heightWin;

	std::vector<std::vector<Entity*>> TrieEntity;

private:
	GameManager();

	void VerifWin();
	void Run();

	void HandleInput();
	void Update();
	void Draw();

	void SetDeltaTime(float deltaTime) { DeltaTime = deltaTime; }

	sf::RenderWindow* GetWindow() const { return Window; }

public:

	sf::RenderWindow* Window;
	AssetManager AssetMana;

	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60);

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return DeltaTime; }
	AssetManager* GetAssetManager() { return &AssetMana; }
	Scene* GetScene() const { return mpScene; }
	sf::Font& GetFont() { return mFont; };

	sf::Texture& GetTexture(const std::string _name);

	friend Scene;

	void ClearAll();
};

#include "GameManager.inl" 
#pragma once

#include <list>
#include "AssetManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

class Entity;
class Scene;
class TileMap;
class CameraSys;

namespace sf
{
	class RenderWindow;
	class Event;
}

class GameManager 
{
	bool Loaded = false;
	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;


	int NumberScene;
	std::vector<Scene*> SceneLoaded;

	sf::Font mFont;

	Scene* mpScene;

	CameraSys* camera;

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

public:

	enum Tag {
		tPlayer,
		tEnnemie,
		tVilagois,
		tMBoss,
		tBoss,
		tSolide,

		nOfTag
	};

	bool DrawHitBox;
	bool KeyPressed;
	
	TileMap* tileMap;
	sf::RenderWindow* Window;
	AssetManager AssetMana;

	~GameManager();
	static GameManager* Get();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60);

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return DeltaTime; }
	sf::Vector2i GetPointer() { return sf::Mouse::getPosition(); }
	AssetManager* GetAssetManager() { return &AssetMana; }
	Scene* GetScene() const { return mpScene; }
	sf::Font& GetFont() { return mFont; };

	sf::Texture& GetTexture(const std::string _name);

	sf::RenderWindow* GetWindow() const { return Window; }

	void SetTileMap(TileMap*);
	TileMap* GetTilemap();

	void SetCamera(CameraSys* cam);

	friend Scene;

	void ClearAll();
};

#include "GameManager.inl" 
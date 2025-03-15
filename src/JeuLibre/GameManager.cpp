#include "pch.h"
#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "AssetManager.h"


GameManager::GameManager() {
	Window = nullptr;
	DeltaTime = 0.0f;
	mpScene = nullptr;
	 widthWin = -1;
	 heightWin = -1;
}

GameManager::~GameManager() {
	delete Window;
	delete mpScene;

	for (Entity* entity : mEntities)
	{
		delete entity;
	}
}

///////////////////////////////////////////////////////////////////////////////////
								//	Run	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::Run() {
	if (Window == nullptr)
	{
		std::cerr << "Window not created, creating default window" << std::endl;
		CreateWindow(800, 600, "Default window");
	}

	AssetMana = *(new AssetManager(Window));
	AssetMana.loadTexturesFromFolder("../../../img");


	bool fontLoaded = mFont.loadFromFile("../../../res/DePixelHalbfett.ttf");
	if (!fontLoaded) { return; }

	sf::Clock clock;
	while (Window->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());

		HandleInput();

		Update();

		Draw();
	}
}

///////////////////////////////////////////////////////////////////////////////////
								//	Update	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::Update() {
	mpScene->OnUpdate();

	//gestion Entity
	for (auto it = mEntities.begin(); it != mEntities.end(); )
	{
		Entity* entity = *it;

		entity->Update();

		if (entity->ToDestroy() == false)
		{
			++it;
			continue;
		}

		mEntitiesToDestroy.push_back(entity);
		it = mEntities.erase(it);
	}
	//colision
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
	{
		auto it2 = it1;
		++it2;
		for (; it2 != mEntities.end(); ++it2)
		{
			Entity* entity = *it1;
			Entity* otherEntity = *it2;

			if (entity->IsColliding(otherEntity))
			{
				entity->OnCollision(otherEntity);
				otherEntity->OnCollision(entity);
			}
		}
	}

	// supretion d'Entity
	for (auto it = mEntitiesToDestroy.begin(); it != mEntitiesToDestroy.end(); ++it)
	{
		delete* it;
	}

	mEntitiesToDestroy.clear();

	//ajout d'Entity
	for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
	{
		mEntities.push_back(*it);
	}

	mEntitiesToAdd.clear();
}

///////////////////////////////////////////////////////////////////////////////////
								//	HandleInput	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::HandleInput() {
	sf::Event event;
	while (Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			Window->close();
		}

		mpScene->OnEvent(event);
	}
}

///////////////////////////////////////////////////////////////////////////////////
								//	Draw	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::Draw() {
	Window->clear();
	TrieEntity.clear();

	for (Entity* entity : mEntities) {
		if (entity && entity->Layout >= 0) {
			if (entity->Layout >= TrieEntity.size()) {
				TrieEntity.resize(entity->Layout + 1);
			}
			TrieEntity[entity->Layout].push_back(entity);
		}
	}

	for (int i = 0; i < TrieEntity.size(); i++) {
		for (Entity* entity : TrieEntity[i]) {
			if (entity) {
				Window->draw(*entity->GetShape());
				Window->draw(*entity->GetSprite());
			}
		}
	}
	Window->display();
}

///////////////////////////////////////////////////////////////////////////////////
								//	Get	//
///////////////////////////////////////////////////////////////////////////////////

GameManager* GameManager::Get() {
	static GameManager mInstance;
	return &mInstance;
}

///////////////////////////////////////////////////////////////////////////////////
								//	CreateWindow	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit)
{

	Window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	Window->setFramerateLimit(fpsLimit);

	widthWin = width;
	heightWin = height;
}

///////////////////////////////////////////////////////////////////////////////////
								//	GetTexture	//
///////////////////////////////////////////////////////////////////////////////////

sf::Texture GameManager::GetTexture(std::string _name) {
	return *(AssetMana.getTexture(_name));
}
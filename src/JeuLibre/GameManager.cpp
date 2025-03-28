﻿#include "pch.h"
#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "TileMap.h"
#include "CameraSys.h"
#include "AssetManager.h"
#include "Debug.h"


GameManager::GameManager() {
	Window = nullptr;
	DeltaTime = 0.0f;
	mpScene = nullptr;
	widthWin = -1;
	heightWin = -1;
	SceneLoaded.clear();
	NumberScene = 0;
	DrawHitBox = true;
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
	if (mpScene) {
		mpScene->OnUpdate();
	}

	if (camera) {
		camera->OnUpdate();
	}
	else
	{
		sf::Vector2f pos(150.0f,-150.0f);
		sf::View DefView;
		DefView.setSize(Window->getSize().x, Window->getSize().y);
		DefView.move(pos.x,pos.y);
		Window->setView(DefView);
	}

	for (auto it = mEntities.begin(); it != mEntities.end();) {


		Entity* entity = *it;

		if (!entity->Hide)
			entity->Update();


		if (!entity->ToDestroy()) {
			++it;
			continue;
		}
		mEntitiesToDestroy.push_back(entity);
		entity = nullptr;
		it = mEntities.erase(it);
	}

	// colide 
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
	{
		auto it2 = it1;
		++it2;
		if (it2 != mEntities.end()) {
			if ((*it1)->Hide || (*it2)->Hide) {
				continue;
			}
		}
		

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

	for (Entity* entity : mEntitiesToDestroy) {
		delete entity;
	}
	mEntitiesToDestroy.clear();

	for (Entity* entity : mEntitiesToAdd) {
		mEntities.push_back(entity);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		if (!KeyPressed) {
			KeyPressed = true;
			DrawHitBox = !DrawHitBox;
			std::cout << "hitbox draw : " << DrawHitBox << std::endl;
		}
	}
	else {
		KeyPressed = false;
	}
}

///////////////////////////////////////////////////////////////////////////////////
								//	Draw	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::Draw() {
	Window->clear();

	if (camera) {
		Window->setView(camera->getView());
	}

	for (auto* tm : GameManager::Get()->GetTileMaps()) {
		for (const auto& line : tm->tiles) {
			for (const auto& tile : line) {
				Window->draw(tile.sprite);
			}
		}
	}

	TrieEntity.clear();

	for (Entity* entity : mEntities) {
		if (entity && entity->Layout >= 0 && entity->SceneName == mpScene->SceneName) {
			if (entity->Layout >= TrieEntity.size()) {
				TrieEntity.resize(entity->Layout + 1);
			}
			TrieEntity[entity->Layout].push_back(entity);
		}
	}

	for (auto& layer : TrieEntity) {
		for (Entity* entity : layer) {
			if (entity->Hide)
			{
				continue;
			}
			if (entity) {
				Window->draw(*entity->GetShape());
				Window->draw(*entity->GetSprite());
			}
		}
	}
	if (DrawHitBox) {
		Debug::Get()->Draw(Window);
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

sf::Texture& GameManager::GetTexture(std::string _name) {
	return AssetMana.GetTexture(_name);
}

///////////////////////////////////////////////////////////////////////////////////
								//	VerifWin	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::VerifWin() {
	if (Window == nullptr)
	{
		std::cerr << "Window not created, creating default window" << std::endl;
		CreateWindow(800, 600, "Default window");
	}
	if (!Loaded) {
		AssetMana = *(new AssetManager(Window));
		bool fontLoaded = mFont.loadFromFile("../../../res/DePixelHalbfett.ttf");
		Loaded = true;
	}
}

///////////////////////////////////////////////////////////////////////////////////
								//	SetTileMap	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::AddTileMap(TileMap* map) {
	tileMaps.push_back(map);
}

TileMap* GameManager::GetTileMap(size_t index) {
	if (index < tileMaps.size())
		return tileMaps[index];
	return nullptr; // Retourne nullptr si l'index est invalide
}

const std::vector<TileMap*>& GameManager::GetTileMaps() const {
	return tileMaps;
}
///////////////////////////////////////////////////////////////////////////////////
								//	SetCamera	//
///////////////////////////////////////////////////////////////////////////////////

void GameManager::SetCamera(CameraSys* cam) {
	camera = cam;
}

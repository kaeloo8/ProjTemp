#include "pch.h"
#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "TileMap.h"
#include "CameraSys.h"
#include "AssetManager.h"
#include "Debug.h"
#include "Text.h"
#include "SceneEloulou.h"
#include "SceneChevalier.h"


GameManager::GameManager() {
	Window = nullptr;
	DeltaTime = 0.0f;
	mpScene = nullptr;
	widthWin = -1;
	heightWin = -1;
	SceneLoaded.clear();
	NumberScene = 0;
	DrawHitBox = true;
	InDonjon = false;
	NoMap = false;
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
	while (Window && Window->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());

		HandleInput();

		if (!Window->isOpen()) break;

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

	for (Entity* entity : mEntities) {
		if (entity->mIsAlive) {
			entity->Layout = static_cast<int>(entity->GetPosition().y / TILESIZE);
		}
	}

	mEntities.sort([](Entity* a, Entity* b) {
		if (a->GetPosition().y == b->GetPosition().y)
			return a->GetPosition().x < b->GetPosition().x;
		return a->GetPosition().y < b->GetPosition().y;
		});

	for (auto it = mEntities.begin(); it != mEntities.end();) {


		Entity* entity = *it;

		if (!entity->isHide)
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
	// Vérification des collisions : pour chaque paire d'entités
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1) {
		for (auto it2 = std::next(it1); it2 != mEntities.end(); ++it2) {
			// Si l'une des deux entités est cachée, on passe à la suivante
			if ((*it1)->isHide || (*it2)->isHide)
				continue;

			if ((*it1)->IsColliding(*it2)) {
				(*it1)->OnCollision(*it2);
				(*it2)->OnCollision(*it1);
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
			return;
		}

		if (mpScene)
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

	// Dessin des tilemaps
	for (auto* tm : GameManager::Get()->GetTileMaps()) {
		if (!InDonjon) {
			if (tm == tileMaps[0] || tm == tileMaps[1]) {
				for (const auto& tile : tm->lTile) {
					Window->draw(tile.sprite);
				}
			}
		}
		else {
			for (const auto& tile : tm->lTile) {
				Window->draw(tile.sprite);
			}
		}
	}

	// Trier les entités par leur position
	mEntities.sort([](Entity* a, Entity* b) {
		if (a->GetPosition().y == b->GetPosition().y)
			return a->GetPosition().x < b->GetPosition().x;
		return a->GetPosition().y < b->GetPosition().y;
		});

	TrieEntity.clear();

	// Séparer les entités avec le tag tUI
	std::vector<Entity*> uiEntities;
	for (Entity* entity : mEntities) {
		if (entity && entity->Layout >= 0 && entity->SceneName == mpScene->SceneName) {
			if (entity->mTag == GameManager::Tag::tUI || entity->mTag == GameManager::Tag::tPointer) {
				uiEntities.push_back(entity);
			}
			else {
				if (entity->Layout >= TrieEntity.size()) {
					TrieEntity.resize(entity->Layout + 1);
				}
				TrieEntity[entity->Layout].push_back(entity);
			}
		}
	}

	// Dessiner les entités non-UI
	for (auto& layer : TrieEntity) {
		for (Entity* entity : layer) {
			if (entity && !entity->isHide) {
				Window->draw(*entity->GetShape());
				Window->draw(*entity->GetSprite());
			}
		}
	}

	// Dessiner les entités UI après toutes les autres
	for (Entity* entity : uiEntities) {
		if (entity && !entity->isHide) {
			Window->draw(*entity->GetShape());
			Window->draw(*entity->GetSprite());
		}
	}

	// Si on doit dessiner les hitboxes, le faire ici
	if (DrawHitBox) {
		Debug::Get()->Draw(Window);
	}

	// Dessiner le texte
	Text::Get()->Draw(Window);

	// Affichage
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

void GameManager::ClearTileMap() {
	std::vector<TileMap*> temps;
	temps.push_back(tileMaps[0]);
	temps.push_back(tileMaps[1]);
	tileMaps.clear();
	tileMaps = temps;

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

///////////////////////////////////////////////////////////////////////////////////
								//	GetPointer	//
///////////////////////////////////////////////////////////////////////////////////


sf::Vector2i GameManager::GetPointer()
{ 
	return sf::Mouse::getPosition();
}

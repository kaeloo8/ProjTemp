#include "pch.h"
#include "ShootThemUp.h"
#include "AssetManager.h"
#include "Background.h"
#include "Debug.h"
#include "Player.h"
#include "Background.h"
#include "FillBar.h"
#include "Bullet.h"
#include "SFML/Audio.hpp"
#include <iostream>
#include <format>  


void ShootThemUp::OnInitialize()
{
	ValidUsername = false;
	reseau.Init();
	PlayerKill = false;
	debugnextlvl = false;
	GameManager* GM = GameManager::Get();
	win = GM->GetWindow();

	LoadLevel();
}

void ShootThemUp::StartGame()
{

	lPlayer = CreateEntity<Player>("BM");
	lPlayer->SetScale(1,1);
	lPlayer->SetName(Username);
	lPlayer->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2);
	lPlayer->AddAABBHitbox();
	lPlayer->SetHitboxSize(25, 20);
	lPlayer->SetTag(ShootThemUp::Tag::tPlayer);
	lPlayer->Layout = 5;

	lLifeBar = CreateEntity<FillBar>("red");
	lLifeBar->SetSize(100, 10);
	lLifeBar->SetPosition(GetWindowWidth() / 2, GetWindowHeight() / 2 - 60);
	lLifeBar->Layout = 5;
	
	lBackground = CreateEntity<Background>("map");
	lBackground->SetScale(1, 1);
	lBackground->SetPosition(0+lBackground->mWidth / 2, 0+lBackground->mHeight / 2);
	lBackground->Layout = 1;

	cam.SetPos(0,0); // pour envoi envoyer pos cam + pos joueur 

	
}

void ShootThemUp::OnEvent(const sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		if (!keyHPressed) {
			keyHPressed = true;
			debugmode = !debugmode;
			if (debugmode) {
				std::cout << "Debug Mode On" << std::endl;
			}
			else {
				std::cout << "Debug Mode Off" << std::endl;
			}
		}
	}
	else {
		keyHPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		//reseau.disconnect();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
		//reseau.connect();
	}
}

void ShootThemUp::OnUpdate()
{
	UpdateWorld();
}

void ShootThemUp::LoadLevel() {
	
}

void ShootThemUp::UpdateWorld() {
	if (!gameStarted) {
		Debug::DrawTextDE(GetWindowWidth() / 2, GetWindowHeight() / 2 - 40, "PUT A USERNAME", 0.5, 0.5, sf::Color::Cyan);
		Debug::DrawTextDE(GetWindowWidth() / 2, GetWindowHeight() / 2 , Username, 0.5, 0.5, sf::Color::Yellow);
		Debug::DrawTextDE(GetWindowWidth() / 2, GetWindowHeight() / 2 + 40, "PRESS SPACE TO CONECT", 0.5, 0.5, sf::Color::Cyan);
		//std::cout << Username << std::endl;
		if (!win->hasFocus()) {
			return;
		}
		for (char c = 'A'; c <= 'Z'; ++c) {
			sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(sf::Keyboard::A + (c - 'A'));

			if (sf::Keyboard::isKeyPressed(key)) {
				if (!keyStates[key]) { // Si la touche n'a pas encore été traitée
					Username += c;    // Ajouter la lettre correspondante au pseudo
					keyStates[key] = true; // Marquer comme traitée
				}
				
			}
			else {
				keyStates[key] = false; // Réinitialiser l'état une fois la touche relâchée
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			Username = "";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (Username.size() < 3)
			{
				ValidUsername = false;
				Debug::DrawTextDE(GetWindowWidth() / 2, GetWindowHeight() / 2 + 60, "LE PSEUDO DOIT FAIRE 3 CARACTERE MINIMUM", 0.5, 0.5, sf::Color::Red);
			}
			else
			{
				ValidUsername = true;
			}
		}
		if (ValidUsername)
		{
			gameStarted = true;
			reseau.connect();
			StartGame();
		}
		return;
	}

	Debug::DrawTextDE(lPlayer->GetPosition().x, lPlayer->GetPosition().y - 50, Username, 0.2, 0.2, sf::Color::White);

	if (!win->hasFocus()) {
		return;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		if (lPlayer->Shoot()) {
			Shootplayer();
		}
	}

	float velocityX = 0;
	float velocityY = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		velocityY += 5.f;  
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		velocityY -= 5.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		velocityX += 5.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocityX -= 5.f;
	}

	cam.Add(velocityX, velocityY);

	lBackground->SetPosition(cam.GetPosX() + lBackground->mWidth / 2,cam.GetPosY() + lBackground->mHeight / 2);
	lLifeBar->SetSize(lPlayer->GetLife(), 10);

	sf::Vector2i Mpos = sf::Mouse::getPosition(*win);
	lPlayer->OrientToMouse(Mpos);
	float x = - cam.GetPosX() + lPlayer->GetPosition().x;
	float y = - cam.GetPosY() + lPlayer->GetPosition().y ;
	std::string info = std::format("{}:{}:{}:{}:{}", lPlayer->GetName(), x, y, lPlayer->GetRad(), lPlayer->GetLife());
	reseau.Envoi(info);
}


void ShootThemUp::clear() {
	
	GameManager* GM = GameManager::Get();
	std::cout << "clear" << std::endl;
	GM->ClearAll();
}

void ShootThemUp::UpdateLevelRestart() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		clear();
	}
	Debug::DrawTextDE(GetWindowWidth() / 2, GetWindowHeight() / 2, "PRESS [R] TO RESPAWN", 0.5, 0.5, sf::Color::Red);
}

void ShootThemUp::Shootplayer() {
	float posx = lPlayer->GetPosition().x - cam.GetPosX();
	float posy = lPlayer->GetPosition().y - cam.GetPosY();
	float tox = sf::Mouse::getPosition(*win).x - lPlayer->GetPosition().x;
	float toy = sf::Mouse::getPosition(*win).y - lPlayer->GetPosition().y;

	Bullet* B = CreateEntity<Bullet>("BU");
	B->Init(posx, posy, tox, toy, &reseau);
	B->SetScale(0.2, 0.2);
	B->AddAABBHitbox();
	B->SetHitboxSize(25, 20);
	B->SetTag(ShootThemUp::Tag::tProjectilePrincipalJoueur);
	B->Layout = 5;

	std::string info = std::format("B:{}:{}:{}:{}", posx, posy, tox, toy);

	reseau.Envoi(info);

}

void ShootThemUp::BulletEnnemi(float x, float y, float tx, float ty) {
	Bullet* B = CreateEntity<Bullet>("BU");
	B->Init(x, y, tx, ty,&reseau);
	B->SetScale(0.2, 0.2);
	B->AddAABBHitbox();
	B->SetHitboxSize(25, 20);
	B->SetTag(ShootThemUp::Tag::tProjectileAutreJoueur);
	B->Layout = 5;
}

void ShootThemUp::OtherPlayer(std::string name,float x,float y, float rad, float life) {

	auto it = lOther.find(name);
	if (it != lOther.end()) {
		std::cout << "p" << std::endl;
		it->second->PosWorldX = x;
		it->second->PosWorldY = y;
		it->second->OrientTo(rad);
		it->second->SetLife(life);
		it->second->Layout = 5;
	}
	else {
		lOther[name] = CreateEntity<Player>("BM");
		lOther[name]->SetTag(tEnnemie);
		lOther[name]->SetName(name);
	}
}
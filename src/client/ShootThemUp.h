#pragma once
#include "vector.h"
#include "Scene.h"
#include "AssetManager.h"
#include "Online.h"
#include "AssetManager.h"
#include "Camera.h"


class Player;
class Background;
class Bullet;
class FillBar;

class ShootThemUp : public Scene
{
private:
	const char* poisson = "fish";

public:
	Online reseau;
	Background* lBackground;
	Background* lObject;
	Player* lPlayer;
	vector<Player*> lPlayerEnnemi;
	AssetManager assetManager;
	FillBar* lLifeBar;
	vector<Bullet*> lBullet;

	std::map<sf::Keyboard::Key, bool> keyStates;
	std::string Username;
	std::map<std::string, Player*> lOther;

	const sf::WindowBase* win;
	bool BossActive;
	bool ValidUsername;
	int Level;
	const char* EnnemieImgL;
	bool gameStarted;
	bool Game;
	bool restart;
	float PlayerCoordX;
	float PlayerCoordY;
	float Speed;
	float SpeedPlayer;
	bool end;
	int Number;
	bool Generate;
	float TimeSpawn;
	float TimeShoot;
	int ScreenWidth;
	int ScreenHeight;
	int NumberProj;
	bool debugnextlvl;
	bool PlayerKill;
	float CreditScrolly;
	int TypeShoot;
	int BGSpeed;

	Camera cam;

	//debugModdde
	bool keyHPressed;
	bool KeyKPressed;
	bool debugmode;

	//MusicMode
	bool KeyBPressed;
	bool MusicMode;

	//Player Control
	bool KeyAPressed;
	float MoveSpeed;


	enum Tag
	{
		tObject,
		tEnnemie,
		tPlayer,
		tDecor,
		tProjectilePrincipalJoueur,
		tProjectileAutreJoueur,

		cout
	};
	void OnInitialize() override;
	void StartGame();
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	void LoadLevel();
	void UpdateLevelFish();
	void UpdateLevelRestart();
	void clear();
	void Shootplayer();
	void BulletEnnemi(float x,float y,float tx, float ty);
	void UpdateWorld();
	void OtherPlayer(std::string name, float x, float y, float rad, float life);
};

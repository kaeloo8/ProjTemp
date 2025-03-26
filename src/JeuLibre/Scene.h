#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
class GameManager;

class Scene
{
private:
	GameManager* mpGameManager;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }

protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnEvent(const sf::Event& event) = 0;
	virtual void OnUpdate() = 0;
	virtual void SetName() = 0;

public:
	bool IsInBuildingMode = false;

	bool KeyHPressed;
	bool KeyEscPressed;
	bool KeyMPressed;
	std::string SceneName;


	template<typename T>
	T* CreateEntity(float radius, const sf::Color& color);

	template<typename T>
	T* CreateEntity(const char* path);

	float GetDeltaTime() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;
};

#include "Scene.inl"


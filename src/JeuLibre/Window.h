#pragma once
#include <SFML/Graphics.hpp>

class Entity;

class Window
{
	sf::RenderWindow window;

public :

	Window(const std::string& title, int width, int height);


	void Display();
	bool IsOpen() const;
	void Clear();
	void PollEvents();
	sf::RenderWindow& GetRenderWindow();
};


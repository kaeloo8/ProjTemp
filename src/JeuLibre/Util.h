#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Vector2f
{
	float x,y;
public :
	Vector2f();
	Vector2f(float x,float y);
	void Set(float _x, float _y);
};

////////////////////////////////////////////////////////////////////////////

struct Depth 
{
	int DepthIndice;
public :
	Depth();
	Depth(int Value);
	int GetDepth();
	void SetDepth(int Value);
};

////////////////////////////////////////////////////////////////////////////

template<typename T>
struct Table
{
	std::vector<std::vector<T>> Tables;
public :

	Table(size_t rows, size_t cols, const T& defaultValue = T()): table(rows, std::vector<T>(cols, defaultValue)) {}

	std::vector<T>& operator[](size_t index) { return table[index]; }
	const std::vector<T>& operator[](size_t index) const { return table[index]; }
};

////////////////////////////////////////////////////////////////////////////

struct ItemInfo {
	std::string Name;
	int Quantity;
	sf::Texture& ImgItem;
public :

	ItemInfo(std::string name,int quantity, sf::Texture texture);

	int GetQuantity();
	std::string GetName();
	sf::Texture& GetTexture();

	void SetQuantity(int quantity);
	void SetName(std::string name);
	void SetTexture(sf::Texture texture);

	void AddQuantity(int Value);
	void LessQuantity(int Value);
	void DivideQuantity(int Value);
	void MultiplyQuantity(int Value);
};

////////////////////////////////////////////////////////////////////////////

struct ColiderABBA {
	float Sx, Sy;
	float x, y;
public :
	ColiderABBA();
	ColiderABBA(float sx, float sy);
	
	void SetSize(float sx, float sy);
	void SetPos(float x, float y);
};

////////////////////////////////////////////////////////////////////////////

struct ColiderCircle {
	float Rad;
	float x, y;
public :
	ColiderCircle();
	ColiderCircle(float rad);

	void SetRad(float rad);
	void SetPos(float x, float y);
};
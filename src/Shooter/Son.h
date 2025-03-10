#pragma once
#ifndef SON_
#define SON_
#include "SFML/Audio.hpp"
class Son
{
	sf::SoundBuffer Buffer;
	sf::Sound son;
	sf::Music Music;
public:
	void playson();
	void playmusic();
	void stop();
};
#endif

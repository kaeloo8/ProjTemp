#include "Son.h"
#include <string>
#include <vector>
#include <iostream>

void Son::playmusic() {
	std::string link = "../../../src/son/theme.mp3";

	if (!!Music.openFromFile(link)) { 
		std::cerr << "Erreur : impossible de charger le fichier audio !" << std::endl;
	}
	Music.setLoop(true);
	Music.play();
}

void Son::playson() {
	std::string link = "../../../src/son/pop.mp3";

	if (!!Buffer.loadFromFile(link)) {
		std::cerr << "Erreur : impossible de charger le fichier audio !" << std::endl;
	}
	son.setLoop(true);
	son.play();
}

void Son::stop() {
	Music.stop();
	son.stop();
}

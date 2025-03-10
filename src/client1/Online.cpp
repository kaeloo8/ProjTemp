#include "pch.h"
#include "Online.h"
#include <sstream>
#include "ShootThemUp.h"

Online::Online() : socketClient(INVALID_SOCKET) {}

Online::~Online() {
    closesocket(socketClient);
    WSACleanup();
}

void Online::Init() {

    // Initialisation de Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup" << std::endl;
        return;
    }

    // Création du socket UDP
    socketClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketClient == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        WSACleanup();
        return;
    }

    // Adresse locale
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = INADDR_ANY;
    localAddr.sin_port = htons(0);  // Le système attribuera un port automatiquement

    // Bind du socket local
    if (bind(socketClient, reinterpret_cast<sockaddr*>(&localAddr), sizeof(localAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors du bind : " << WSAGetLastError() << std::endl;
        closesocket(socketClient);
        WSACleanup();
        return;
    }

    std::cout << "Client initialisé." << std::endl;
}

void Online::connect() {
    // Spécifie l'adresse du serveur
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(10001);  // Le port du serveur (doit correspondre au serveur)
    if (inet_pton(AF_INET, "127.0.0.1", &remoteAddr.sin_addr) <= 0) {
        std::cerr << "Erreur lors de la conversion de l'adresse IP." << std::endl;
        return;
    }

    // Envoi d'un message pour signaler la connexion au serveur
    std::string message = "hello";  // Message de connexion
    int bytesSent = sendto(socketClient, message.c_str(), message.size(), 0, reinterpret_cast<sockaddr*>(&remoteAddr), sizeof(remoteAddr));

    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Erreur lors de l'envoi du message de connexion : " << WSAGetLastError() << std::endl;
    }
    else {
        std::cout << "Message de connexion envoyé au serveur." << std::endl;
    }

    // Créer les threads pour envoyer et recevoir des messages
    thread1 = CreateThread(NULL, 0, Recus, this, 0, NULL);
}

void Online::disconnect() {
    // Envoie un message de déconnexion au serveur
    std::string message = "quit";
    sendto(socketClient, message.c_str(), message.size(), 0, reinterpret_cast<sockaddr*>(&remoteAddr), sizeof(remoteAddr));

    WaitForSingleObject(thread1, INFINITE);

    std::cout << "Client déconnecté." << std::endl;
}

DWORD WINAPI Online::Recus(LPVOID lpParam) {
    Online* _Online = static_cast<Online*>(lpParam);

    while (true) {
        int bytesReceived = recvfrom(_Online->socketClient, _Online->buffer, sizeof(_Online->buffer) - 1, 0, nullptr, nullptr);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Erreur lors de la réception du message : " << WSAGetLastError() << std::endl;
            continue;
        }

        _Online->buffer[bytesReceived] = '\0'; // Terminer correctement la chaîne de caractères
        std::cout << "Message reçu du serveur : " << _Online->buffer << std::endl;

        std::string typeOrName;
        float x1 = 0.0f, x2 = 0.0f, x3 = 0.0f, x4 = 0.0f;

        std::stringstream ss(_Online->buffer);
        if (!std::getline(ss, typeOrName, ':')) {
            std::cerr << "Erreur : type ou nom non trouvé dans le message." << std::endl;
            continue;
        }

        std::string x1Str, x2Str, x3Str, x4Str;

        // Récupérer les valeurs x1, x2, x3, x4
        if (std::getline(ss, x1Str, ':') && std::getline(ss, x2Str, ':') &&
            std::getline(ss, x3Str, ':') && std::getline(ss, x4Str)) {
            try {
                x1 = std::stof(x1Str);
                x2 = std::stof(x2Str);
                x3 = std::stof(x3Str);
                x4 = std::stof(x4Str);
            }
            catch (const std::exception& e) {
                std::cerr << "Erreur de conversion : " << e.what() << std::endl;
                continue;
            }

            // Vérifier si le message est une balle (B) ou un joueur (name)
            if (typeOrName == "B") {
                _Online->newB(x1, x2, x3, x4);
                std::cout << "Balle ajoutée - x1: " << x1 << ", x2: " << x2
                    << ", x3: " << x3 << ", x4: " << x4 << std::endl;
            }
            else {
                _Online->newP(typeOrName, x1, x2, x3, x4);
            }
        }
        else {
            std::cerr << "Erreur : format incorrect pour les données." << std::endl;
            continue;
        }
    }

    return 0;
}




void Online::Envoi(std::string info) {
    int bytesSent = sendto(socketClient, info.c_str(), info.size(), 0, reinterpret_cast<sockaddr*>(&remoteAddr), sizeof(remoteAddr));
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Erreur lors de l'envoi : " << WSAGetLastError() << std::endl;
    }
}

void Online::newB(float x,float y,float tx,float ty) {
    this->GetScene<ShootThemUp>()->BulletEnnemi(x, y, tx, ty);
}
void Online::newP(std::string name, float x, float y, float rad, float life) {
    this->GetScene<ShootThemUp>()->OtherPlayer(name,x,y,rad,life);
}

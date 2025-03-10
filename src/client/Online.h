#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include "Entity.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

class Online : public Entity
{
private:
    SOCKET socketClient;  // Socket pour le client
    sockaddr_in remoteAddr;  // Adresse du serveur (à qui le client envoie les messages)
    sockaddr_in localAddr;  // Adresse locale du client
    WSADATA wsaData;  // Données de Winsock
    char buffer[1500];  // Buffer pour recevoir les messages
    HANDLE thread1;  // Thread pour recevoir les messages
    HANDLE thread2;  // Thread pour envoyer les messages

public:
    // Constructeur et destructeur
    Online();
    ~Online();

    // Méthodes publiques
    void Init();  // Initialise le client
    void connect();  // Connecte le client au serveur
    void disconnect();  // Déconnecte le client

    // Fonction pour envoyer et recevoir des messages
    static DWORD WINAPI Recus(LPVOID lpParam);
    void Envoi(std::string info);
    void newB(float x, float y, float tx, float ty);
    void newP(std::string name, float x, float y, float tx, float ty);
};

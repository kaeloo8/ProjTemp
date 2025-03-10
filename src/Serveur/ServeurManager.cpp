#include "pch.h"
#include "ServeurManager.h"
#include <iostream>
#include <algorithm>
#include <thread>

// Fonction de réception des messages
void reception(SOCKET clientSocket, ServeurManager* manager) {
    char buffer[1024];
    int receivedBytes;

    while (true) {
        receivedBytes = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (receivedBytes > 0) {
            buffer[receivedBytes] = '\0'; // Assurer une terminaison correcte
            std::cout << "Message reçu : " << buffer << std::endl;
            manager->BroadcastMessage(buffer, clientSocket); // Envoyer à tous les autres clients
        }
        else {
            std::cout << "Client déconnecté ou erreur de réception." << std::endl;
            break;
        }
    }

    // Fermer le socket et supprimer le client de la liste
    closesocket(clientSocket);
}

// Fonction pour envoyer un message à tous les autres clients
void ServeurManager::BroadcastMessage(const char* message, SOCKET sender) {
    std::lock_guard<std::mutex> lock(listMutex); // Protéger l'accès à ClientsList
    for (SOCKET client : ClientsList) {
        if (client != sender) {
            send(client, message, static_cast<int>(strlen(message)), 0);
        }
    }
}

// Initialisation du serveur
void ServeurManager::Init() {
    std::cout << "Serveur Initie" << std::endl;

    if (WSAStartup(MAKEWORD(2, 2), &Data) != 0) {
        std::cout << "Erreur initialisation WinSock : " << WSAGetLastError() << std::endl;
        return;
    }

    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server == INVALID_SOCKET) {
        std::cout << "Erreur initialisation socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    ip = "127.0.0.1"; // Adresse IP du serveur
    const unsigned short port = 8080;

    addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) != 0) {
        std::cout << "Erreur bind : " << WSAGetLastError() << std::endl;
        closesocket(server);
        WSACleanup();
        return;
    }

    if (listen(server, SOMAXCONN) != 0) {
        std::cout << "Erreur listen : " << WSAGetLastError() << std::endl;
        closesocket(server);
        WSACleanup();
        return;
    }

    std::cout << "Serveur en attente de connexions sur le port " << port << "..." << std::endl;

    // Boucle principale pour accepter les connexions
    while (true) {
        sockaddr_in from = {};
        int addrlen = sizeof(from);
        SOCKET newClient = accept(server, (sockaddr*)&from, &addrlen);
        if (newClient == INVALID_SOCKET) {
            std::cout << "Erreur accept : " << WSAGetLastError() << std::endl;
            continue;
        }

        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(from.sin_addr), clientIp, INET_ADDRSTRLEN);
        std::cout << "Connexion de " << clientIp << ":" << ntohs(from.sin_port) << std::endl;

        {
            std::lock_guard<std::mutex> lock(listMutex);
            ClientsList.push_back(newClient);
        }

        // Démarrer un thread pour gérer le client
        std::thread clientThread(reception, newClient, this);
        clientThread.detach();
    }

    // Nettoyage
    closesocket(server);
    WSACleanup();
}

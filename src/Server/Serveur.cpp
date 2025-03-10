#include "pch.h"
#include "Serveur.h"

Server::Server() : socketServer(INVALID_SOCKET), clientAddrSize(sizeof(clientAddr)) {}

void Server::Init() {
    // Initialisation de Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup" << std::endl;
        return;
    }

    // Création du socket UDP
    socketServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socketServer == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        WSACleanup();
        return;
    }

    // Adresse du serveur
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(10001);  // Port d'écoute

    // Bind du socket
    if (bind(socketServer, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors du bind : " << WSAGetLastError() << std::endl;
        closesocket(socketServer);
        WSACleanup();
        return;
    }

    // Créer un thread pour recevoir les messages
    receiveThread = CreateThread(NULL, 0, ReceiveMessages, this, 0, NULL);
    if (receiveThread == NULL) {
        std::cerr << "Erreur lors de la création du thread" << std::endl;
        closesocket(socketServer);
        WSACleanup();
        return;
    }

    std::cout << "Serveur démarré, en attente des clients..." << std::endl;
}

void Server::Start() {
    // Attente de la fin du thread de réception
    WaitForSingleObject(receiveThread, INFINITE);

    // Fermeture de la socket et nettoyage de Winsock
    closesocket(socketServer);
    WSACleanup();
}

// Thread pour recevoir les messages des clients
DWORD WINAPI Server::ReceiveMessages(LPVOID lpParam) {
    Server* server = static_cast<Server*>(lpParam);
    char buffer[1500];

    while (true) {
        int bytesReceived = recvfrom(server->socketServer, buffer, sizeof(buffer) - 1, 0, reinterpret_cast<sockaddr*>(&server->clientAddr), &server->clientAddrSize);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Erreur lors de la réception : " << WSAGetLastError() << std::endl;
            continue;
        }

        buffer[bytesReceived] = '\0';  // Terminaison de la chaîne
        std::cout << "Message reçu de " << server->GetClientInfo(server->clientAddr) << ": " << buffer << std::endl;

        // Ajouter le client si ce n'est pas déjà dans la liste
        server->AddClient(server->clientAddr);

        // Broadcast du message à tous les clients
        server->BroadcastMessage(buffer, server->clientAddr);
    }

    return 0;
}

void Server::BroadcastMessage(const std::string& message, sockaddr_in emeteur) {
    std::lock_guard<std::mutex> lock(mtx);  // Verrouillage pour l'accès sécurisé à la liste des clients

    for (const auto& client : clients) {
        // Comparer les adresses et les ports, et ne pas envoyer à l'expéditeur
        if (client.sin_addr.s_addr != emeteur.sin_addr.s_addr || client.sin_port != emeteur.sin_port) {
            int bytesSent = sendto(socketServer, message.c_str(), message.size(), 0, reinterpret_cast<const sockaddr*>(&client), sizeof(client));
            if (bytesSent == SOCKET_ERROR) {
                std::cerr << "Erreur lors de l'envoi à " << GetClientInfo(client) << ": " << WSAGetLastError() << std::endl;
            }
        }
    }
}

void Server::AddClient(const sockaddr_in& client) {
    std::lock_guard<std::mutex> lock(mtx);  // Verrouillage pour l'accès sécurisé à la liste des clients

    // Vérifier si le client est déjà dans la liste
    for (const auto& existingClient : clients) {
        if (existingClient.sin_addr.s_addr == client.sin_addr.s_addr &&
            existingClient.sin_port == client.sin_port) {
            return;  // Le client est déjà dans la liste
        }
    }
    // Ajouter le client à la liste
    clients.push_back(client);
    std::cout << "Nouveau client connecté: " << GetClientInfo(client) << std::endl;
}

void Server::RemoveClient(const sockaddr_in& client) {
    std::lock_guard<std::mutex> lock(mtx);  // Verrouillage pour l'accès sécurisé à la liste des clients

    auto it = std::remove_if(clients.begin(), clients.end(), [&client](const sockaddr_in& c) {
        return c.sin_addr.s_addr == client.sin_addr.s_addr && c.sin_port == client.sin_port;
        });

    if (it != clients.end()) {
        clients.erase(it, clients.end());
        std::cout << "Client déconnecté: " << GetClientInfo(client) << std::endl;
    }
}

std::string Server::GetClientInfo(const sockaddr_in& clientAddr) {
    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, ip, INET_ADDRSTRLEN);
    std::ostringstream oss;
    oss << ip << ":" << ntohs(clientAddr.sin_port);
    return oss.str();
}

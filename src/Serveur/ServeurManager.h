#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <vector>
#include <mutex>

#pragma comment(lib, "Ws2_32.lib")

class ServeurManager
{
private:
    std::vector<SOCKET> ClientsList; // Liste dynamique des clients
    std::mutex listMutex;            // Mutex pour synchroniser l'accès à ClientsList
    WSAData Data;
    SOCKET server;
    PCSTR ip;
    sockaddr_in addr;

public:
    void Init();
    void BroadcastMessage(const char* message, SOCKET sender);
};

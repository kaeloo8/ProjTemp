#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <algorithm>

#pragma comment(lib, "ws2_32.lib")

class Server {
public:
    Server();
    void Init();
    void Start();
    void AddClient(const sockaddr_in& client);
    void RemoveClient(const sockaddr_in& client);
    void BroadcastMessage(const std::string& message, sockaddr_in emeteur);
    std::string GetClientInfo(const sockaddr_in& clientAddr);

private:
    static DWORD WINAPI ReceiveMessages(LPVOID lpParam);

    SOCKET socketServer;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    int clientAddrSize;
    std::vector<sockaddr_in> clients;
    std::mutex mtx;
    HANDLE receiveThread;
    WSADATA wsaData;
};
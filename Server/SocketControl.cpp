#include "D:\\LTMc++\\WinsockTest2\\Bai1\\SocketControl.h"
bool SocketControl::initWinsock() {
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("WSAStartup failed: \n");
        return false;
    }
    return true;
}
bool SocketControl::createSocket() {
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof (hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    // Resolve the local address and port to be used by the server
    if (getaddrinfo(NULL, port, &hints, &addressInfo) != 0) {
        printf("getaddrinfo failed: \n");
        std::cout << WSAGetLastError();
        cleanup();
        return false;
    }
    primarySocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
    if (primarySocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(addressInfo);
        cleanup();
        return false;
    }
    return true;
}
void SocketControl::cleanup() {
    closesocket(primarySocket);
    freeaddrinfo(addressInfo);
    WSACleanup();
}
SocketControl::~SocketControl() {
    cleanup();
}
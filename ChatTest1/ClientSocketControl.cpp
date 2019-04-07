#include "ClientSocketControl.h"

bool ClientSocketControl::start() {
	if (!initWinsock() || !createSocket() || !connectSocket()) {
		cleanup();
		return false;
	}
	return true;
}
bool ClientSocketControl::connectSocket() {
	std::string serverIP = "";
	std::getline(std::cin, serverIP);
	if (serverIP.length() == 0) {
		serverIP = "13.67.73.174";
		//serverIP = "127.0.0.1";
	}
	addrinfo *serverAddressInfo = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	// Resolve the server address and port
	if (getaddrinfo(serverIP.c_str(), port, &hints, &serverAddressInfo) != 0) {
		printf("getaddrinfo failed: %d\n", WSAGetLastError());
		return false;
	}
	if (connect(primarySocket, serverAddressInfo->ai_addr, (int)serverAddressInfo->ai_addrlen) == SOCKET_ERROR) {
		closesocket(primarySocket);
		primarySocket = INVALID_SOCKET;
		std::cout << "failed to connect to a server. " << WSAGetLastError() << "\n";
		return false;
	}
	freeaddrinfo(serverAddressInfo);
	if (primarySocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		return false;
	}
	return true;
}
std::string ClientSocketControl::sendMessage(std::string name, std::string message) {
	Message sendBuffer;
	sendBuffer.setSender(name);
	sendBuffer.setMessage(message);
	int sendResult = send(primarySocket, (char*)&sendBuffer, sizeof(Message), 0);
	if (sendResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(primarySocket);
		WSACleanup();
		return "lag vkl\n";
	}
	printf("Bytes Sent: %ld\n", sendResult);
	return "Message sent\n";
}
Message ClientSocketControl::receiveMessage() {
	Message recvbuf;
	Message error;
	int receiveResult = recv(primarySocket, (char*)&recvbuf, sizeof(Message), 0);
	if (receiveResult > 0) {
		printf("Bytes received: %d.\n", receiveResult);
		return recvbuf;
	}
	else if (receiveResult == 0) {
		printf("Connection closed\n");
		return error;
	}
	else {
		printf("recv failed with error: %d\n", WSAGetLastError());
		return error;
	}
}
bool ClientSocketControl::closeSocket() {
	if (shutdown(primarySocket, SD_SEND) == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(primarySocket);
		WSACleanup();
		return false;
	}
	return true;
}
ClientSocketControl::~ClientSocketControl() {
	closeSocket();
}
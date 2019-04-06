#include "pch.h"
#ifndef SOCKET_CONTROL_H
#define SOCKET_CONTROL_H
class SocketControl {
protected:
	WSADATA wsaData;
	SOCKET primarySocket = INVALID_SOCKET;
	addrinfo *addressInfo;
	char port[6] = "27015";
public:
	virtual bool start() = 0;
	bool initWinsock();
	bool createSocket();
	void cleanup();
	~SocketControl();
};
#endif


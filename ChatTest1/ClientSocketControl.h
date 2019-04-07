#pragma once
#include "SocketControl.h"
#include "Message.h"
class ClientSocketControl :
	public SocketControl
{
public:
	bool start();
	bool connectSocket();
	std::string sendMessage(std::string name, std::string message);
	Message receiveMessage();
	bool closeSocket();
	~ClientSocketControl();
};


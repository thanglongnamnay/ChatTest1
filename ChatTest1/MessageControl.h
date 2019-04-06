#pragma once
#include "ClientSocketControl.h"
class MessageControl {
public:
	ClientSocketControl* socketControl;
	MessageControl();
	~MessageControl();
	std::string connectToServer();
	std::string sendMessage(std::string name, std::string message);
	std::string receiveMessage();
	std::string closeSocket();
};

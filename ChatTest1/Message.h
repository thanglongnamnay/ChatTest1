#ifndef MESSAGE_H
#define MESSAGE_H
#include "pch.h"
class Message
{
public:
	char sender[128] = "";
	char message[256] = "";
	void setSender(std::string sender);
	void setMessage(std::string message);
	bool isError();
	friend std::ostream &operator<<(std::ostream &out, const Message &message);
};
#endif


#ifndef MESSAGE_H
#define MESSAGE_H
#include "pch.h"
class Message
{
private:
	char sender[128] = "";
	char message[256] = "";
public:
	std::string getSender();
	std::string getMessage();
	void setSender(std::string sender);
	void setMessage(std::string message);
	bool isError();
	friend std::ostream &operator<<(std::ostream &out, const Message &message);
};
#endif


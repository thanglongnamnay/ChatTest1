#ifndef MESSAGE_H
#define MESSAGE_H
#include "pch.h"
class Message
{
public:
	char sender[128] = "";
	char message[256] = "";
	bool isError();
	friend std::ostream &operator<<(std::ostream &out, const Message &message);
};
#endif


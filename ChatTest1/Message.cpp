#include "Message.h"

std::ostream &operator<<(std::ostream &out, const Message &message) {
	out << message.sender << ": " << message.message;
	return out;
}
bool Message::isError() {
	return sender == "";
}

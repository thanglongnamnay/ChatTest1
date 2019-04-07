#include "Message.h"

std::ostream &operator<<(std::ostream &out, const Message &message) {
	out << message.sender << ": " << message.message;
	return out;
}
void Message::setSender(std::string sender) {
	strcpy(this->sender, sender.c_str());
}
void Message::setMessage(std::string message) {
	strcpy(this->message, message.c_str());
}
bool Message::isError() {
	return sender == "";
}

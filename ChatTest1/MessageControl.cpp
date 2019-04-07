#include "MessageControl.h"
MessageControl::MessageControl() {
	socketControl = new ClientSocketControl();
}
MessageControl::~MessageControl() {
	delete socketControl;
}
std::string MessageControl::connectToServer() {
	if (socketControl->start()) {
		return "Connected.\n";
	}
	return "Not connected.\n";
}
std::string MessageControl::sendMessage(std::string name, std::string message) {
	return socketControl->sendMessage(name, message);
}
std::string MessageControl::receiveMessage() {
	Message rm = socketControl->receiveMessage();
	if (rm.isError()) return "";
	return "\n" + rm.getSender() + ": " + rm.getMessage();
}
std::string MessageControl::closeSocket() {
	if (socketControl->closeSocket()) {
		return "Done.\n";
	}
	return "Not done.\n";
}

#include "D:\\LTMc++\\WinsockTest2\\Bai1\\SocketControl.h"
#include "MessageControl.h"
#include "Message.h"
#include <vector>
#include <set>
#include <thread>

class ServerSocketControl : public SocketControl {
protected:
	MessageControl messageControl;
	std::vector<Message> messageList;
	std::vector<SOCKET> clientSocketList;
	std::vector<std::thread*> communicateThreadList;
	std::set<std::string> nameList;
public:
	bool start() {
		if (!initWinsock() || !createSocket() || !bindSocket() || !listenForConnection() || !acceptSocket()) {
			cleanup();
			return false;
		}
		return true;
	}
	bool bindSocket() {
	    if (bind( primarySocket, addressInfo->ai_addr, (int)addressInfo->ai_addrlen) == SOCKET_ERROR) {
	        printf("bind failed with error: %d\n", WSAGetLastError());
			cleanup();
	        return false;
	    }
		return true;
	}
	bool listenForConnection() {
		if (listen(primarySocket, SOMAXCONN) == SOCKET_ERROR) {
		    printf( "Listen failed with error: %ld\n", WSAGetLastError() );
			cleanup();
		    return false;
		}
		std::cout << "Listening...\n";
		return true;
	}
	void sendBack(Message respondMessage) {
		for (auto clientSocket : clientSocketList) {
			std::cout << "Send back to socket" << clientSocket << "\n";
			int sendResult = send(clientSocket, (char*)&respondMessage, sizeof(Message), 0);
	        if (sendResult == SOCKET_ERROR) {
	            printf("send failed: %d\n", WSAGetLastError());
	        }
	        printf("Bytes sent: %d.\n", sendResult);
		}
	}
	int findIndex(SOCKET s) {
		for (int i = 0; i < clientSocketList.size(); ++i) {
			if (clientSocketList[i] == s) {
				return i;
			}
		}
		return -1;
	}
	bool communicate(SOCKET clientSocket) {
		std::string name;
		std::cout << "Just accept a socket.\n";
		if (clientSocket == INVALID_SOCKET) {
		    printf("accept failed, close client socket: %d\n", WSAGetLastError());
		    remove(findIndex(clientSocket));
		    return false;
		}
		// Receive until the peer shuts down the connection
		int receiveResult;
		do {
			Message recvbuf;
		    receiveResult = recv(clientSocket, (char*)&recvbuf, sizeof(Message), 0);
		    if (receiveResult > 0) {
		        printf("Bytes received: %d\n", receiveResult);
		        if (std::string(recvbuf.message) == "/VERIFY") {
		        	std::cout << "Verifying...\n";
		        	name = std::string(recvbuf.sender);
		        	if (nameList.find(name) != nameList.end()) {
		        		Message error;
		        		std::cout << "Duplicated, sendding back\n";
		        		int sr = send(clientSocket, (char*)&error, sizeof(Message), 0);
		        		if (sr == SOCKET_ERROR) {
							printf("send failed: %d\n", WSAGetLastError());
						}
		        	} else {
		        		std::cout << "Not duplicated\n";
		        		Message success;
		        		strcpy(success.sender, "Server");
		        		strcpy(success.message, "Success");
		        		int sr = send(clientSocket, (char*)&success, sizeof(Message), 0);
		        		if (sr == SOCKET_ERROR) {
							printf("send failed: %d\n", WSAGetLastError());
						}
		        		nameList.insert(name);
						for (auto message : messageList) {
							if (send(clientSocket, (char*)&message, sizeof(Message), 0) == SOCKET_ERROR) {
								printf("send failed: %d\n", WSAGetLastError());
							}
						}
		        	}
		        } else {
			        messageList.push_back(recvbuf);
					std::cout << "Received message: " << recvbuf.sender << ": " << recvbuf.message << std::endl;
			        sendBack(recvbuf);
			    }
		    } else if (receiveResult == 0) {
		        printf("Connection closed.\n");
			    nameList.erase(name);
	    		remove(findIndex(clientSocket));
			    return false;
		    } else {
		        printf("recv failed, close client socket: %d\n", WSAGetLastError());
			    nameList.erase(name);
	    		remove(findIndex(clientSocket));
			    return false;
		    }
		} while (receiveResult > 0);
		// shutdown the connection since we're done
	    if (shutdown(clientSocket, SD_SEND) == SOCKET_ERROR) {
	        printf("shutdown failed with error, close client socket: %d\n", WSAGetLastError());
	    }
	    nameList.erase(name);
	    remove(findIndex(clientSocket));
	    return true;
	}
	bool acceptSocket() {
		SOCKET clientSocket = INVALID_SOCKET;
		// Accept a client socket
		while (1) {
			clientSocket = INVALID_SOCKET;
			clientSocket = accept(primarySocket, NULL, NULL);
			clientSocketList.push_back(clientSocket);
			communicateThreadList.push_back(new std::thread(&ServerSocketControl::communicate, this, clientSocket));
		}
	    // cleanup
	 //    printf("close client socket\n");
	 //    closesocket(clientSocket);
		// return true;
	}
	void remove(int index) {
		communicateThreadList.erase(communicateThreadList.begin() + index);
		clientSocketList.erase(clientSocketList.begin() + index);
		std::cout << "ThreadList: " << communicateThreadList.size() << ".\nSocketList: " << clientSocketList.size() << "\n";
	}
};
class ServerForm {
public:
	void start() {
		ServerSocketControl socketControl;
		if (socketControl.start())
			std::cout << "Done\n";
		else 
			std::cout << "Error! Try again.\n";
	}
};

int main() {
	ServerForm sf;
	sf.start();
	system("pause");
	return 0;
}
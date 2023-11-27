#include "Server.h"

Server::Server(const char* host, const char* port) : pollGroup(nullptr)
{
	if (!listener.setUp(host, port))
		throw std::runtime_error("Server set up failed");

	if (!listener.startListen())
		throw std::runtime_error("Server set up failed");

	pollGroup = std::make_unique<PollGroup>(*listener.getFd());

	std::cout << "Server set up successful. Listening for new connections...\n";
}

Server::~Server() 
{}

// will only return false if closesocket() fails. 
// Error conditions from pollGroup.remove() and
// users.remove() only suggest that the socket
// was connected, but never stored in those structures
bool Server::disconnectUser(SOCKET fd)
{
	if (closesocket(fd) == SOCKET_ERROR)
	{
		reportWSAErr("SC_getAddrInfo()", WSAGetLastError());
		return false;
	}

	std::cout << "Socket " << fd << " closed\n";

	if (!pollGroup->remove(fd))
		std::cout << "Error removing socket " << fd << "from Poll Group\n";

	if (!users.remove(fd))
		std::cout << "Error removing socket " << fd << "from User Set\n";

	return true;
}


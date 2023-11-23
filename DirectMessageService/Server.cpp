#include "Server.h"

Server::Server(const char* host, const char* port) : pollGroup(nullptr)
{
	std::string failed = "Server set up failed";

	if (!listener.setUp(host, port))
		throw std::runtime_error(failed);

	if (!listener.startListen())
		throw std::runtime_error(failed);

	pollGroup = std::make_unique<PollGroup>(listener.getAddrData()->fd);
}

Server::~Server()
{}

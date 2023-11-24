#include "Server.h"

Server::Server(const char* host, const char* port) : pollGroup(nullptr)
{
	std::string failed = "Server set up failed";

	if (!listener.setUp(host, port))
		throw std::runtime_error(failed);

	if (!listener.startListen())
		throw std::runtime_error(failed);

	pollGroup = std::make_unique<PollGroup>(listener.getAddrData()->fd);

	std::cout << "Server set up successful. Listening for new connections...\n";
}

Server::~Server()
{}



//SOCKET UserSet::getFdByName(const std::string& nm)
//{
//	auto found = mSet.find(nm);
//}


bool UserSet::User::operator==(const User& rhs)
{
	return this->fd == rhs.fd && this->username == rhs.username;
}

bool UserSet::User::operator==(SOCKET fd)
{
	return this->fd == fd;
}

bool UserSet::User::operator==(const std::string& nm)
{
	return this->username == nm;
}
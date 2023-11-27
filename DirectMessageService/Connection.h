#pragma once
#include "Utils.h"

using namespace Utils;

class Connection
{
public:
	Connection();
	virtual ~Connection();

	const SOCKET* getFd();

	bool setUp(const char* host, const char* port);
	bool isSetUp();

protected:
	// either bindFirstAvail or connectFirstAvail
	SOCKET(*connectionTask) (addrinfo*, addrinfo*&) = 0;
	SOCKET* fd;
};

namespace ConnectionTools
{
	int getAddrInfo(const char* host, const char* port, addrinfo*& ai);
	SOCKET bindFirstAvail(addrinfo* ai, addrinfo*& p);
	SOCKET connectFirstAvail(addrinfo* ai, addrinfo*& p);
	//addrinfo makeHints();
}

class ListenerConnection : public Connection
{
public:
	ListenerConnection();
	virtual ~ListenerConnection();

	const int BACKLOG = 10;
	bool startListen();
};

class ClientConnection : public Connection
{
public:
	ClientConnection();
	virtual ~ClientConnection();
};
#pragma once
#include "Utils.h"
#include "Connection.h"


// has
	// client connection
	// array of open communication channels
	// cinToPacket parser
class Client
{
public:
	Client(const char* host, const char* port);


private:
	ClientConnection connection;

};


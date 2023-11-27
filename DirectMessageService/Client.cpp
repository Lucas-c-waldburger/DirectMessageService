#include "Client.h"

Client::Client(const char* host, const char* port)
{
	if (!connection.setUp(host, port))
		throw std::runtime_error("client setup failed");


}

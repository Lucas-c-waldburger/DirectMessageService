#pragma once
#include "ListenerConnection.h"
#include "Connection.h"
#include "PollGroup.h"
#include "CreateSerialPacket.h"
#include "UserSet.h"
#include <set>
#include <functional>


// need an entered-text parser to convert raw char buf to proper Out PacketType
	// determine PacketType
	// make corresponding outPacket

class Server
{
public:
	Server(const char* host, const char* port);
	~Server();

	//int handleEvents();

private:
	ListenerConnection listener;
	std::unique_ptr<PollGroup> pollGroup;
	UserSet users;
	SerializedPacket serializer;

	//int acceptConnection();

	bool disconnectUser(SOCKET fd);


};






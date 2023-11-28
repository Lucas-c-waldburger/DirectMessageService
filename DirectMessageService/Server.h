#pragma once
#include "Connection.h"
#include "PollGroup.h"
#include "CreateSerialPacket.h"
#include "UserSet.h"
#include "RecvHandler.h"


// need an entered-text parser to convert raw char buf to proper Out PacketType
	// determine PacketType
	// make corresponding outPacket

class Server
{
public:
	Server(const char* host, const char* port);
	~Server();

	bool eventLoop();

	bool recvAll(SOCKET fd);

private:
	ListenerConnection listener;
	std::unique_ptr<PollGroup> pollGroup; // change pollGroup ctor, make this stack allocated
	UserSet users;
	RecvHandler recvHandler;

	//AskUsernameBuffer askUsernameBuf;

	//int acceptConnection();
	//int handleEvents();

	bool disconnectUser(SOCKET fd);


};






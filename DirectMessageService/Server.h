#pragma once
#include "Connection.h"
#include "PollGroup.h"
#include "CreateSerialPacket.h"
#include "UsernameValidation.h"
#include "RecvHandler.h"

// TODO:
	// in RecvHandler.h
		// make RecvHandler into a DataTransmission abstract class
		// have RecvHandler and SendHandler derive from it
	// in Buffer.h (or new related file)
		// make preset constexpr messages to populate send buffers with
		// ex: successful connection, etc...


using namespace UsernameValidation;

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
	UsernameValidator validateUsername;

	RecvHandler recvHandler;

	//int acceptConnection();
	//int handleEvents();

	bool disconnectUser(SOCKET fd);


};






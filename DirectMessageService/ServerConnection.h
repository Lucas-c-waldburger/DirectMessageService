#pragma once
#include "SockConnection.h"



class ServerConnection : public SockConnection
{
public:
	ServerConnection();
	virtual ~ServerConnection();
};


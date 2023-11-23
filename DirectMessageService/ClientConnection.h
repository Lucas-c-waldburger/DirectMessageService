#pragma once
#include "SockConnection.h"



class ClientConnection : public SockConnection
{
public:
	ClientConnection();
	virtual ~ClientConnection();
};


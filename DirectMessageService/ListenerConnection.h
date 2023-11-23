#pragma once
#include "SockConnection.h"


const int BACKLOG_MAX = 10;

class ListenerConnection : public SockConnection
{
public:
	ListenerConnection();
	virtual ~ListenerConnection();

	bool startListen();

private:
	int backLog;
};


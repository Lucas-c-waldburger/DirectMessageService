#pragma once
#include "SockConnection.h"


const int BACKLOG_MAX = 10;

class ListenerConnectionOLD : public SockConnection
{
public:
	ListenerConnectionOLD();
	virtual ~ListenerConnectionOLD();

	bool startListen();

private:
	int backLog;
};




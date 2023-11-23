#pragma once
#include <iostream>
#include <memory>
#include "WSAInit.h"
#include "Server.h"

// TELNET 2601:88:8100:42a0:294d:e579:992e:30fc 3490

namespace App
{
	const char HOST_IP[] = "2601:88:8100:42a0:294d:e579:992e:30fc";
	const char PORT[] = "3490";
	const int BACKLOG_MAX = 10;

	static std::unique_ptr<WSAInit> wsaInit;
	static std::unique_ptr<Server> server;

	bool Init();

};


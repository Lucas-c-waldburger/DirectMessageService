#pragma once

#define RUN_AS_SERVER 1
#define RUN_AS_CLIENT 0

#include "WSAInit.h"

#if RUN_AS_SERVER
#include "Server.h"

#elif RUN_AS_CLIENT
#include "Client.h"

#endif


namespace App
{
	const char HOST_IP[] = "2601:88:8100:42a0:294d:e579:992e:30fc";
	const char PORT[] = "3490";
	const int BACKLOG_MAX = 10;

	static std::unique_ptr<WSAInit> wsaInit;

#if RUN_AS_SERVER
	static std::unique_ptr<Server> server;

#elif RUN_AS_CLIENT
	static std::unique_ptr<Client> client;

#endif

	bool Init();

};


#include "WSAInit.h"

WSADATA WSAInit::wsaData{};

WSAInit::WSAInit()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw std::runtime_error("WSAStartup failed");
	}

	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		throw std::runtime_error("Version 2.2 of Winsock is not available");
	}
}

WSAInit::~WSAInit()
{
	WSACleanup();
}

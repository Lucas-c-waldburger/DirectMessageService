#pragma once
#include "Utils.h"
#include <memory>

using namespace Utils;

class SockConnection
{
public:
	SockConnection();
	virtual ~SockConnection();

	int setUp(const char* host, const char* port);
	bool isSetUp();

	SOCKET getFd() const;
	int getFamily() const;
	std::string getAddrStr() const;

protected:
	struct SC_AddrData
	{
		SOCKET sockFd;
		int family;
		char addrStr[INET6_ADDRSTRLEN];

		static std::unique_ptr<SC_AddrData> makeAddrData(SOCKET fd, addrinfo* p);

	private:
		int makeAddrStr(addrinfo* p);
	};
	std::unique_ptr<SC_AddrData> addrData;

	int (*connectionTask) (addrinfo*, addrinfo*&) = 0;

	static int SC_getAddrInfo(const char* host, const char* port, addrinfo*& ai);
	static int SC_bindFirstAvail(addrinfo* ai, addrinfo*& p);
	static int SC_connectFirstAvail(addrinfo* ai, addrinfo*& p);
};

 




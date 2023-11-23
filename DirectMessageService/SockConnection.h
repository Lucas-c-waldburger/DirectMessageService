#pragma once
#include "Utils.h"
#include <memory>

using namespace Utils;


// what do i actually NEED from here
	// auto-set up functionality
	// SOCKET fd
	
class SockConnection
{
public:
	struct SC_AddrData;

	SockConnection();
	virtual ~SockConnection();

	bool setUp(const char* host, const char* port);
	bool isSetUp() const;
	bool close();

	std::unique_ptr<SC_AddrData>& getAddrData();

protected:
	struct SC_AddrData
	{
		SC_AddrData(SOCKET fd, addrinfo* p);

		SOCKET fd;
		int family;
		char addrStr[INET6_ADDRSTRLEN];

		static std::unique_ptr<SC_AddrData> makeAddrData(SOCKET fd, addrinfo* p);

	private:
		bool makeAddrStr(addrinfo* p);
	};
	std::unique_ptr<SC_AddrData> addrData;

	// either bound to bindFirstAvail or connectFirstAvail
	int (*connectionTask) (addrinfo*, addrinfo*&) = 0;

	static int SC_getAddrInfo(const char* host, const char* port, addrinfo*& ai);
	static int SC_bindFirstAvail(addrinfo* ai, addrinfo*& p);
	static int SC_connectFirstAvail(addrinfo* ai, addrinfo*& p);
};

 
//namespace SockConnections
//{
//	int SC_getAddrInfo(const char* host, const char* port, addrinfo*& ai);
//	int SC_bindFirstAvail(addrinfo* ai, addrinfo*& p);
//	int SC_connectFirstAvail(addrinfo* ai, addrinfo*& p);
//
//	//std::unique_ptr<SC_AddrData> makeAddrData(SOCKET fd, addrinfo* p);
//
//	struct SC_AddrData
//	{
//		SC_AddrData(SOCKET fd, addrinfo* p);
//
//		SOCKET fd;
//		int family;
//		char addrStr[INET6_ADDRSTRLEN];
//
//		static std::unique_ptr<SC_AddrData> makeAddrData(SOCKET fd, addrinfo* p);
//
//	private:
//		bool makeAddrStr(addrinfo* p);
//	};
//};


// makeListener
// makeServConnection
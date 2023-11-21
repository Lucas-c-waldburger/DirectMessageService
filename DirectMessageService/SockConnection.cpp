#include "SockConnection.h"

SockConnection::SockConnection() : addrData(nullptr)
{}

SockConnection::~SockConnection()
{}


int SockConnection::setUp(const char* host, const char* port)
{
    SOCKET fd;
    addrinfo* ai, * p;

    if (SC_getAddrInfo(host, port, ai) == SOCKET_ERROR)
    {
        reportWSAErr("SC_getAddrInfo()", WSAGetLastError());
        return -1;
    }

    fd = connectionTask(ai, p);

    if (fd == SOCKET_ERROR)
    {
        freeaddrinfo(ai);
        reportWSAErr("connectionTask()", WSAGetLastError());
        return -1;
    }

    // p not null, use it to construct addrData ptr
    this->addrData = SC_AddrData::makeAddrData(fd, p);

    freeaddrinfo(ai);

    return 0;
}

bool SockConnection::isSetUp()
{
    return addrData != nullptr;
}


SOCKET SockConnection::getFd() const
{
    if (!addrData)
        throw std::runtime_error("SockConnection not set up");

    return addrData->sockFd;
}


int SockConnection::getFamily() const
{
    if (!addrData)
        throw std::runtime_error("SockConnection not set up");

    return addrData->family;
}


std::string SockConnection::getAddrStr() const
{
    if (!addrData)
        throw std::runtime_error("SockConnection not set up");

    return addrData->addrStr;
}


std::unique_ptr<SockConnection::SC_AddrData> SockConnection::SC_AddrData::makeAddrData(SOCKET fd, addrinfo* p)
{
    auto addrData = std::make_unique<SC_AddrData>();

    if (addrData->makeAddrStr(p) == -1)
        return nullptr;

    addrData->sockFd = fd;
    addrData->family = p->ai_family;

    return addrData;
}


int SockConnection::SC_AddrData::makeAddrStr(addrinfo* p)
{
    inet_ntop(p->ai_family, castInAddrIPv((struct sockaddr*)p->ai_addr), this->addrStr, sizeof(addrStr));

    if (!addrStr)
    {
        reportWSAErr("makeAddrStr(): inet_ntop", WSAGetLastError());
        return -1;
    }

    return 0;
}


int SockConnection::SC_getAddrInfo(const char* host, const char* port, addrinfo*& ai)
{
    addrinfo hints = makeHints();
    return getaddrinfo(host, port, &hints, &ai);
}


int SockConnection::SC_bindFirstAvail(addrinfo* ai, addrinfo*& p)
{
    SOCKET sockFd;
    int errRet;

    for (p = ai; p != nullptr; p = p->ai_next)
    {
        if ((sockFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == SOCKET_ERROR)
        {
            errRet = WSAGetLastError();
            reportWSAErr("socket()", errRet);
            std::cout << "attempting next...\n";
            continue;
        }

        setReuse(sockFd);

        if (bind(sockFd, p->ai_addr, p->ai_addrlen) == SOCKET_ERROR)
        {
            errRet = WSAGetLastError();
            reportWSAErr("bind()", errRet);
            std::cout << "attempting next...\n";
            continue;
        }

        break;
    }

    return (!p) ? SOCKET_ERROR : sockFd;
}


int SockConnection::SC_connectFirstAvail(addrinfo* ai, addrinfo*& p)
{
    SOCKET sockFd;
    int errRet;

    for (p = ai; p != nullptr; p = p->ai_next)
    {
        if ((sockFd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == SOCKET_ERROR)
        {
            errRet = WSAGetLastError();
            reportWSAErr("socket()", errRet);
            std::cout << "attempting next...\n";
            continue;
        }

        setReuse(sockFd);

        if (connect(sockFd, p->ai_addr, p->ai_addrlen) == SOCKET_ERROR)
        {
            closesocket(sockFd);
            errRet = WSAGetLastError();
            reportWSAErr("connect()", errRet);
            std::cout << "attempting next...\n";
            continue;
        }

        break;
    }

    return (!p) ? SOCKET_ERROR : sockFd;
}



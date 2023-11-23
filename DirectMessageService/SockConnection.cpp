#include "SockConnection.h"

SockConnection::SockConnection() : addrData(nullptr)
{}

SockConnection::~SockConnection()
{
    close(); // maybe not in destructor
}


// if true, we can be sure that addrData is not null
bool SockConnection::setUp(const char* host, const char* port)
{
    SOCKET fd;
    addrinfo* ai, * p;

    if (SC_getAddrInfo(host, port, ai) == SOCKET_ERROR)
    {
        reportWSAErr("SC_getAddrInfo()", WSAGetLastError());
        return false;
    }

    fd = connectionTask(ai, p);

    if (fd == SOCKET_ERROR)
    {
        freeaddrinfo(ai);
        reportWSAErr("connectionTask()", WSAGetLastError());
        return false;
    }

    // p not null, use it to construct addrData ptr
    this->addrData = SC_AddrData::makeAddrData(fd, p);

    freeaddrinfo(ai);

    return (addrData != nullptr);
}

bool SockConnection::isSetUp() const
{
    return addrData != nullptr;
}

bool SockConnection::close()
{
    if (addrData != nullptr)
    {
        if (closesocket(addrData->fd) == SOCKET_ERROR)
        {
            reportWSAErr("close()", WSAGetLastError());
            return false;
        }

        addrData = nullptr;
    }

    return true;
}

std::unique_ptr<SockConnection::SC_AddrData>& SockConnection::getAddrData()
{
    if (!addrData)
        throw std::runtime_error("SockConnection not set up");

    return addrData;
}

SockConnection::SC_AddrData::SC_AddrData(SOCKET fd, addrinfo* p) : fd(fd), family(p->ai_family)
{
    makeAddrStr(p);
}

// this doesn't need to be a factory?
std::unique_ptr<SockConnection::SC_AddrData> SockConnection::SC_AddrData::makeAddrData(SOCKET fd, addrinfo* p)
{
    auto addrData = std::make_unique<SC_AddrData>(fd, p);

    if (!addrData->makeAddrStr(p))
        return nullptr;

    return addrData;
}


bool SockConnection::SC_AddrData::makeAddrStr(addrinfo* p)
{
    inet_ntop(p->ai_family, castInAddrIPv((struct sockaddr*)p->ai_addr), this->addrStr, sizeof(addrStr));

    if (!addrStr)
    {
        reportWSAErr("makeAddrStr(): inet_ntop", WSAGetLastError());
        return false;
    }

    return true;
}


int SockConnection::SC_getAddrInfo(const char* host, const char* port, addrinfo*& ai)
{
    addrinfo hints = makeHints();
    return getaddrinfo(host, port, &hints, &ai);
}


int SockConnection::SC_bindFirstAvail(addrinfo* ai, addrinfo*& p)
{
    SOCKET fd;
    int errRet;

    for (p = ai; p != nullptr; p = p->ai_next)
    {
        if ((fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == SOCKET_ERROR)
        {
            errRet = WSAGetLastError();
            reportWSAErr("socket()", errRet);
            std::cout << "attempting next...\n";
            continue;
        }

        setSockReuse(fd);

        if (bind(fd, p->ai_addr, p->ai_addrlen) == SOCKET_ERROR)
        {
            errRet = WSAGetLastError();
            reportWSAErr("bind()", errRet);
            std::cout << "attempting next...\n";
            continue;
        }

        break;
    }

    return (!p) ? SOCKET_ERROR : fd;
}


int SockConnection::SC_connectFirstAvail(addrinfo* ai, addrinfo*& p)
{
    SOCKET fd;
    int errRet;

    for (p = ai; p != nullptr; p = p->ai_next)
    {
        if ((fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == SOCKET_ERROR)
        {
            errRet = WSAGetLastError();
            reportWSAErr("socket()", errRet);
            std::cout << "attempting next...\n";
            continue;
        }

        if (connect(fd, p->ai_addr, p->ai_addrlen) == SOCKET_ERROR)
        {
            closesocket(fd);
            errRet = WSAGetLastError();
            reportWSAErr("connect()", errRet);
            std::cout << "attempting next...\n";
            continue;
        }

        break;
    }

    return (!p) ? SOCKET_ERROR : fd;
}



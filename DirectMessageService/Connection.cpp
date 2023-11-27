#include "Connection.h"


Connection::Connection() : fd(nullptr)
{}

Connection::~Connection()
{
    delete fd;
}

const SOCKET* Connection::getFd()
{
    return fd;
}

bool Connection::setUp(const char* host, const char* port)
{
    if (fd != nullptr)
    {
        std::cout << "Connection is already set up";
        return false;
    }

    addrinfo* ai, * p;

    if (ConnectionTools::getAddrInfo(host, port, ai) == SOCKET_ERROR)
    {
        reportWSAErr("getAddrInfo()", WSAGetLastError());
        return false;
    }

    fd = new SOCKET(connectionTask(ai, p));

    if (*fd == SOCKET_ERROR)
    {
        delete fd;
        fd = nullptr;

        freeaddrinfo(ai);

        reportWSAErr("connectionTask()", WSAGetLastError());
        return false;
    }

    freeaddrinfo(ai);

    return true;
}

bool Connection::isSetUp()
{
    return fd != nullptr;
}


int ConnectionTools::getAddrInfo(const char* host, const char* port, addrinfo*& ai)
{
    addrinfo hints = makeHints();
    return getaddrinfo(host, port, &hints, &ai);
}


SOCKET ConnectionTools::bindFirstAvail(addrinfo* ai, addrinfo*& p)
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

SOCKET ConnectionTools::connectFirstAvail(addrinfo* ai, addrinfo*& p)
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

ListenerConnection::ListenerConnection()
{
    connectionTask = ConnectionTools::bindFirstAvail;
}

ListenerConnection::~ListenerConnection()
{}

bool ListenerConnection::startListen()
{
    if (!isSetUp())
    {
        std::cout << "Listener is not set up\n";
        return false;
    }

    if (listen(*fd, BACKLOG) == SOCKET_ERROR)
    {
        reportWSAErr("startListen()", WSAGetLastError());
        return false;
    }

    return true;
}

ClientConnection::ClientConnection()
{
    connectionTask = ConnectionTools::connectFirstAvail;
}

ClientConnection::~ClientConnection()
{}

#include "ListenerConnection.h"


ListenerConnection::ListenerConnection() : SockConnection(), backLog(BACKLOG_MAX)
{
    connectionTask = &SockConnection::SC_bindFirstAvail;
}

ListenerConnection::~ListenerConnection()
{}

bool ListenerConnection::startListen() // maybe move out to handler class
{
    if (!addrData)
    {
        std::cout << "SockConnection not set up\n";
        return false;
    }

    if (listen(addrData->fd, backLog) == SOCKET_ERROR)
    {
        reportWSAErr("startListen()", WSAGetLastError());
        return false;
    }

    return true;
}
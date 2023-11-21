#include "ListenerConnection.h"


ListenerConnection::ListenerConnection() : SockConnection(), backLog(BACKLOG_MAX)
{
    connectionTask = &SockConnection::SC_bindFirstAvail;
}

ListenerConnection::~ListenerConnection()
{}

int ListenerConnection::startListen() // maybe move out to handler class
{
    if (!addrData)
        throw std::runtime_error("SockConnection not set up");

    if (listen(addrData->sockFd, backLog) == SOCKET_ERROR)
    {
        reportWSAErr("startListen()", WSAGetLastError());
        return -1;
    }

    return 0;
}
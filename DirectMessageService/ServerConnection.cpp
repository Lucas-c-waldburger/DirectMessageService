#include "ServerConnection.h"

ServerConnection::ServerConnection() : SockConnection()
{
    connectionTask = &SockConnection::SC_connectFirstAvail;
}

ServerConnection::~ServerConnection()
{}

#include "ClientConnection.h"

ClientConnection::ClientConnection() : SockConnection()
{
    connectionTask = &SockConnection::SC_connectFirstAvail;
}

ClientConnection::~ClientConnection()
{}

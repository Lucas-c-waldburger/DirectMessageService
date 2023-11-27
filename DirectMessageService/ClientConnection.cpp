#include "ClientConnection.h"

ClientConnectionOLD::ClientConnectionOLD() : SockConnection()
{
    connectionTask = &SockConnection::SC_connectFirstAvail;
}

ClientConnectionOLD::~ClientConnectionOLD()
{}

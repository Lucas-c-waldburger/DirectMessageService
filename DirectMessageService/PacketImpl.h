#pragma once
#include "Packet.h"

// Maybe channel makes outMsgPackets through a factory function, which holds the fdIndex and prepends it to the buf during creation

class OutMsgPacket : public OutPacket<char*, 256>
{
public:
	OutMsgPacket();
	virtual ~OutMsgPacket();

	void fill(char* data) override;
};

class InMsgPacket : public InPacket<char*, 256>
{
public:
	InMsgPacket();
	virtual ~InMsgPacket();

	char* getData() override;

};


// used by server to send client the index of the socket inside server's pollGroup,
// corresponding to the socketFd the client is communicating with for an opened channel.
// this value is appended to the start of each message sent by the 
// client through that channel. The server reads it as a uint_8 and uses
// it to route the message to the appropriate socket
class FdIndexPacket : public Packet<uint16_t, sizeof(uint16_t)>
{
public:
	FdIndexPacket();
	virtual ~FdIndexPacket();

	void fill(uint16_t data) override;
};


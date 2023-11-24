#pragma once
#include "Packet.h"


//CLIENT SIDE: user enters raw text 
//CLIENT SIDE: parser takes raw text and interprets as a packet type
//CLIENT SIDE: packet factory creates derived packet and fills it with data
//CLIENT SIDE: serializer turns packet into serialized string
//CLIENT SIDE: send()s serialized string.c_str() to server

//SERVER SIDE: server recv()s char buffer from client
//SERVER SIDE: deserializes to auto, checks type, returns appropriate packet type












// Maybe channel makes outMsgPackets through a factory function, which holds the fdIndex and prepends it to the buf during creation
// MAKE FILL() pure virtual in OutPacket, do the hton functins in the derived OutLrgDataPacket type

//class OutMsgPacket : public OutPacket<char*, 256>
//{
//public:
//	OutMsgPacket();
//	virtual ~OutMsgPacket();
//
//	void fill(char* data) override;
//};
//
//class InMsgPacket : public InPacket<char*, 256>
//{
//public:
//	InMsgPacket();
//	virtual ~InMsgPacket();
//
//	char* getData() override;
//
//};
//
//
//class OutServCommandPacket;
//class InServCommandPacket;


// used by server to send client the index of the socket inside server's pollGroup,
// corresponding to the socketFd the client is communicating with for an opened channel.
// this value is appended to the start of each message sent by the 
// client through that channel. The server reads it as a uint_8 and uses
// it to route the message to the appropriate socket
// 
//class FdIndexPacket : public Packet<uint16_t, sizeof(uint16_t)>
//{
//public:
//	FdIndexPacket();
//	virtual ~FdIndexPacket();
//
//	void fill(uint16_t data) override;
//};


#pragma once
#include "Packet.h"
#include "Buffer.h"

// holds a pointer to base packet and each derived packet.
// deserializes recv()'d data into base packet, checks packet type, 
// casts it to that type and records the current packet type

class RecvHandler
{
public:
	RecvHandler() = default;

	RecvBuffer& getRecvBuf();
	const PacketType& toPacket();
	PacketType getActivePacketType() const;

	MessagePacket& getMsgPacket();
	ServerCommandPacket& getServCmdPacket();

private:
	RecvBuffer recvBuf;
	std::string serialStr;
	PacketType activePacketType;

	std::unique_ptr<Packet> mBasePacket;
	MessagePacket mMsgPacket;
	ServerCommandPacket mServCmdPacket;
};


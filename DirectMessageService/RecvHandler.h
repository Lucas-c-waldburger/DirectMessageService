#pragma once
#include "Packet.h"
#include "Buffer.h"

// holds a pointer to base packet and each derived packet.
// deserializes recv()'d data into base packet, checks packet type, 
// casts it to that type and records the current packet type

//class RecvHandler
//{
//public:
//	RecvHandler() = default;
//
//	RecvBuffer& getRecvBuf();
//	PacketType toPacket();
//	PacketType getActivePacketType() const;
//
//	MessagePacket& getMsgPacket();
//	ServerCommandPacket& getServCmdPacket();
//
//private:
//	RecvBuffer recvBuf;
//	std::string serialStr;
//	PacketType activePacketType;
//
//	std::unique_ptr<Packet> mBasePacket;
//	MessagePacket mMsgPacket;
//	ServerCommandPacket mServCmdPacket;
//};


class RecvHandler
{
public:
	RecvHandler();
	~RecvHandler() = default;

	RecvBuffer& getBuffer();
	PacketType getActivePacketType() const;

	PacketType deserializeToPacket();
	MessagePacket& castToMsgPacket();
	ServerCommandPacket& castToServCmdPacket();

private:
	RecvBuffer recvBuf;
	std::string serialStr;
	std::unique_ptr<Packet> basePacket;
	PacketType activePacketType;

	template <typename PACK_REF, PacketType packType>
	PACK_REF& packetCast();
};

template<typename PACK_REF, PacketType packType>
inline PACK_REF& RecvHandler::packetCast()
{
	if (!basePacket)
		throw std::runtime_error("basePacket is a nullptr");

	if (activePacketType != packType)
		throw std::invalid_argument("requested cast does not match active packet type");

	return dynamic_cast<PACK_REF&>(*basePacket);
}


// might need a "getbufSizePair()" if necessary
class SendHandler
{
public:
	SendHandler() = default;
	~SendHandler() = default;

	using bufSizePair = std::pair<const char*, size_t>;
	bufSizePair serializePacket(std::unique_ptr<Packet> const& pack);

private:
	std::string serialStr;

};



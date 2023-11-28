#pragma once
#include "Utils.h"
#include "TextEntry.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/unique_ptr.hpp>


enum PacketType
{
	EMPTY,
	MESSAGE,
	SERVER_COMMAND,
};

enum MessageType
{
	UNSPEC,
	DIRECT_MSG,
	USERNAME_REQ
};

class Packet
{
public:
	Packet();
	Packet(PacketType pType);
	virtual ~Packet() = default;

	PacketType getPacketType() const;

	static void serialize(std::string& serialStr, std::unique_ptr<Packet> const& pack);
	static std::unique_ptr<Packet> deserialize(const std::string& serialStr);

protected:
	PacketType packetType;

	friend class boost::serialization::access;

	template <typename Archive>
	inline void serialize(Archive& ar, unsigned v)
	{
		ar& packetType;
	}
};


class MessagePacket : public Packet
{
public:
	MessagePacket();
	MessagePacket(MessageType msgtyp, SOCKET destFd, const std::string& msg);
	virtual ~MessagePacket();

	MessageType getMsgType() const;
	SOCKET getDestFd() const;
	std::string getMsgStr() const;

private:
	friend class Mixin;

	MessageType msgType;
	SOCKET destFd;
	std::string msgStr;

	friend class boost::serialization::access;
	friend class Packet;

	template <typename Archive>
	inline void serialize(Archive& ar, unsigned v)
	{
		ar& boost::serialization::base_object<Packet>(*this);
		ar& msgType;
		ar& destFd;
		ar& msgStr;
	}
};


class ServerCommandPacket : public Packet
{
public:
	ServerCommandPacket();
	ServerCommandPacket(TextEntry::Type servCmdType, const std::string& suppTxt);
	virtual ~ServerCommandPacket();

	std::string getSupplementalText() const;

private:
	friend class Mixin;

	TextEntry::Type servCmdType;
	std::string supplementalText;

	friend class boost::serialization::access;
	friend class Packet;

	template <typename Archive>
	inline void serialize(Archive& ar, unsigned v)
	{
		ar& boost::serialization::base_object<Packet>(*this);
		ar& servCmdType;
		ar& supplementalText;
	}
};


BOOST_SERIALIZATION_ASSUME_ABSTRACT(Packet)
BOOST_CLASS_EXPORT_KEY(MessagePacket) // (KEY and IMPLEMENT split between .h and .cpp to avoid linker errors)
BOOST_CLASS_EXPORT_KEY(ServerCommandPacket)

////// SERIALIZING TOOL //////

//class SerializedPacket
//{
//public:
//	SerializedPacket();
//	~SerializedPacket();
//
//	char* serialize(const OutPacket& outPack);
//	void deserialize(InPacket& inPack);
//
//	void clear();
//
//private:
//	std::string serialStr;
//	char* serialBuf;
//
//	void prepSerialBuf(size_t strSz);
//};



#pragma once
#include "Utils.h"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/unique_ptr.hpp>


using SOCKET = unsigned long long;

enum PacketType
{
	UNSPEC,
	MESSAGE,
	NEW_CHANNEL_REQ,
	CHANNEL_CLOSE_REQ,
	LIST_USERS_REQ,
};

class Packet
{
public:
	Packet();
	Packet(PacketType t);
	virtual ~Packet() = default;

	PacketType getType() const;

	static void serialize(std::string& serialStr, std::unique_ptr<Packet> const& pack);
	static std::unique_ptr<Packet> deserialize(const std::string& serialStr);

protected:
	PacketType type;

	friend class boost::serialization::access;

	template <typename Archive>
	inline void serialize(Archive& ar, unsigned v)
	{
		ar& type;
	}
};


class MessagePacket : public Packet
{
public:
	MessagePacket();
	MessagePacket(SOCKET destFd, const std::string& msg);
	virtual ~MessagePacket();

	SOCKET getDestFd() const;
	std::string getMsg() const;

private:
	friend class Mixin;

	SOCKET destFd;
	std::string msg;

	friend class boost::serialization::access;
	friend class Packet;

	template <typename Archive>
	inline void serialize(Archive& ar, unsigned v)
	{
		ar& boost::serialization::base_object<Packet>(*this);
		ar& destFd;
		ar& msg;
	}
};


class ChannelReqPacket : public Packet
{
public:
	ChannelReqPacket();
	ChannelReqPacket(const std::string& reqNm);
	virtual ~ChannelReqPacket();

	std::string getReqUsername() const;

private:
	friend class Mixin;

	std::string reqUsername;

	friend class boost::serialization::access;
	friend class Packet;

	template <typename Archive>
	inline void serialize(Archive& ar, unsigned v)
	{
		ar& boost::serialization::base_object<Packet>(*this);
		ar& reqUsername;
	}
};



BOOST_SERIALIZATION_ASSUME_ABSTRACT(Packet)
BOOST_CLASS_EXPORT_KEY(MessagePacket) // (KEY and IMPLEMENT split between .h and .cpp to avoid linker errors)
BOOST_CLASS_EXPORT_KEY(ChannelReqPacket)

////// SERIALIZING TOOL //////

//class SerialPacket
//{
//public:
//	SerialPacket();
//	~SerialPacket();
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



#pragma once
#include "Utils.h"
#include "PacketSerializer.h"

using namespace Utils;

enum PacketType
{
	UNSPEC,
	MESSAGE,
	CHANNEL_OPEN_REQ,
	CHANNEL_CLOSE_REQ,
	LIST_USERS_REQ,
};


class Packet
{
public:
	Packet();
	Packet(PacketType type);
	virtual ~Packet() = 0;

	//static std::unique_ptr<OutPacket> makeOutPacket(PacketType);
	//char* readBuf();
	//virtual void clearBuf();

protected:
	friend class boost::serialization::access;
	friend class SerialPacket;

	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& packType;
		ar& dataStr;
	}

	PacketType packType;
	std::string dataStr;
};

////// OUT //////
class OutPacket : public Packet
{
public:
	OutPacket();
	OutPacket(PacketType type);
	virtual ~OutPacket() override;

	//virtual void clearBuf() override;
	//virtual void fill(T data);
	//bool isEmpty();

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Packet>(*this);
		ar& packType;
		ar& dataStr;
	}
};

////// IN //////
class InPacket : public Packet
{
public:
	InPacket();
	InPacket(PacketType type);
	virtual ~InPacket() override;

private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Packet>(*this);
		ar & packType;
		ar & dataStr;
	}
};

////// SERIALIZING TOOL //////

class SerialPacket
{
public:
	SerialPacket();
	~SerialPacket();

	char* serialize(const OutPacket& outPack);
	void deserialize(InPacket& inPack);

	void clear();

private:
	std::string serialStr;
	char* serialBuf;

	void prepSerialBuf(size_t strSz);
};





// ------------------------ DEFINITIONS ---------------------------- //

// -------------- Packet --------------- //


//template<typename T, int BUF_SIZE>
//inline char* Packet<T>::readBuf()
//{
//	return this->buf;
//}
//
//template<typename T, int BUF_SIZE>
//inline void Packet<T>::clearBuf()
//{
//	memset(this->buf, 0, sizeof(this->buf));
//}


// -------------- OutPacket --------------- //


//template<typename T>
//inline void OutPacket<T>::clearBuf()
//{
//	Packet<T, BUF_SIZE>::clearBuf();
//	empty = true;
//}

//template<typename T>
//inline void OutPacket<T>::fill(T data)
//{
//	T orderedData = convertDataByteOrder(data, this->byteOrdering);
//	memcpy(this->buf, &orderedData, sizeof(orderedData));
//	empty = false;
//}
//
//template<typename T>
//inline bool OutPacket<T>::isEmpty()
//{
//	return empty;
//}


// -------------- InPacket --------------- //


//template<typename T>
//inline T InPacket<T>::getData()
//{
//	return data;
//}


// -------------- Serialize / Deserialize --------------- //

// Serialize (outpacket)
	// 1. create outpacket (packType, fdDestination (either server or a specific user), dataContent)
		// 1a. convert
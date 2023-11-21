#pragma once
#include "Utils.h"

using namespace Utils;

template <typename T, int BUF_SIZE>
class Packet
{
public:
	Packet(Endian byteOrd);
	virtual ~Packet() = 0;

	char* readBuf();
	virtual void clearBuf();

protected:
	char buf[BUF_SIZE];
	Endian byteOrdering;
};

template <typename T, int BUF_SIZE>
class OutPacket : public Packet<T, BUF_SIZE>
{
public:
	OutPacket();
	virtual ~OutPacket() override;

	virtual void clearBuf() override;
	virtual void fill(T data);
	bool isEmpty();

protected:
	bool empty;
};

template <typename T, int BUF_SIZE>
class InPacket : public Packet<T, BUF_SIZE>
{
public:
	InPacket();
	virtual ~InPacket() override;

	virtual T getData();

protected:
	T data;
};

// ------------------------ DEFINITIONS ---------------------------- //

// -------------- Packet --------------- //

template<typename T, int BUF_SIZE>
inline Packet<T, BUF_SIZE>::Packet(Endian byteOrd) : byteOrdering(byteOrd)
{
	clearBuf();
}

template<typename T, int BUF_SIZE>
inline char* Packet<T, BUF_SIZE>::readBuf()
{
	return buf;
}

template<typename T, int BUF_SIZE>
inline void Packet<T, BUF_SIZE>::clearBuf()
{
	memset(buf, 0, sizeof(buf));
}


// -------------- OutPacket --------------- //

template<typename T, int BUF_SIZE>
inline OutPacket<T, BUF_SIZE>::OutPacket() : Packet(Endian::TO_NETWORK), empty(true)
{}

template<typename T, int BUF_SIZE>
inline OutPacket<T, BUF_SIZE>::~OutPacket()
{}

template<typename T, int BUF_SIZE>
inline void OutPacket<T, BUF_SIZE>::clearBuf()
{
	Packet<T, BUF_SIZE>::clearBuf();
	empty = true;
}

template<typename T, int BUF_SIZE>
inline void OutPacket<T, BUF_SIZE>::fill(T data)
{
	T orderedData = convertDataByteOrder(data, byteOrdering);
	memcpy(buf, &orderedData, sizeof(orderedData));
	empty = false;
}

template<typename T, int BUF_SIZE>
inline bool OutPacket<T, BUF_SIZE>::isEmpty()
{
	return empty;
}


// -------------- InPacket --------------- //

template<typename T, int BUF_SIZE>
inline InPacket<T, BUF_SIZE>::InPacket() : Packet(Endian::TO_HOST)
{}

template<typename T, int BUF_SIZE>
inline InPacket<T, BUF_SIZE>::~InPacket()
{}

template<typename T, int BUF_SIZE>
inline T InPacket<T, BUF_SIZE>::getData()
{
	return data;
}

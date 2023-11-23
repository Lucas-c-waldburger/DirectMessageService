#include "Packet.h"

Packet::Packet() : packType(UNSPEC)
{}

Packet::Packet(PacketType type) : packType(type)
{}

Packet::~Packet()
{}


OutPacket::OutPacket() : Packet()
{}

OutPacket::OutPacket(PacketType type) : Packet(type)
{}

OutPacket::~OutPacket()
{}


InPacket::InPacket() : Packet()
{}

InPacket::InPacket(PacketType type) : Packet(type)
{}

InPacket::~InPacket()
{}


SerialPacket::SerialPacket() : serialBuf(nullptr)
{}

SerialPacket::~SerialPacket()
{
	delete[] serialBuf;
}

char* SerialPacket::serialize(const OutPacket& outPack)
{
	clear();

	PacketSerializer::serializeToString(serialStr, outPack);

	auto strSz = serialStr.size() + 1;
	prepSerialBuf(strSz);
	memcpy(serialBuf, serialStr.c_str(), strSz);

	return serialBuf;
}

void SerialPacket::deserialize(InPacket& inPack)
{
	if (!serialStr.empty())
		PacketSerializer::deSerialize(serialStr, inPack);
}


void SerialPacket::clear()
{
	if (serialBuf)
		memset(serialBuf, 0, sizeof(serialBuf));

	serialStr.clear();
}


void SerialPacket::prepSerialBuf(size_t strSz)
{
	bool bufLargeEnough = false;

	if (serialBuf)
	{
		// if serialBuf already allocated & enough space for new str
		if (strSz <= strlen(serialBuf))
			bufLargeEnough = true;

		else
			delete[] serialBuf;
	}

	else if (!serialBuf || !bufLargeEnough)
		serialBuf = new char[strSz];
}
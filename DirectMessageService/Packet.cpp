#include "Packet.h"


Packet::Packet() : packetType(EMPTY)
{}

Packet::Packet(PacketType pType) : packetType(pType)
{}

Packet::~Packet()
{}

PacketType Packet::getPacketType() const
{
	return packetType;
}

void Packet::serialize(std::string& serialStr, std::unique_ptr<Packet> const& pack)
{
	boost::iostreams::back_insert_device<std::string> inserter(serialStr);
	boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> stream(inserter);
	boost::archive::binary_oarchive oa(stream);

	oa << pack;

	stream.flush();
};


std::unique_ptr<Packet> Packet::deserialize(const std::string& serialStr)
{
	std::unique_ptr<Packet> pack;

	boost::iostreams::basic_array_source<char> device(serialStr.data(), serialStr.size());
	boost::iostreams::stream<boost::iostreams::basic_array_source<char>> stream(device);
	boost::archive::binary_iarchive ia(stream);

	ia >> pack;

	return pack;
}


MessagePacket::MessagePacket() : Packet(MESSAGE), msgType(UNSPEC), destFd(SOCKET_ERROR)
{}

MessagePacket::MessagePacket(MessageType msgtyp, SOCKET destFd, const std::string& msg) : Packet(MESSAGE), msgType(msgtyp), destFd(destFd), msgStr(msg)
{}

MessagePacket::~MessagePacket()
{}

MessageType MessagePacket::getMsgType() const
{
	return msgType;
}

SOCKET MessagePacket::getDestFd() const
{
	return destFd;
}

const std::string& MessagePacket::getMsgStr() const
{
	return msgStr;
}


ServerCommandPacket::ServerCommandPacket() : Packet(SERVER_COMMAND)
{}

ServerCommandPacket::ServerCommandPacket(TextEntry::Type servCmdType, const std::string& suppTxt) : Packet(SERVER_COMMAND), supplementalText(suppTxt)
{}

ServerCommandPacket::~ServerCommandPacket()
{}

std::string ServerCommandPacket::getSupplementalText() const
{
	return supplementalText;
}


BOOST_CLASS_EXPORT_IMPLEMENT(MessagePacket)
BOOST_CLASS_EXPORT_IMPLEMENT(ServerCommandPacket)


//SerializedPacket::SerializedPacket() : serialBuf(nullptr)
//{}
//
//SerializedPacket::~SerializedPacket()
//{
//	delete[] serialBuf;
//}
//
//char* SerializedPacket::serialize(const OutPacket& outPack)
//{
//	clear();
//
//	PacketSerializer::serializeToString(serialStr, outPack);
//
//	auto strSz = serialStr.size() + 1;
//	prepSerialBuf(strSz);
//	memcpy(serialBuf, serialStr.c_str(), strSz);
//
//	return serialBuf;
//}
//
//void SerializedPacket::deserialize(InPacket& inPack)
//{
//	if (!serialStr.empty())
//		PacketSerializer::deSerialize(serialStr, inPack);
//}
//
//
//void SerializedPacket::clear()
//{
//	if (serialBuf)
//		memset(serialBuf, 0, sizeof(serialBuf));
//
//	serialStr.clear();
//}
//
//
//void SerializedPacket::prepSerialBuf(size_t strSz)
//{
//	bool bufLargeEnough = false;
//
//	if (serialBuf)
//	{
//		// if serialBuf already allocated & enough space for new str
//		if (strSz <= strlen(serialBuf))
//			bufLargeEnough = true;
//
//		else
//			delete[] serialBuf;
//	}
//
//	else if (!serialBuf || !bufLargeEnough)
//		serialBuf = new char[strSz];
//}



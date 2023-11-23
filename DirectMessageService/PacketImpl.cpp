#include "PacketImpl.h"



//FdIndexPacket::FdIndexPacket() : Packet(Endian::TO_NETWORK)
//{}
//
//FdIndexPacket::~FdIndexPacket()
//{}
//
//
//void FdIndexPacket::fill(uint16_t data)
//{
//	try
//	{
//		prepDataForSend(data, byteOrdering, buf);
//		empty = false;
//	}
//
//	catch (std::invalid_argument& ex)
//	{
//		std::cout << ex.what();
//	}
//}

//OutMsgPacket::OutMsgPacket() : OutPacket<char*, 256>()
//{}
//
//OutMsgPacket::~OutMsgPacket()
//{}
//
//void OutMsgPacket::fill(char* data)
//{
//	memcpy(buf, data, sizeof(buf));
//	empty = false;
//}
//
//char* InMsgPacket::getData()
//{
//	return readBuf();
//}

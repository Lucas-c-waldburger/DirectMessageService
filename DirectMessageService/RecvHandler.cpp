#include "RecvHandler.h"

//RecvBuffer& RecvHandler::getRecvBuf()
//{
//    return recvBuf;
//}
//
//PacketType RecvHandler::toPacket()
//{
//    if (recvBuf.currentLen() == 0)
//        return EMPTY;
//
//    serialStr = recvBuf.data();
//    recvBuf.clear();
//
//    mBasePacket = Packet::deserialize(serialStr);
//    activePacketType = mBasePacket->getPacketType();
//
//    switch (activePacketType)
//    {
//    case MESSAGE:
//    {
//        mMsgPacket = dynamic_cast<MessagePacket&>(*mBasePacket);
//        break;
//    }
//    case SERVER_COMMAND:
//    {
//        mServCmdPacket = dynamic_cast<ServerCommandPacket&>(*mBasePacket);
//        break;
//    }
//    }
//
//    mBasePacket = nullptr;
//
//    return activePacketType;
//}
//
//PacketType RecvHandler::getActivePacketType() const
//{
//    return activePacketType;
//}
//
//MessagePacket& RecvHandler::getMsgPacket()
//{
//    if (activePacketType != MESSAGE)
//        throw std::runtime_error("Can only retrieve active packet of type Message");
//
//    return mMsgPacket;
//}
//
//ServerCommandPacket& RecvHandler::getServCmdPacket()
//{
//    if (activePacketType != SERVER_COMMAND)
//        throw std::runtime_error("Can only retrieve active packet of type Server Command");
//
//    return mServCmdPacket;
//}


//////////////////////////////////// RECV HANDLER ////////////////////////////////////////

RecvHandler::RecvHandler() : activePacketType(EMPTY)
{}

RecvBuffer& RecvHandler::getBuffer()
{
    return recvBuf;
}

PacketType RecvHandler::getActivePacketType() const
{
    return activePacketType;
}

PacketType RecvHandler::deserializeToPacket()
{
    if (recvBuf.currentLen() == 0)
        return EMPTY;

    serialStr = recvBuf.data();
    recvBuf.clear();

    basePacket = Packet::deserialize(serialStr);
    activePacketType = basePacket->getPacketType();

    return activePacketType;
}

MessagePacket& RecvHandler::castToMsgPacket()
{
    return packetCast<MessagePacket, MESSAGE>();
}

ServerCommandPacket& RecvHandler::castToServCmdPacket()
{
    return packetCast<ServerCommandPacket, SERVER_COMMAND>();
}


//////////////////////////////////// SEND HANDLER ////////////////////////////////////////

SendHandler::bufSizePair SendHandler::serializePacket(std::unique_ptr<Packet> const& pack)
{
    serialStr.clear();
    Packet::serialize(serialStr, pack);

    return std::make_pair(serialStr.c_str(), serialStr.length());
}

#include "RecvHandler.h"

RecvBuffer& RecvHandler::getRecvBuf()
{
    return recvBuf;
}

const PacketType& RecvHandler::toPacket()
{
    if (recvBuf.currentLen() == 0)
        return EMPTY;

    serialStr = recvBuf.data();
    recvBuf.clear();

    mBasePacket = Packet::deserialize(serialStr);
    activePacketType = mBasePacket->getPacketType();

    switch (activePacketType)
    {
    case MESSAGE:
    {
        mMsgPacket = dynamic_cast<MessagePacket&>(*mBasePacket);
        break;
    }
    case SERVER_COMMAND:
    {
        mServCmdPacket = dynamic_cast<ServerCommandPacket&>(*mBasePacket);
        break;
    }
    }

    mBasePacket = nullptr;

    return activePacketType;
}

PacketType RecvHandler::getActivePacketType() const
{
    return activePacketType;
}

MessagePacket& RecvHandler::getMsgPacket()
{
    if (activePacketType != MESSAGE)
        throw std::runtime_error("Can only retrieve active packet of type Message");

    return mMsgPacket;
}

ServerCommandPacket& RecvHandler::getServCmdPacket()
{
    if (activePacketType != SERVER_COMMAND)
        throw std::runtime_error("Can only retrieve active packet of type Server Command");

    return mServCmdPacket;
}

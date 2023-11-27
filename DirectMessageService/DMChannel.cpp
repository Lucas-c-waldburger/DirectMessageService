#include "DMChannel.h"


DMChannel::DMChannel(SOCKET recFd, const std::string& senderUsrnm) : recipientFd(recFd), senderUsername(senderUsrnm), assembledMsg(senderUsrnm)
{}





DMChannel::AssembledMessage::AssembledMessage(const std::string& senderUsrnm) : mMsg('[' + senderUsrnm + "]: "), lenUsrnmDecoration(mMsg.length())
{}

bool DMChannel::AssembledMessage::empty()
{
	return mMsg.length() == lenUsrnmDecoration;
}

void DMChannel::AssembledMessage::set(const std::string& typedMsg)
{
	if (!empty())
		clear();

	mMsg += typedMsg;
}

const std::string& DMChannel::AssembledMessage::get()
{
	return mMsg;
}

void DMChannel::AssembledMessage::clear()
{
	mMsg.erase(lenUsrnmDecoration);
}


